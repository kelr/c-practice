#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void merge(int* input_one, int* input_two, const size_t size_one, const size_t size_two, int* output);
void merge_sort(int* input, size_t size);


void merge(int* input_one, int* input_two, const size_t size_one, const size_t size_two, int* output)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size_one && j < size_two)
    {
        // Add the smaller one to the output array
        if (input_one[i] < input_two[j])
        {
            output[k] = input_one[i];
            i++;
        }
        // If they're the same use the 2nd one I guess
        else
        {
            output[k] = input_two[j];
            j++;
        }
        k++;
    }
    // If the first array index goes out of bounds, copy the rest of the second array
    if (i >= size_one)
    {
        for (;j < size_two; j++)
        {
            output[k] = input_two[j];
            k++;
        }
    }
    // Copy the first array instead
    else if (j >= size_two)
    {
        for (;i < size_one; i++)
        {
            output[k] = input_one[i];
            k++;
        }
    }
}

void merge_sort(int* input, size_t size)
{
    // We don't need to do anything if the array has nothing or one thing in it
    if (size > 1)
    {
        // Split the input array into two and determine their sizes
        const size_t size_one = floor(size / 2);
        const size_t size_two = size - size_one;

        int* array_one = malloc(sizeof(int) * size_one);
        int* array_two = malloc(sizeof(int) * size_two);

        for (size_t i = 0; i < size_one; i++)
        {
            array_one[i] = input[i];
        }

         for (size_t j = 0; j < size_two; j++)
        {
            array_two[j] = input[j+size_one];
        }

        merge_sort(array_one, size_one);
        merge_sort(array_two, size_two);

        merge(array_one, array_two, size_one, size_two, input);

        free(array_one);
        free(array_two);
    }
}

int main(void)
{
    int* test_array;
    test_array = (int[10]){10,23,18,49,78,172,55,8,29,37};

    merge_sort(test_array, 10);

    // Print results
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d%s", test_array[i], (i!=9) ? ", " : "\n");
    }

    return 0;
}