#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

// Adapted from http://www.cs.binghamton.edu/~huilu/examples/exec_ex.c

int main(void)
{
    pid_t pid = fork();

    // Fork failure if ret val < 0
    if (pid < 0) 
    { 
        fprintf(stderr, "fork failed\n"); 
        return 1;
    } 

    if (pid == 0) 
    {   
        // Child does its own thing
        if (execlp("echo", "echo", "Hello from the child", (char *) NULL) == -1)
        {
            fprintf(stderr, "execl failed\n"); 
        }
        // We shouldn't be here
        return 2;
    } 

    // The parent goes here
    printf("parent sleeps for 5 seconds\n"); 
    sleep(5);
    printf("parent carries on\n"); 
}