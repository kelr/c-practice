#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

volatile int count = 0;
int loops;

void *worker(void *arg)
{
    // No locking of the critical section on purpose
    for (int i = 0; i < loops; i++)
    {
        count++;
    }
}

// Give this an initial value of 1000000000
// Doubles the input value with 2 threads
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }

    loops = atoi(argv[1]);

    pthread_t thread_1, thread_2;

    printf("Initial value : %d\n", count);

    pthread_create(&thread_1, NULL, worker, NULL);
    pthread_create(&thread_2, NULL, worker, NULL);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("Final value : %d\n", count);
    return 0;
}