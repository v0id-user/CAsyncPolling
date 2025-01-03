#include "scheduler.h"
#include "pprint.h"

// This is just a design choice, we could have used a function it self to the did_time_pass function
static bool did_time_pass(void *self){
    return time(NULL) - ((schedular_t *)self)->tick > SCHEDULER_TICK_MS;
}

schedular_t *schedular_new(){
    schedular_t *schedular = (schedular_t *)malloc(sizeof(schedular_t));
    if (schedular == NULL)
    {
        HANDLE_ERROR("Failed to allocate memory for schedular");
        return NULL;
    }
    schedular->did_time_pass = did_time_pass;
    return schedular;
}

schedular_t *schedule(schedular_t *self){
    self->tick = time(NULL);
    return self;
}

void schedular_free(schedular_t *schedular){
    if (schedular != NULL)
    {
        free(schedular);
        schedular = NULL;
    }
}
