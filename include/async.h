/*
 The async is responsible for managing the state of the async function.
*/
#ifndef ASYNC_H
#define ASYNC_H

#include "poll.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <ucontext.h>
#endif

typedef struct async_state async_state; 

struct async {
    poll_t* poll;
    async_state* state;
    void (*wait)(struct async*);
};


typedef struct async async;

async* async_init();
async* await(async* self,function f);
async* yeild(async* self);
void async_free(async* self);

#endif