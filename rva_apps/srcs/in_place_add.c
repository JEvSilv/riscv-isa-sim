#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>
#include "rva-fwk.h"

#define SIZE 16

int main()
{
    uint32_t A[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    uint32_t B[] = { 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
    uint32_t result[SIZE], i;
 
    ADD_RVA(&A, &B, &result, SIZE, 4);

    for(i = 0; i < SIZE; i++) {
        printf("result[%u]: %u\n", i, result[i]);
    }    

    return 0;
}
