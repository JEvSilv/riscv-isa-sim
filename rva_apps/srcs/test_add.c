#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>
#include "rva-fwk.h"

#define SIZE 16

int main()
{
    uint64_t A[] = { 0 };
    uint64_t B[] = { 0 };
    uint64_t result[] = { 0 };

    for(uint8_t i = 0; i < SIZE; i++) {
        for(uint8_t j = 0; j < SIZE; j++) {
            if(i <= j) {
                printf("%u+%u -> ", i, j);
                A[0] = i;
                B[0] = j;
                ADD_RVA(&A, &B, &result, 1, 8);
                if(i+j == result[0]) {
                    printf("Ok!\n");
                }else {
                    printf("Error\n");
                }
            }
        }   
    }
 
    return 0;
}
