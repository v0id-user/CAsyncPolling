/*
 The async is responsible for managing the state of the async function and the event loop.
*/
#ifndef ASYNC_H
#define ASYNC_H

#include "poll.h"

typedef struct async_state async_state; 

struct async {
    poll_t* poll;
    async_state* state;
};


typedef struct async async;

async* async_init();
async* await(async* self,function f);
async* async_yeild(async* self);
void async_free(async* self);

#endif