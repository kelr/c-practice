#include "stdlib.h"
#include "stdio.h"

unsigned long long factorial(unsigned long long n);
unsigned long long *fib(unsigned long long n);

// n-1 operations, but actually exponential when using the formal def
// n >= 2^(2-1) where s = floor(lg (n)) + 1
unsigned long long factorial(unsigned long long n)
{
    unsigned long long result = 1;
    for (unsigned long long i = 1; i < n; i++)
        result *= i;
    return result;
}

// n-1 operations, but actually exponential when using the formal def
// n >= 2^(2-1) where s = floor(lg (n)) + 1
unsigned long long *fib(unsigned long long n)
{
    unsigned long long *fib_list = malloc(sizeof(unsigned long long) * n);
    if (n < 2)
    {
        return fib_list;
    }
    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long next = 0;

    for (unsigned long long i=1; i < n; i++)
    {
        fib_list[i-1] = a;
        next = a + b;
        b = a;
        a = next;
    }
    return fib_list;
}

int main(void)
{

    unsigned long long fact = factorial(100);
    printf("%u\n\n", fact);

    unsigned long long fib_sz = 50;
    unsigned long long *list = fib(fib_sz);
    for (unsigned long long i=0; i < fib_sz-1; i++)
    {
        printf("%u\n", list[i]);
    }
    return 0;
}