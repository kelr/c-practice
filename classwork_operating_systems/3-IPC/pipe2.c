#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Adapted from http://www.cs.binghamton.edu/~huilu/examples/pipe2.c

int main()
{
    int file_descriptors[2];
    pid_t pid, pid_fork_1, pid_fork_2;

    // Create a pipe
    if (pipe(file_descriptors) == -1) 
    {
            perror("Error, pipe unable to be created");
            exit(1);
    }

    // Fork the first child
    if ((pid_fork_1 = fork()) < 0) 
    {
        perror("Error in forking child 1");
        exit(1);
    }

    // Child one block
    if ( pid_fork_1 == 0 ) 
    {
        // Close child one's stdout (fd = 1)
        close(1); 

        // Duplicate the write fd of the pipe, make it stdout
        dup2(file_descriptors[1], 1);

        // Close the read fd of the pipe, because we don't need it
        close(file_descriptors[0]);

        // Load the ps binary and execute ps -elf with the exec system call
        // Stdout of this command will be sent to the write fd of the pipe
        if (execlp("ps", "ps", "-elf", (char *) 0) < 0) 
        {
            perror("Error in executing command 'ps -elf' in child 1");
            exit(0);
        }
    }
    // Parent block post 1st fork
    else
    {
        // Fork the second child
        if ((pid_fork_2 = fork()) < 0) 
        {
            perror("Error in forking child 2");
            exit(1);
        }

        if ( pid_fork_2 == 0 ) 
        {
            // Close child two's stdin (fd = 0)
            close(0);   

            // Duplicate the read fd of the pipe, make it stdin
            dup2(file_descriptors[0],0);  

            // Close the write fd of the pipe, we don't need it
            close(file_descriptors[1]);

            // Load the less binary and execute less. 
            // Stdin of this command will be receieved by the read fd of the pipe
            if( execlp("less", "less", (char *) 0) < 0) 
            {
                perror("Error in executing command 'less' in child 2");
                exit(0);
            }
        }
        // Parent block post 2nd fork
        else
        {
            // The parent does not need any pipe file descriptors as it is not sending or receiving any data
            close(file_descriptors[0]); 
            close(file_descriptors[1]); 

            int status;

            // Parent waits for the children to complete
            for(int i=0; i<2; i++) 
            {
                pid = wait(&status);
                printf("Parent: Child %d completed with status %d\n", pid, status);
            }
        }
    }
}
