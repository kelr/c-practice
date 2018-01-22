/*
Project Euler Problem 13
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
-- Number is in file problem_13_input
*/
#include "stdio.h" //printf()
#include "math.h" //sqrt(), make sure to compile with the -lm flag
#include "time.h" //clock(), CLOCKS_PER_SEC, clock_t



int main(int argc, char *argv[])
{
    unsigned int nth_triangle_num = 0;
    unsigned int curr_triangle_num = 0;
    unsigned int count = 0;
    unsigned int max_count = 0;
    clock_t start = clock();
    while (max_count <= 500)
    {
        // Build triangle numbers by adding the desired position to the previous one
        nth_triangle_num++;
        curr_triangle_num += nth_triangle_num;
        count = count_factors(curr_triangle_num);
        if (count > max_count)
        {
            max_count = count;
            printf("%d\n", max_count);
        }

    }
    clock_t end = clock();
    double total_s = (((double)(end - start)) / CLOCKS_PER_SEC);

    printf("The %dth Triangle num: %d has %d factors\n",nth_triangle_num, curr_triangle_num, max_count);
    printf("Time taken: %f s\n", total_s);
    return 0;
}