#include "insertion_sort.h"

int main(void)
{
    int snacks[50] = {5, 2, 8, 34, 8, 2, 4, 89, -10, 11,5, 2, 8, 34, 8, 2, 4, 89, -10, 11,5, 2, 8, 34, 8, 2, 4, 89, -10, 11,5, 2, 8, 34, 8, 2, 4, 89, -10, 11,5, 2, 8, 34, 8, 2, 4, 89, -10, 11};
    size_t size = sizeof(snacks) / sizeof(snacks[0]);
    int *p_snacks = snacks;

    insertion_sort(p_snacks, size);
    visualize(p_snacks, size);
}