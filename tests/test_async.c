#include "async.h"
#include <assert.h>
#include <stdio.h>

void test_function(void *ctx, void *arg){
    printf("TEST FUNCTION: %s\n", (char *)arg);
}

static void test_async_create()
{
    printf("Testing async creation...\n");
    
    // Basic test to ensure poll creation works
    async *asyn = async_init();
    if (asyn == NULL) {
        printf("FAIL: async_init returned NULL\n");
        return;
    }
    
    assert(asyn != NULL);
    assert(asyn->ctx != NULL);
    assert(asyn->ctx->state != NULL);
    assert(asyn->ctx->poll != NULL);
    assert(asyn->async_run != NULL);

    // Create async_func_t structure
    async_func_t async_func = {
        .self = NULL,  // Will be set by the async system
        .id = 0,       // Will be set by the async system
        .f = test_function,
        .arg = "Hello, World!"
    };


    asyn->async_run(asyn->ctx, &async_func);

    // Cleanup
    async_free(asyn);
    printf("test_async_create: PASS\n");
}

int main(int argc, char **argv)
{
    printf("Running async tests...\n");

    test_async_create();

    printf("All tests passed!\n");
    return 0;
}