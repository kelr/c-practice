#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];
    for (int i=0; i < 10; i++)
    {
        sleep(1);
        printf("%s\n", str);
    }
    return 0;
}