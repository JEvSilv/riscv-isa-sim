#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rva-fwk.h"
#define SIZE 16

int main()
{
    uint8_t A[] = { 0 };
    uint8_t B[] = { 0 };
    uint8_t result[] = { 0 };

    for(uint8_t i = 0; i < SIZE; i++) {
        for(uint8_t j = 0; j < SIZE; j++) {
            if(i <= j) {
                printf("%u*%u -> ", i, j);
                A[0] = i;
                B[0] = j;
                MULT_RVA(&A, &B, &result, 1, 1);
                if(i*j == result[0]) {
                    printf("Ok!\n");
                }else {
                    printf("Error\n");
                }
            }
        }   
    }
    /*
    mult_rim(&A, &B, &result, 1); 
    printf("\n");
    for(uint32_t i; i < length; i++)
        printf("result[%d] => %d\n", i, result[i]);
    */    
    return 0;
}

