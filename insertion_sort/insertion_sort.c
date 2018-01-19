#include "insertion_sort.h"

void insertion_sort(int *input, size_t size)
{
    unsigned int basic_op_count = 0;
    // Worst case performance
    unsigned int worst = (size*(size-1))/2;
    visualize(input, size);
    // For each element in the array except the first
    for (int i = 1; i < size; i++)
    {
        // For each element starting from the current index in the outer loop
        for (int j = i; j > 0; j--)
        {
            basic_op_count++;
            // Compare the current element with the one before it, exchange places if the one before it is larger
            if (input[j] < input[j-1])
            {
                printf("Exchanging %d and %d\n\n", input[j-1], input[j]);
                int temp = input[j];
                input[j] = input[j-1];
                input[j-1] = temp;
                visualize(input, size);
            }
            // If it's not larger, we don't need to retest everything before what was already tested
            else
            {
                break;
            }
        }
    }
    printf("%d basic operations performed for input size %d. Worst case: %d\n", basic_op_count, size, worst);
}

// Print out an array with nice pretty brackets around it
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