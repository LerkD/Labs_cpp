#include <iostream>
#include <stdlib.h>

int main()
{
    // 0 0 0 69
    int i = 69;

    // 0 0 0 72
    int number = 72;

    i = i + number; // 0 0 0 141

    // 0 0 0 0
    // 0 0 0 0
    // 0 0 0 0
    int arr[3] = {};

    int* iPointer = &i;

    number = *iPointer;

    *iPointer = 15;

    iPointer =&arr[0];

    iPointer = iPointer + 2;

    arr[0] = 5;
    *iPointer = 6;

    return 0;
}



