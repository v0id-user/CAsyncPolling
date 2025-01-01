#include "poll.h"


static void chain(poll_t self,function f){
}

static void wait(poll_t self){

}

poll_t* poll_new(){
    poll_t* self = (poll_t*)malloc(sizeof(poll_t));
    self->ctx = (struct poll_ctx*)malloc(sizeof(struct poll_ctx));
    self->ctx->functions = (function*)malloc(sizeof(function)*DEFAULT_POLL_CAPACITY);
    self->ctx->size = 0;
    self->ctx->capacity = DEFAULT_POLL_CAPACITY;
    self->ctx->index = 0;
    self->chain = chain;
    self->wait = wait;
    return self;
}