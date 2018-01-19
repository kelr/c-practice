#include "../insertion_sort/insertion_sort.h"
#include "recursive_binary_search.h"

int main(void)
{
    int snacks[10] = {5, 2, 88, 34, 8, 3, 4, 89, -10, 11};
    int size = (int)(sizeof(snacks) / sizeof(snacks[0]));
    int *p_snacks = snacks;
    insertion_sort(p_snacks, size);
    assert(0 == recursive_binary_search(-10, p_snacks, 0, size-1));
    assert(1 == recursive_binary_search(2, p_snacks, 0, size-1));
    assert(2 == recursive_binary_search(3, p_snacks, 0, size-1));
    assert(3 == recursive_binary_search(4, p_snacks, 0, size-1));
    assert(4 == recursive_binary_search(5, p_snacks, 0, size-1));
    assert(5 == recursive_binary_search(8, p_snacks, 0, size-1));
    assert(6 == recursive_binary_search(11, p_snacks, 0, size-1));
    assert(7 == recursive_binary_search(34, p_snacks, 0, size-1));
    assert(8 == recursive_binary_search(88, p_snacks, 0, size-1));
    assert(9 == recursive_binary_search(89, p_snacks, 0, size-1));
}