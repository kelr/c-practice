#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    int ret = 0;

    int status = 0;

    // Fork failure if ret val < 0
    if (pid == 0) 
    {
        // Child execs another program image
        // This will fail because I don't have a printer nor do I have a file called myfile
        ret = execlp("lpr", "lpr", "myfile", (char *) 0);
    }

    if ( ret == -1 )
    {
        fprintf(stderr, "exec failed\n");
    }
    else 
    {

    //in the parent, check for completion of child
    waitpid(pid, &status, 0);

    //Alternatively ==> while (wait(&status) != pid);

    unlink("myfile");

    return 0;
    } 
}