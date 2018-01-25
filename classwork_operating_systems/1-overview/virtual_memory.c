#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

int main(void)
{
    int *p_int = malloc(sizeof(int));
    assert(p_int != NULL);
    // Running two instances of this program allocates seemingly the same memory address
    printf("%d memory addr stored in p_int: %08x\n", getpid(), (unsigned)p_int);

    *p_int = 0;
    while(1)
    {
        sleep(1);
        *p_int = *p_int + 1;
        printf("%d p_int: %d\n", getpid(), *p_int);
        break;
    }
    return 0;
}