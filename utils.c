#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Helper function to convert an integer to a string
void itoa(int num, char *str)
{
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (num < 0)
    {
        is_negative = 1;
        num = -num;
    }

    // Process each digit
    while (num != 0)
    {
        str[i++] = (num % 10) + '0'; // Get next digit
        num = num / 10;
    }

    // Add negative sign for negative numbers
    if (is_negative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
