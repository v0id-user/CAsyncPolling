#include "async.h"
#include "poll.h"
#include "pprint.h"
#include "scheduler.h"
#include "async_func.h" 

#include <stdbool.h>
#include <stdint.h>
// Internal state of the functions
struct async_state
{
    schedular_t *schedular;
    int32_t current_function_index;
    CONTEXT_POINTER main_thread;
    bool is_running;
};

static void async_run(async_ctx *self_ctx, async_func_t *f){
    // Chain in the poll
    if (self_ctx->poll == NULL)
    {
        HANDLE_ERROR("ASYNC_RUN: Poll is NULL");
    }

    poll_t *poll = self_ctx->poll;
    poll->chain(poll->ctx, f, self_ctx);
}

async *async_init()
{
    DEBUG_PRINT("Initializing async");

    // First allocate the main structure
    async *self = (async *)malloc(sizeof(async));
    if (self == NULL)
    {
        HANDLE_ERROR("Failed to allocate memory for async");
        return NULL;
    }

    // Initialize all pointers to NULL first
    self->ctx = NULL;
    self->async_run = NULL;
    self->async_yield = NULL;

    // Allocate and initialize the state
    self->ctx = (async_ctx *)malloc(sizeof(async_ctx));
    if (self->ctx == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
        return NULL;
    }

    // Initialize ctx pointers to NULL
    self->ctx->poll = NULL;
    self->ctx->state = NULL;

    self->ctx->state = (async_state *)malloc(sizeof(async_state));
    if (self->ctx->state == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
        return NULL;
    }

    // Initialize state pointers to NULL
    self->ctx->state->schedular = NULL;
    self->ctx->state->main_thread = NULL;
    self->ctx->state->is_running = false;
    self->ctx->state->current_function_index = 0;

    self->ctx->state->schedular = schedular_new();
    if (self->ctx->state->schedular == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to create scheduler");
        return NULL;
    }

// Initialize the context/fiber
#ifdef _WIN32
    DEBUG_PRINT("Converting thread to fiber");
    self->ctx->state->main_thread = ConvertThreadToFiber(NULL);
    if (self->ctx->state->main_thread == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to convert thread to fiber");
        return NULL;
    }
#else
    DEBUG_PRINT("Allocating memory for main_thread");
    self->ctx->state->main_thread = malloc(sizeof(ucontext_t));
    if (self->ctx->state->main_thread == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for main_thread");
        return NULL;
    }

    DEBUG_PRINT("Getting context");
    if (getcontext(self->ctx->state->main_thread) != 0)
    {
        async_free(self);
        HANDLE_ERROR("Failed to get context");
        return NULL;
    }
#endif

    // Initialize the poll last
    self->ctx->poll = poll_new();
    if (self->ctx->poll == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to create poll");
        return NULL;
    }

    // Set function pointers last
    self->async_run = async_run;

    DEBUG_PRINT("Async initialization complete");
    return self;
}

void async_free(async *self)
{
    DEBUG_PRINT("Freeing async");
    if (self == NULL) {
        return;
    }

    if (self->ctx == NULL) {
        free(self);
        return;
    }

    // Free poll if it exists
    if (self->ctx->poll != NULL) {
        poll_free(self->ctx->poll);
        self->ctx->poll = NULL;
    }

    // Free state and its contents if they exist
    if (self->ctx->state != NULL) {
        if (self->ctx->state->schedular != NULL) {
            schedular_free(self->ctx->state->schedular);
            self->ctx->state->schedular = NULL;
        }

        if (self->ctx->state->main_thread != NULL) {
            DEBUG_PRINT("Freeing main_thread");
#ifdef _WIN32
            // Convert back to thread before freeing
            if (!ConvertFiberToThread()) {
                DEBUG_PRINT("Warning: Failed to convert fiber back to thread");
            }
#else
            free(self->ctx->state->main_thread);
#endif
            self->ctx->state->main_thread = NULL;
        }

        DEBUG_PRINT("Freeing state");
        free(self->ctx->state);
        self->ctx->state = NULL;
    }

    DEBUG_PRINT("Freeing ctx");
    free(self->ctx);
    self->ctx = NULL;

    DEBUG_PRINT("Freeing async");
    free(self);
}