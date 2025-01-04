/*
 The async is responsible for managing the state of the async function.
*/
#ifndef ASYNC_H
#define ASYNC_H

#include "poll.h"
#include "scheduler.h"

#ifdef _WIN32
#include <windows.h>
#else
#define _XOPEN_SOURCE
#include <sys/ucontext.h>
#include <ucontext.h>  // This is a deprecated POSIX, but it's the only way to get the context on macOS that I can find
#endif

#include <stdbool.h>

// Forward declaration
typedef struct async_state async_state;

struct async_ctx{
    schedular_t *schedular;
    poll_t *poll;
    async_state *state;

    bool is_running;
};

typedef struct async_ctx async_ctx;

struct async
{
    async_ctx *ctx;
    void (*async_run)(struct async_ctx *, async_func_t *);
    void (*await)(struct async_ctx *);
};

typedef struct async async;

// Function declarations
async *async_init();
void async_yield(async_ctx *self_ctx, async_state *self_state);
void async_free(async *self);

#endif