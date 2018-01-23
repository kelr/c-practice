/*
Project Euler Problem 13
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
-- Number is in file problem_13_input
*/
#include "stdio.h" //printf(), fopen(), fclose()
#include "stdlib.h" //getline(), malloc(), free()
#include "string.h" //strlen(), strcspn()

char* sum_big_numbers(char *num1, char *num2);
char* reverse_string (char *str);

// Sum some big numbers represented by char arrays.
// Determines the sizes and difference in sizes between both input arrays.
// Then begins summing the arrays from the last element, like elementary school addition
// This summation continues until the smaller array has iterated through.
// Then the rest of the larger array gets appended to the end of the output array.
// Because we summed both arrays from back to front, we need to reverse the output array.
char* sum_big_numbers(char *num1, char *num2)
{
    int temp_sum = 0;
    int carry_over = 0;
    ssize_t smaller_size = 0;
    ssize_t larger_size = 0;
    ssize_t offset1 = 0;
    ssize_t offset2 = 0;
    int j = 0;
    int j2 = 0;

    size_t size1 = strlen(num1);
    size_t size2 = strlen(num2);

    // If they're equal just pretend size2 is bigger, it doesn't really matter
    if (size1 > size2) 
    {
        smaller_size = size2;
        larger_size = size1;
        offset1 = larger_size - smaller_size;
        offset2 = 0;
    }
    else
    {
        smaller_size = size1;
        larger_size = size2;
        offset1 = 0;
        offset2 = larger_size - smaller_size;
    }

    // Allocate extra space just in case the largest units place causes a carry over
    char *output = malloc(sizeof(char) * (larger_size + 1));

    // Begin summing through the smaller array
    for (int i = smaller_size-1; i > -1; i--)
    {
        // Start a reverse counter to fill the output array
        j = (smaller_size-1) - i;

        // Add the current decimal place, need to convert chars to ints
        // Offsets will only be applied to the larger array to align both arrays.
        // One of the offsets will be 0, that will be the smaller array
        temp_sum = (num1[i+offset1] - '0') + (num2[i+offset2] - '0') + carry_over;

        // Determine if we need a carry over if the sum >= 10
        carry_over = temp_sum / 10;

        // Grab the units part of the sum if we have a carry over
        if (carry_over) 
        {
            temp_sum = temp_sum % 10;
        }

        // Add the current decimal place to the output array
        output[j] = temp_sum + '0';
    }


    // Carry over the remaining digits
    // The starting point should be the difference between the sizes of the inputs (offset)
    // We add both offsets because one of them is zero and the other is the actual offset
    j2 = smaller_size;
    for (int k = (offset1+offset2) - 1; k > -1; k--)
    {
        // Add only the values for the larger array
        if (larger_size == size1)
        {
            temp_sum = (num1[k] - '0') + carry_over;
        }
        else
        {
            temp_sum = (num2[k] - '0') + carry_over;
        }

        // Determine if we need a carry over if the sum >= 10
        carry_over = temp_sum / 10;

        // Grab the units part of the sum if we have a carry over
        if (carry_over) 
        {
            temp_sum = temp_sum % 10;
        }

        // Add the current decimal place to the output array
        output[j2] = temp_sum + '0';
        j2++;
    }

    // Calculate the final carry over and add it to the output if needed
    if (carry_over)
    {
        output[j2] = carry_over + '0';
    }

    output = reverse_string(output);
    return output;
}

char* reverse_string (char *str) 
{
    char tmp;
    char *src;
    char *dst;
    size_t len;
    if (str != NULL)
    {
        len = strlen(str);
        if (len > 1) 
        {
            src = str;
            dst = src + len - 1;
            while (src < dst) 
            {
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
    char *curr_sum = "00000000000000000000000000000000000000000000000000";
    size_t len = 0;
    ssize_t num_chars_read;

    f = fopen("problem_13_input", "r");
    if (f == NULL) return 1;

    // Read a line from the file
    while ((num_chars_read = getline(&curr_line, &len, f)) != -1)
    {
        // Strip the newline from the read line
        curr_line[strcspn(curr_line, "\n")] = 0;
        printf("        +%s\n\n", curr_line);
        // Calculate the sum, store it back in the current sum
        curr_sum = sum_big_numbers(curr_sum, curr_line);
        printf("Result: %s\n", curr_sum);
    }

    fclose(f);
    /*
       If *lineptr is set to NULL and *n is set 0 before the call, then
       getline() will allocate a buffer for storing the line.  This buffer
       should be freed by the user program even if getline() failed.
    */
    if (curr_line) free(curr_line);

    return 0;
}