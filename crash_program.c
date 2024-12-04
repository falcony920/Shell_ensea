#include <stdio.h>

int crash_program()
{
    // This will cause a segmentation fault
    int *ptr = NULL;
    *ptr = 10; // Segmentation fault
    return 0;
}
