#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void merge(int* input_one, int* input_two, const size_t size_one, const size_t size_two, int* output);
void merge_sort(int* input, size_t size);


void merge(int* input_one, int* input_two, const size_t size_one, const size_t size_two, int* output)
{
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
    test_array = (int[10]){1,15,29,33,0,22,999,62,10,77};

    merge_sort(test_array, 10);

    // Print results
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d%s", test_array[i], (i!=9) ? ", " : "\n");
    }

    return 0;
}