#include "async.h"
#include "poll.h"
#include "pprint.h"

#include <stdbool.h>

// Internal state of the functions
struct async_state
{
    CONTEXT_POINTER main_thread;
    bool is_running;
};

void async_wait(async *self)
{
    if (self != NULL && self->ctx->poll != NULL)
    {   
        self->ctx->poll->wait(self->ctx->poll);
    }
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
    self->async_wait = NULL;
    self->async_yield = NULL;

    // Allocate and initialize the state
    self->ctx = (async_ctx *)malloc(sizeof(async_ctx));
    if (self->ctx == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
        return NULL;
    }
    self->ctx->state = (async_state *)malloc(sizeof(async_state));
    if (self->ctx->state == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
        return NULL;
    }

    // Initialize state members
    self->ctx->state->is_running  = false;
    self->ctx->state->main_thread = NULL;

// Initialize the context/fiber
#ifdef _WIN32
    DEBUG_PRINT("Converting thread to fiber");
    self->ctx->main_thread = ConvertThreadToFiber(NULL);
    if (self->ctx->main_thread == NULL)
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
    self->async_wait = async_wait;

    DEBUG_PRINT("Async initialization complete");
    return self;
}

void async_free(async *self)
{
    DEBUG_PRINT("Freeing async");
    if (self != NULL)
    {
        if (self->ctx->poll != NULL)
        {
            poll_free(self->ctx->poll);
            self->ctx->poll = NULL;
        }
        if (self->ctx != NULL)
        {
            if (self->ctx->state->main_thread != NULL)
            {
                DEBUG_PRINT("Freeing main_thread");
                free(self->ctx->state->main_thread);
                self->ctx->state->main_thread = NULL;
            }
            DEBUG_PRINT("Freeing state");
            free(self->ctx->state);
            self->ctx->state = NULL;

            DEBUG_PRINT("Freeing ctx");
            free(self->ctx);
            self->ctx = NULL;
        }
        DEBUG_PRINT("Freeing async");
        free(self);
    }
}