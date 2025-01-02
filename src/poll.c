#include "poll.h"
#include "pprint.h"
#include <stdlib.h>

static struct poll_ctx *expand_poll_ctx(struct poll_ctx *self_ctx)
{
    if (self_ctx->size >= self_ctx->capacity)
    {
        self_ctx->capacity *= 2;
        self_ctx->functions = (func_t *)realloc(self_ctx->functions, sizeof(func_t) * self_ctx->capacity);
    }
    else
    {
        DEBUG_PRINT("Poll capacity is not full");
    }

    return self_ctx;
}

static void chain(struct poll_ctx *self_ctx, function f, void *arg)
{
    // TODO: Implement chain functionality
    DEBUG_PRINT("CHAIN: %p", f);
}

static void poll_wait(struct poll *self)
{
    // TODO: Implement wait functionality
}

poll_t *poll_new()
{
    DEBUG_PRINT("Allocating memory for poll");
    poll_t *self = (poll_t *)malloc(sizeof(poll_t));
    if (self == NULL)
    {
        HANDLE_ERROR("Failed to allocate memory for poll");
    }
    DEBUG_PRINT("Allocated memory for poll");
    self->ctx = (struct poll_ctx *)malloc(sizeof(struct poll_ctx));
    if (self->ctx == NULL)
    {
        free(self);
        HANDLE_ERROR("Failed to allocate memory for poll_ctx");
    }
    DEBUG_PRINT("Allocated memory for poll_ctx");
    self->ctx->functions = (func_t *)malloc(sizeof(func_t) * DEFAULT_POLL_CAPACITY);
    if (self->ctx->functions == NULL)
    {
        free(self->ctx);
        free(self);
        HANDLE_ERROR("Failed to allocate memory for functions");
    }
    DEBUG_PRINT("Allocated memory for functions");
    self->ctx->size     = 0;
    self->ctx->capacity = DEFAULT_POLL_CAPACITY;
    self->ctx->index    = 0;
    self->chain         = chain;
    self->wait          = poll_wait;
    DEBUG_PRINT("Returning poll %p", self);
    return self;
}

void poll_free(poll_t *poll)
{
    if (poll != NULL)
    {
        if (poll->ctx != NULL)
        {
            if (poll->ctx->functions != NULL)
            {
                free(poll->ctx->functions);
            }
            free(poll->ctx);
        }
        free(poll);
    }
}