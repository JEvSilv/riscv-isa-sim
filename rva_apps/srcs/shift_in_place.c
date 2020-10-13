#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rva-fwk.h"

int main() {
    uint8_t a[1] = { 2 };
    uint8_t res[1] = { 0 };
    
    SLL_RVA(a, res, 1, 1, 1);
    printf("SLL A -> %u\n", res[0]);
 
    SRL_RVA(a, res, 1, 1, 1);
    printf("SRL A -> %u\n", res[0]);
 
    AND_RVA(a, res, 1, 2, 1);
    printf("AND A -> %u\n", res[0]);
 
    OR_RVA(a, res, 1, 1, 1);
    printf("OR A -> %u\n", res[0]);
 
    XOR_RVA(a, res, 1, 1, 1);
    printf("XOR A -> %u\n", res[0]);
    
    NOT_RVA(a, res, 1, 1, 1);
    printf("NOT A -> %u\n", res[0]);

    return 0;
}
