#include "scheduler.h"
#include "pprint.h"
schedular_t *schedular_new(){
    schedular_t *schedular = (schedular_t *)malloc(sizeof(schedular_t));
    if (schedular == NULL)
    {
        HANDLE_ERROR("Failed to allocate memory for schedular");
        return NULL;
    }
    return schedular;
}