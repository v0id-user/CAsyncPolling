/*
 The scheduler is responsible for managing the event loop.
*/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>
#include <time.h>

#define SCHEDULER_TICK_MS 25

struct schedular
{
    time_t tick;
    bool (*did_time_pass)(void *);
};

typedef struct schedular schedular_t;

schedular_t *schedular_new();
schedular_t *schedule(schedular_t *self);
void schedular_free(schedular_t *schedular);

#endif