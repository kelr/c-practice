#include "recursive_binary_search.h"

int recursive_binary_search(int target, int *input, int low, int high)
{
    if (low > high) return 0;
    else
    {
        int mid = (low + high) / 2;

        if (input[mid] == target) 
        {
            return mid;
        }
        else if (input[mid] > target)
        {
            return recursive_binary_search(target, input, low, mid - 1);
        }
        else
        {
            return recursive_binary_search(target, input, mid + 1, high);
        }
    }

}