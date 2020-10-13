#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rva-fwk.h"

int main() {
    size_t len = 5;
    uint8_t* v = (uint8_t*) malloc(len*sizeof(uint8_t));

    SET_RVA(v,len,2,1);

    uint8_t i;
    for(i = 0; i < len; i++) {
        printf("%u\n", v[i]);
    }
}
