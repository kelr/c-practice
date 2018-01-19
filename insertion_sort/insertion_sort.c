#include "insertion_sort.h"

void insertion_sort(int *input, size_t size)
{
    unsigned int basic_op_count = 0;
    unsigned int worst = (size*(size-1))/2;
    visualize(input, size);
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 1; j--)
        {
            basic_op_count++;
            if (input[j] < input[j-1])
            {
                printf("Exchanging %d and %d\n\n", input[j-1], input[j]);
                int temp = input[j];
                input[j] = input[j-1];
                input[j-1] = temp;
                visualize(input, size);
            }
            else
            {
                break;
            }
        }
    }
    printf("%d basic operations performed for input size %d. Worst case: %d\n", basic_op_count, size, worst);
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

    insertion_sort(p_snacks, size);
    visualize(p_snacks, size);
}