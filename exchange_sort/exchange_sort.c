#include "exchange_sort.h"

void exchange_sort(int *input, size_t size)
{
    unsigned int basic_op_count = 0;
    unsigned int worst = (size*(size-1))/2;
    visualize(input, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            printf("Test %d and %d\n", input[j], input[i]);
            basic_op_count++;
            if (input[j] < input[i])
            {
                printf("Exchanging %d and %d\n\n", input[j], input[i]);
                int temp = input[i];
                input[i] = input[j];
                input[j] = temp;
                visualize(input, size);
            }
        }
    }
    printf("%d basic operations performed for input size %d. Expected: %d\n", basic_op_count, size, worst);
}

void visualize(int *input, size_t size)
{  
    printf("[");
    for (int i = 0; i < size; i++)
    {
        if (i != size-1)
        {
            printf("%d, ", input[i]);
        }
        else
        {
            printf("%d", input[i]);
        }
    }
    printf("]\n");
}

int main(void)
{
    int snacks[10] = {5, 2, 8, 34, 8, 2, 4, 89, -10, 11};
    size_t size = sizeof(snacks) / sizeof(snacks[0]);
    int *p_snacks = snacks;

    exchange_sort(p_snacks, size);
    visualize(p_snacks, size);
}