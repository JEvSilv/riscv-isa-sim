#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rva-fwk.h"

#define LENGTH 11

int main()
{
    uint8_t A[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    //uint8_t B[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint8_t B[] = { 0, 1, 2, 3, 4, 5, 3, 2, 1, 1, 0 };
    uint8_t result[LENGTH];

    MULT_RVA(A, B, result, LENGTH, 1);
    //ADD_RVA(A, B, result, LENGTH, 1);
    //SUB_RVA(A, B, result, LENGTH, 1);

    for(uint32_t i; i < LENGTH; i++)
        printf("result[%d] => %d\n", i, result[i]);

    return 0;
}
