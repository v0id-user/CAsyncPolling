#include "async.h"
#include "utils.h"

#include <stdbool.h>

// Internal state of the functions
struct async_state{

    POINTER main_thread;
    bool is_running;
};

async* async_init(){
    async* self = (async*)malloc(sizeof(async));
    self->poll = poll_new();
    self->state = (async_state*)malloc(sizeof(async_state));
    return self;
}