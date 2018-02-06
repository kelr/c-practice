#include <stdio.h> //perror(), printf()
#include <stdlib.h> //exit(), 
#include <sys/types.h> //pid_t, fork()
#include <sys/wait.h> //wait()
#include <unistd.h> //close(), dup2(), execlp(), fork()

// Create the command: ps -elf | grep "/usr" | wc -l

int main(void)
{
    int fd_pipe_1[2];
    int fd_pipe_2[2];
    pid_t parent_wait_pid, pid_fork_1, pid_fork_2, pid_fork_3;

    // Create a pipe
    if (pipe(fd_pipe_1) == -1) 
    {
            perror("Error, pipe 1 unable to be created");
            exit(1);
    }

    // Create the second pipe
    if (pipe(fd_pipe_2) == -1) 
    {
            perror("Error, pipe 2 unable to be created");
            exit(1);
    }

    // Fork the first child
    if ((pid_fork_1 = fork()) < 0) 
    {
        perror("Error in forking child 1");
        exit(1);
    }

    // Child one block
    if (pid_fork_1 == 0) 
    {
        // Close child one's stdout (fd = 1)
        close(1); 

        // Duplicate the write fd of pipe 1, make it stdout
        dup2(fd_pipe_1[1], 1);

        // Close the read fd of pipe 1, because we don't need it
        close(fd_pipe_1[0]);

        // Close pipe 2, we don't need it at all
        close(fd_pipe_2[0]);
        close(fd_pipe_2[1]);

        // Load the ps binary and execute ps -elf with the exec system call
        // Stdout of this command will be sent to the write fd of pipe 1
        if (execlp("ps", "ps", "-elf", NULL) < 0)
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

        if (pid_fork_2 == 0 ) 
        {
            // Close child two's stdin (fd = 0)
            close(0);

            // Duplicate the read fd of pipe 1, make it stdin
            dup2(fd_pipe_1[0], 0);

            // Close the write fd of pipe 1, we don't need it
            close(fd_pipe_1[1]);

            // Close child two's stdout (fd = 1)
            close(1);

            // Duplicate the write fd of pipe 2, make it stdout
            dup2(fd_pipe_2[1], 1);

            // Close the read fd of pipe 2, because we don't need it
            close(fd_pipe_2[0]);

            // Load the grep binary and execute grep. 
            // Stdin of this command will be the read fd of pipe 1
            // Stdout of thie command will be the write fd of pipe 2
            if (execlp("grep", "grep", "/usr", NULL) < 0)
            {
                perror("Error in executing command 'grep \"/usr\"' in child 2");
                exit(0);
            }
        }
        // Parent block post 2nd fork
        else
        {
            // Fork the 3rd child
            if ((pid_fork_3 = fork()) < 0) 
            {
                perror("Error in forking child 3");
                exit(1);
            }

            if (pid_fork_3 == 0) 
            {
                // Close child three's stdin (fd = 0)
                close(0);   

                // Duplicate the read fd of pipe 2, make it stdin
                dup2(fd_pipe_2[0], 0);  

                // Close the write fd of pipe 2, we don't need it
                close(fd_pipe_2[1]);

                // Close pipe 1, we don't need it at all
                close(fd_pipe_1[0]);
                close(fd_pipe_1[1]);

                // Load the wc binary and execute wc. 
                // Stdin of this command will be receieved by the read fd of pipe 2
                if (execlp("wc", "wc", "-l", NULL) < 0) 
                {
                    perror("Error in executing command 'wc -l' in child 3");
                    exit(0);
                }
            }
            // Parent block post 3rd fork
            else
            {
                // The parent does not need any pipe file descriptors as it is not sending or receiving any data
                close(fd_pipe_1[0]); 
                close(fd_pipe_1[1]); 
                close(fd_pipe_2[0]);
                close(fd_pipe_2[1]);

                int status;

                // Parent waits for the children to complete
                for(int i = 0; i < 3; i++) 
                {
                    parent_wait_pid = wait(&status);
                    printf("Parent: Child %d completed with status %d\n", parent_wait_pid, status);
                }
            }   
        }
    }
    // Parent return
    return 0;
}
