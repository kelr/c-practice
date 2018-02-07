#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

// Adapted from: http://www.cs.binghamton.edu/~huilu/examples/shm_delete.c

// Make sure you compile and run shm_create.c first
int main(void)
{
    key_t key = 0;
    int shmid = 0;

    // Make the key from key_file and the id
    if ((key = ftok("key_file", 'X')) == -1) 
    {
         perror("Error executing ftok");
         exit(1);
    }

    // Connect to the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) 
    {
         perror("Error executing shmget");
         exit(1);
    }

    // Delete the shared memory segment
    if( shmctl(shmid, IPC_RMID, NULL) == -1) 
    {
         perror("Error executing shmctl");
         exit(1);
    }

    return 0;
}