#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rva-fwk.h"
#define SIZE 16

int main()
{
    uint8_t A[] = { 6 };
    uint8_t B[] = { 6 };
    uint8_t result[] = { 0 };

    printf("%u *%u\n", A[0], B[0]);
    MULT_RVA(&A, &B, &result, 1, 1);
    printf("result[%d] => %d\n", 0, result[0]);
    return 0;
}

