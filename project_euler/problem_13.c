/*
Project Euler Problem 13
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
-- Number is in file problem_13_input
*/
#include "stdio.h" //printf()
#include "stdlib.h" //getline()

void sum_big_numbers(char* num1, char* num2);

// Sum big numbers and store the result in num1.
void sum_big_numbers(char* num1, char* num2)
{
    int current_num_1 = 0;
    int current_num_2 = 0;
    int temp_sum = 0;
    int carry_over = 0;
    for (int i = 49; i > -1; i--)
    {
        // Convert the chars to ints for this unit place
        current_num_1 = num1[i] - '0';
        current_num_2 = num2[i] - '0';
        temp_sum = current_num_2 + current_num_1;
        if (temp_sum >= 10) carry_over = temp_sum - 10;
        printf("%d, %d\n", temp_sum, carry_over);
    }
}


int main(int argc, char *argv[])
{
    FILE *f;
    char *curr_line = NULL;
    //char *curr_sum = "00000000000000000000000000000000000000000000000000";
    char *curr_sum = "46376937677490009712648124896970078050417018260538";
    size_t len = 0;
    ssize_t num_chars_read;

    f = fopen("problem_13_input", "r");
    if (f == NULL) return 1;

    while ((num_chars_read = getline(&curr_line, &len, f)) != -1) 
    {
        sum_big_numbers(curr_sum, curr_line);
        break;
    }

    fclose(f);
    if (curr_line) free(curr_line);

    return 0;
}