#include "pprint.h"
#include "async.h"
#include <assert.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void test_function(async_state *state, void *arg){
    DEBUG_PRINT("TEST FUNCTION: %s\n", (char *)arg);
    DEBUG_PRINT("STATE PTR: %p\n", (void *)state);
    for (int i = 0; i < 10; i++) {
        // Mimic a long running function
        Sleep(10); // Sleep for 10 ms because the scheduler is 25ms
        async_yield(state);
    }
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
    async_func_t async_test_function1 = {
        .self = NULL,  // Will be set by the async system
        .id = 0,       // Will be set by the async system
        .f = test_function,
        .arg = "Hello, World!"
    };

    async_func_t async_test_function2 = {
        .self = NULL,  // Will be set by the async system
        .id = 0,       // Will be set by the async system
        .f = test_function,
        .arg = "Hello, World!"
    };


    // Run same function twice to test if it can be run again
    asyn->async_run(asyn->ctx, &async_test_function1);
    asyn->async_run(asyn->ctx, &async_test_function2);

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