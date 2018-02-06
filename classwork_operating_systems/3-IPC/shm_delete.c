#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

// Adapted from: http://www.cs.binghamton.edu/~huilu/examples/shm_delete.c

int main(void)
{
      key_t key;
      int shmid;

      /* make the key: */
      if ((key = ftok("test_shm", 'X')) == -1) 
      {
           perror("ftok");
           exit(1);
      }

      /* connect to memory segment: */
      if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) 
      {
           perror("shmget");
           exit(1);
      }

      /* delete he segment */
      if( shmctl(shmid, IPC_RMID, NULL) == -1) 
      {
           perror("shmctl");
           exit(1);
      }

      return 0;
}