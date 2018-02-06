#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

// Adapted from http://www.cs.binghamton.edu/~huilu/examples/shm_create.c

int main(void)
{
    //Make the key from file test_shm
    if ((key_t key = ftok("test_shm", 'X')) < 0) 
    {
        perror("ftok command failed");
        exit(1);
    }

    // Create the shared memory segment
    if ((int shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT | IPC_EXCL )) < 0) 
    {
        perror("shmget command failed");
        exit(1);
    }

    return 0;
}