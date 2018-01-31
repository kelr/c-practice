#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Allocated in the data segment
static int idata = 111; 

int main(void)
{
    // Allocated on the stack
    int istack = 222; 

    pid_t childPid = fork();
    // If an error occured, panic
    if (childPid == -1) 
    {
        return -1;
    }
    else if (childPid == 0) 
    {
        // Child process modifies the data
        idata *= 3; istack *= 3; 
    } 
    else 
    {
        // Parent process is here. Sleep to let the child execute
        sleep(3);
    } 
    
    // Both processes print out their data
    printf("PID=%ld %s idata=%d istack=%d\n",
         (long)getpid(), (childPid == 0) ? "(child) " : "(parent)", idata, istack);
    
    return 0;
}

