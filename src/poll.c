#include "poll.h"
#include "pprint.h"
#include <stdlib.h>

static void chain(struct poll* self, function f) {
    // TODO: Implement chain functionality
}

static void poll_wait(struct poll* self) {
    // TODO: Implement wait functionality
}

poll_t* poll_new() {
    poll_t* self = (poll_t*)malloc(sizeof(poll_t));
    if (self == NULL) 
    {
        HANDLE_ERROR("Failed to allocate memory for poll");
    }
    
    self->ctx = (struct poll_ctx*)malloc(sizeof(struct poll_ctx));
    if (self->ctx == NULL) 
    {
        free(self);
        HANDLE_ERROR("Failed to allocate memory for poll_ctx");
    }

    self->ctx->functions = (func_t*)malloc(sizeof(func_t)*DEFAULT_POLL_CAPACITY);
    if (self->ctx->functions == NULL) 
    {
        free(self->ctx);
        free(self);
        HANDLE_ERROR("Failed to allocate memory for functions");
    }
    
    self->ctx->size = 0;
    self->ctx->capacity = DEFAULT_POLL_CAPACITY;
    self->ctx->index = 0;
    self->chain = chain;
    self->wait = poll_wait;
    return self;
}

void poll_free(poll_t* poll) {
    if (poll != NULL) {
        if (poll->ctx != NULL) {
            if (poll->ctx->functions != NULL) {
                free(poll->ctx->functions);
            }
            free(poll->ctx);
        }
        free(poll);
    }
}