#include "poll.h"
#include "pprint.h"
#include <stdlib.h>

static struct poll_ctx *expand_poll_ctx(struct poll_ctx *self_ctx)
{
    DEBUG_PRINT("Expanding poll context");
    if (self_ctx->count >= (self_ctx->capacity / sizeof(void*)))
    {
        DEBUG_PRINT("Poll capacity is full");
        self_ctx->capacity *= 2;
        self_ctx->contexts = (void**)realloc(self_ctx->contexts, self_ctx->capacity);
        if (self_ctx->contexts == NULL) {
            HANDLE_ERROR("Failed to reallocate memory for poll contexts");
        }
        DEBUG_PRINT("Poll capacity: %d", self_ctx->capacity);
    }
    return self_ctx;
}

static struct poll_ctx *add_poll_ctx(struct poll_ctx *self_ctx, void* context)
{
    DEBUG_PRINT("Adding poll context");
    self_ctx = expand_poll_ctx(self_ctx);
    DEBUG_PRINT("Poll context added %p", context);
    self_ctx->contexts[self_ctx->count] = context;
    DEBUG_PRINT("Poll context added at index %d", self_ctx->count);
    self_ctx->size = (self_ctx->count + 1) * sizeof(void*);
    DEBUG_PRINT("Poll size: %d", self_ctx->size);
    self_ctx->count++;
    DEBUG_PRINT("Poll count: %d", self_ctx->count);
    return self_ctx;
}

static void* get_next_poll_ctx(struct poll_ctx *self_ctx)
{
    DEBUG_PRINT("Getting next poll context");
    DEBUG_PRINT("Poll index: %d", self_ctx->index);
    DEBUG_PRINT("Poll count: %d", self_ctx->count);
    if (self_ctx->index >= self_ctx->count)
    {
        // Just reset the index to 0
        self_ctx->index = 0;
        DEBUG_PRINT("Resetting poll index to 0");
    }
    DEBUG_PRINT("Incrementing poll index");
    void* context = self_ctx->contexts[self_ctx->index];
    self_ctx->index++;
    
    DEBUG_PRINT("Returning poll context %p", context);
    return context;
}

static void chain(struct poll_ctx *self_ctx, void* context)
{
    self_ctx = add_poll_ctx(self_ctx, context);
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
    self->ctx->contexts = (CONTEXT_POINTER *)malloc(DEFAULT_POLL_CAPACITY);
    if (self->ctx->contexts == NULL)
    {
        free(self->ctx);
        free(self);
        HANDLE_ERROR("Failed to allocate memory for functions");
    }
    DEBUG_PRINT("Allocated memory for functions");
    self->ctx->size     = 0;
    self->ctx->capacity = DEFAULT_POLL_CAPACITY;
    self->ctx->index    = 0;
    self->ctx->count    = 0;
    self->chain         = chain;
    self->next_context  = get_next_poll_ctx;
    DEBUG_PRINT("Returning poll %p", self);
    return self;
}

void poll_free(poll_t *poll)
{
    if (poll == NULL)
    {
        return;
    }

    if (poll->ctx == NULL)
    {
        free(poll);
        return;
    }

    if (poll->ctx->contexts != NULL)
    {
        free(poll->ctx->contexts);
    }

    free(poll->ctx);
    free(poll);
}