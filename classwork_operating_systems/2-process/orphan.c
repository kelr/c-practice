#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();
    if (pid < 0) 
    {
        fprintf(stderr, "fork failed\n");
        return 1;
    }

    if (pid == 0) 
    {
        printf("Child pid = %d\n Don't forget to kill -9 the child\n", getpid());
        // Infinite loop for the child
        while(1);
    }

    printf("parent exits\n");
    return 0;
}