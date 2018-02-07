#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

// Adapted from: http://www.cs.binghamton.edu/~huilu/examples/shm_attach.c

// Make sure you compile and run shm_create.c first
int main(int argc, char *argv[])
{
    key_t key = 0;
    int shmid = 0;
    char *data;

    // Make the key from key_file and the id
    if ((key = ftok("key_file", 'X')) == -1) 
    {
        perror("Error executing ftok");
        exit(1);
    }

    // Connect to the shared memory segment
    //There's no IPC_CREATE, otherwise we would make another shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) 
    {
        perror("Error executing shmget");
        exit(1);
    }

    //Attach to the shared memory segment to get a pointer to it
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("Error executing shmat");
        exit(1);
    }

    // Read or write to the segment depending on command line input
    if (argc == 2) 
    {
        printf("writing to segment: \"%s\"\n", argv[1]);
        strncpy(data, argv[1], SHM_SIZE);
    } 
    else
    {
        printf("segment contains: \"%s\"\n", data);
    }

    // Detach from the segment
    if (shmdt(data) == -1) 
    {
        perror("Error executing shmdt");
        exit(1);
    }

    return 0;
}
