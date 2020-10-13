#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rva-fwk.h"
#define PACKET_SIZE 8

int main()
{
    uint32_t length  = 1; 
    //uint8_t A[] = { 1, 2, 4, 4, 5, 16, 7, 10 };
    //uint8_t B[] = { 1, 2, 3, 5, 5, 6, 1, 13 };
    uint8_t A[] = { 6 };
    uint8_t B[] = { 12 };

    uint8_t result[PACKET_SIZE];
    uint32_t polynomial = 0x04C11DB7;
    //add_rim(&A, &B, &result, 8); 
    //mult_rim(&A, &B, &result, 8);
    MULT_RVA(&A, &B, &result, length, 1); 
    //and_rim(&A, &result, PACKET_SIZE, 1);
    //crc_rim(&A, &result, PACKET_SIZE, polynomial);
    printf("\n");
    for(uint32_t i; i < length; i++)
        printf("result[%d] => %d\n", i, result[i]);
        
    return 0;
}

