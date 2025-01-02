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
    if (self != NULL && self->poll != NULL)
    {
        self->poll->wait(self->poll);
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
    self->poll       = NULL;
    self->state      = NULL;
    self->async_wait = NULL;

    // Allocate and initialize the state
    self->state = (async_state *)malloc(sizeof(async_state));
    if (self->state == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
        return NULL;
    }

    // Initialize state members
    self->state->is_running  = false;
    self->state->main_thread = NULL;

// Initialize the context/fiber
#ifdef _WIN32
    DEBUG_PRINT("Converting thread to fiber");
    self->state->main_thread = ConvertThreadToFiber(NULL);
    if (self->state->main_thread == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to convert thread to fiber");
        return NULL;
    }
#else
    DEBUG_PRINT("Allocating memory for main_thread");
    self->state->main_thread = malloc(sizeof(ucontext_t));
    if (self->state->main_thread == NULL)
    {
        async_free(self);
        HANDLE_ERROR("Failed to allocate memory for main_thread");
        return NULL;
    }

    DEBUG_PRINT("Getting context");
    if (getcontext(self->state->main_thread) != 0)
    {
        async_free(self);
        HANDLE_ERROR("Failed to get context");
        return NULL;
    }
#endif

    // Initialize the poll last
    self->poll = poll_new();
    if (self->poll == NULL)
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
        if (self->poll != NULL)
        {
            poll_free(self->poll);
            self->poll = NULL;
        }
        if (self->state != NULL)
        {
            if (self->state->main_thread != NULL)
            {
                DEBUG_PRINT("Freeing main_thread");
                free(self->state->main_thread);
                self->state->main_thread = NULL;
            }
            DEBUG_PRINT("Freeing state");
            free(self->state);
            self->state = NULL;
        }
        DEBUG_PRINT("Freeing async");
        free(self);
    }
}