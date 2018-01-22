/*
Project Euler Problem 13
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
-- Number is in file problem_13_input
*/
#include "stdio.h" //printf()
#include "stdlib.h" //getline()
#include "string.h" //strlen()

char* sum_big_numbers(char* num1, char* num2);
char* reverse_string (char *str);

// Sum some big numbers 
char* sum_big_numbers(char* num1, char* num2)
{
    int current_num_1 = 0;
    int current_num_2 = 0;
    int temp_sum = 0;
    int carry_over = 0;
    ssize_t larger_size = 0;
    char *p_output;
    int j = 0;
    size_t size1 = strlen(num1);
    size_t size2 = strlen(num2);

    // If they're equal just use size 2
    if (size1 > size2) 
    {
        larger_size = size1;
    }
    else
    {
        larger_size = size2;
    }

    // Allocate a one extra space just in case
    char output[larger_size+1];

    for (int i = larger_size-1; i > -1; i--)
    {
        j = (larger_size-1) - i;

        // Convert the chars to ints for this unit place
        current_num_1 = num1[i] - '0';
        current_num_2 = num2[i] - '0';

        temp_sum = current_num_2 + current_num_1 + carry_over;
        carry_over = 0;

        if (temp_sum >= 10) 
        {
            carry_over = 1;
        }

        temp_sum = temp_sum % 10;

        output[j] = '0' + temp_sum;

        if (carry_over && i == 0)
        {
            output[j] = '0' + carry_over;
        }
        else if(i == 0)
        {
            output[j+1] = '\0';
        }
    }
    p_output = output;
    printf("%s\n", p_output);
    reverse_string(p_output);

    return p_output;
}

char* reverse_string (char *str) 
{
    char tmp, *src, *dst;
    size_t len;
    if (str != NULL)
    {
        len = strlen (str);
        if (len > 1) {
            src = str;
            dst = src + len - 1;
            while (src < dst) {
                tmp = *src;
                *src++ = *dst;
                *dst-- = tmp;
            }
        }
    }
    return str;
}


int main(int argc, char *argv[])
{
    FILE *f;
    char *curr_line = NULL;
    //char *curr_sum = "00000000000000000000000000000000000000000000000000";
    char *curr_sum = "74324986199524741059474233309513058123726617309629";
    size_t len = 0;
    ssize_t num_chars_read;

    f = fopen("problem_13_input", "r");
    if (f == NULL) return 1;

    while ((num_chars_read = getline(&curr_line, &len, f)) != -1) 
    {
        // Strip the newline from the read line
        curr_line[strcspn(curr_line, "\n")] = 0;
        curr_sum = sum_big_numbers(curr_sum, curr_line);
        printf("%s\n", curr_sum);
        break;
    }

    fclose(f);
    if (curr_line) free(curr_line);

    return 0;
}