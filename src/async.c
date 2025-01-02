#include "async.h"
#include "pprint.h"
#include "poll.h"

#include <stdbool.h>

// Internal state of the functions
struct async_state{
    CONTEXT_POINTER main_thread;
    bool is_running;
};

void async_wait(async* self){
    self->poll->wait(self->poll);
}

async* async_init(){
    async* self = (async*)malloc(sizeof(async));
    if (self == NULL) 
    {
        HANDLE_ERROR("Failed to allocate memory for async");
    }
    self->poll = poll_new();
    self->state = (async_state*)malloc(sizeof(async_state));
    if (self->state == NULL) 
    {
        free(self);
        HANDLE_ERROR("Failed to allocate memory for async_state");
    }

    // Converting the main thread to a fiber so we can return to it
    #ifdef _WIN32
    self->state->main_thread = ConvertThreadToFiber(NULL);
    #else
    self->state->main_thread = malloc(sizeof(ucontext_t));
    int r = getcontext(self->state->main_thread);
    if (r != 0) {
        HANDLE_ERROR("Failed to get context");
    }
    #endif
    return self;
}