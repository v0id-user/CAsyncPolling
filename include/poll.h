/*
 The poll is responsible for containing the functions that are 
 to be executed and chaining them together.
*/
#ifndef POLL_H
#define POLL_H

#define DEFAULT_POLL_CAPACITY 10

typedef void (*function)(void*);


struct poll_ctx{
    function* functions;
    int size;
    int capacity;
    int index;
};

struct poll{
    struct poll_ctx* ctx;
    void (*chain)(struct poll*,function);
    void (*wait)(struct poll*);
};


typedef struct poll poll_t;

poll_t* poll_new();
void poll_free(poll_t* poll);

#endif