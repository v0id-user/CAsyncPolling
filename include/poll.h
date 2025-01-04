/*
 The poll is responsible for containing the functions that are
 to be executed and chaining them together.
*/
#ifndef POLL_H
#define POLL_H


#include "async_func.h"
#include "utils.h"

#include <stdint.h>
#include <stdbool.h>

#define DEFAULT_POLL_CAPACITY sizeof(void*) * 10

struct poll_ctx
{
    // function contexts (for windows it's fiber in unix it's ucontext)
    CONTEXT_POINTER *contexts;
    int32_t size;
    int32_t capacity;
    int32_t index;
    int32_t count;
    bool is_running;
};

struct poll
{
    struct poll_ctx *ctx;
    void (*chain)(struct poll_ctx *, void* );
    void* (*next_context)(struct poll_ctx *);
};

typedef struct poll poll_t;

poll_t *poll_new();
void poll_free(poll_t *poll);

#endif