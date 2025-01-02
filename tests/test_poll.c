#include <stdio.h>
#include <assert.h>
#include "poll.h"

static void test_poll_create() {
    // Basic test to ensure poll creation works
    poll_t *poll = poll_new();
    assert(poll != NULL);
    poll_free(poll);
    printf("test_poll_create: PASS\n");
}

int main(int argc, char **argv) {
    printf("Running poll tests...\n");
    
    test_poll_create();
    
    printf("All tests passed!\n");
    return 0;
} 