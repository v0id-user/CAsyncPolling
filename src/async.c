#include "async.h"
#include "poll.h"
#include "pprint.h"
#include "async_func.h" 

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Internal state of the functions
struct async_state
{
    int32_t current_function_index;
    CONTEXT_POINTER async_addr;
    CONTEXT_POINTER main_thread;
#ifndef _WIN32
    char stack[60*1024]; // 60kb stack required for ucontext.h
#endif
    bool is_running;
    bool is_done;
    async_func_t *self_func;
};

struct async_args
{
    async_ctx *self_ctx;
    async_state *self_state;
    void *arg;
};

static void async_start(struct async_args *self_args)
{
    DEBUG_PRINT("Starting async function %p", self_args->self_state->self_func->f);
    self_args->self_state->is_running = true;
    self_args->self_state->is_done = false;
    
    DEBUG_PRINT("Running function %p", self_args->self_state->self_func->f);

    // Run the function
    DEBUG_PRINT("CONTEXT: %p", self_args->self_ctx);
    DEBUG_PRINT("STATE: %p", self_args->self_state);
    DEBUG_PRINT("ARG: %p", self_args->arg);
    self_args->self_state->self_func->f(self_args->self_ctx, self_args->self_state, self_args->arg);

    // Mark the function as done
    self_args->self_state->is_done = true;
    DEBUG_PRINT("Function done %p", self_args->self_state->self_func->f);
    // TODO: Clean up the context

    free(self_args);
}

static void async_run_internal(async_ctx *self_ctx, async_state *state)
{

    // We run the function and assume, it will yeild as normal async programs do.
    // > I'm lazy to make a timeout mechanism ;P

    // Async args which is all the arguments we need to pass to the function
    struct async_args* args = malloc(sizeof(struct async_args));
    args->self_ctx = self_ctx;
    args->self_state = state;
    args->arg = state->self_func->arg;

    #ifdef _WIN32
        DEBUG_PRINT("Creating fiber");
        state->async_addr = CreateFiber(0, async_start, (LPVOID)args);
        DEBUG_PRINT("Fiber created");
        // Chain the async_state in the poll
        DEBUG_PRINT("Chaining async_state in poll");
        self_ctx->poll->chain(self_ctx->poll->ctx, state);
        state->current_function_index = self_ctx
                                                ->poll
                                                ->ctx
                                                ->index;
    #else
    #endif
}

static void async_run(async_ctx *self_ctx, async_func_t *f)
{
    // Chain in the poll
    if (self_ctx->poll == NULL)
    {
        HANDLE_ERROR("ASYNC_RUN: Poll is NULL");
    }

    // Create new state object for the function
    async_state *self_state = malloc(sizeof(async_state));
    if (self_state == NULL)
    {
        HANDLE_ERROR("Failed to allocate memory for async_state");
    }

    // Copy the state
    memcpy(self_state, self_ctx->state, sizeof(async_state));

    // Set the function and context
    self_state->self_func = f;

    // Run the function
    async_run_internal(self_ctx, self_state);
}


static void async_await(async_ctx *self_ctx)
{
    DEBUG_PRINT("Awaiting");
    if (self_ctx->poll == NULL)
    {
        HANDLE_ERROR("ASYNC_AWAIT: Poll is NULL");
    }

    if (self_ctx->poll->ctx->count == 0)
    {
        HANDLE_ERROR("ASYNC_AWAIT: No contexts to run");
    }

    bool all_done = false;
    // Event loop
    int number_of_dones = 0;

    do {
        // Start running from the poll
        for (struct async_state *state = self_ctx->poll->next_context(self_ctx->poll->ctx); state != NULL; state = self_ctx->poll->next_context(self_ctx->poll->ctx))
        {
            DEBUG_PRINT("Main event loop: Running state %d", state->current_function_index);
            DEBUG_PRINT("Main event loop: Is running: %d", state->is_running);
            DEBUG_PRINT("Main event loop: Is done: %d", state->is_done);
            if (number_of_dones >= self_ctx->poll->ctx->count) {
                all_done = true;
                break;
            }
            if (!state->is_done)
            {
                DEBUG_PRINT("Main event loop: Switching to state %d", state->current_function_index);
                DEBUG_PRINT("Main event loop: Switching to context %p", state->async_addr);
                all_done = false;
                self_ctx->schedular = schedule(self_ctx->schedular);
                SwitchToFiber(state->async_addr);
                DEBUG_PRINT("Main event loop: Switched to state %d", state->current_function_index);
            }else{
                DEBUG_PRINT("Main event loop: State %d is done", state->current_function_index);
                number_of_dones++;
            }
            DEBUG_PRINT("Main event loop: Swtich to next context");
        }
    } while (!all_done);

    DEBUG_PRINT("Main event loop: All done");
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
    self->ctx->schedular = NULL;
    self->ctx->state->main_thread = NULL;
    self->ctx->state->is_running = false;
    self->ctx->state->is_done = false;
    self->ctx->state->current_function_index = 0;

    self->ctx->schedular = schedular_new();
    if (self->ctx->schedular == NULL)
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

    // Set function pointers
    self->async_run = async_run;
    self->await = async_await;
    self->ctx->is_running = false;
    DEBUG_PRINT("Async initialization complete");
    return self;
}

void async_yield(async_ctx *self_ctx, async_state *self_state){

    DEBUG_PRINT("Yielding");
    DEBUG_PRINT("Current function index: %d\n", self_state->current_function_index);
    DEBUG_PRINT("Is running: %d\n", self_state->is_running);
    DEBUG_PRINT("Current function: %p\n", self_state->self_func);
    DEBUG_PRINT("Current schedular: %p\n", self_ctx->schedular);
    DEBUG_PRINT("Current schedular tick: %lld\n", self_ctx->schedular->tick);

    // Check if the time has passed
    if (!self_ctx->schedular->did_time_pass(self_ctx->schedular))
    {
        DEBUG_PRINT("Tick has not passed, we can't change execution context");
        return;
    }
    
    DEBUG_PRINT("Tick has passed, we can change execution context");

    // Swtich to the main thread as it's will be in an event loop
    // that iterates over the poll and switches to the next context
    SwitchToFiber(self_state->main_thread);
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
        if (self->ctx->schedular != NULL) {
            schedular_free(self->ctx->schedular);
            self->ctx->schedular = NULL;
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