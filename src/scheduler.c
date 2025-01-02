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

void schedular_free(schedular_t *schedular){
    if (schedular != NULL)
    {
        free(schedular);
        schedular = NULL;
    }
}
