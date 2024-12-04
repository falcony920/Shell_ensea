#include <stdio.h>

int main()
{
    // This will cause a segmentation fault
    int *ptr = NULL;
    *ptr = 10; // Segmentation fault
    return 0;
}
