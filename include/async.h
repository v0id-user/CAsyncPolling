/*
 The async is responsible for managing the state of the async function.
*/
#ifndef ASYNC_H
#define ASYNC_H

#include "poll.h"

#ifdef _WIN32
#include <windows.h>
#else
#define _XOPEN_SOURCE
#include <sys/ucontext.h>
#include <ucontext.h>  // This is a deprecated POSIX, but it's the only way to get the context on macOS that I can find
#endif

typedef struct async_state async_state;


struct async_ctx{
    poll_t *poll;
    async_state *state;
};

typedef struct async_ctx async_ctx;

struct async
{
    async_ctx *ctx;
    void (*async_wait)(struct async *);
    void (*async_yield)(struct async *);
};

typedef struct async async;

// Function declarations
async *async_init();
void async_wait(async *self);
async *await(async *self, function f);
void async_free(async *self);

#endif