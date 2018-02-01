#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

// Adapted from http://www.cs.binghamton.edu/~huilu/examples/pipe1.c

int main()
{
    int pipe_file_descriptors[2];
    char buf[30];
    pid_t pid;

    // Use the pipe() system call to create a pipe
    if (pipe(pipe_file_descriptors) == -1) 
    {
        perror("Error in creating pipe");
        exit(1);
    }

    // Fork this process to create a child process
    if ( (pid = fork()) < 0) 
    {
        perror("Error in forking process");
        exit(1);
    }

    // Child process block
    if ( pid == 0 ) 
    {

        printf("Child: writing to the pipe\n");

        // Close the read part of the pipe in the child process scope
        close(pipe_file_descriptors[0]);

        // Write Hello to the parent through the pipe
        if (write(pipe_file_descriptors[1], "Hello", 6) <= 0) 
        {
            perror("Error in writing to the pipe in child");
            exit(1);
        }

        printf("Child: exiting\n");
        exit(0);
    } 
    // Parent process block
    else 
    {
        printf("Parent: reading from pipe\n");

        // Close the write part of the pipe in the parent process scope
        close(pipe_file_descriptors[1]);

        // Read the message from the child
        if (read(pipe_file_descriptors[0], buf, 6) <= 0 ) 
        {
            perror("Error in reading the pipe in parent");
            exit(1);
        }

        printf("Parent read: \"%s\"\n", buf);

        // Wait for the child process to finish
        wait(NULL);
    }
}
