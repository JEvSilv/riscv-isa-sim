#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "rva-fwk.h"

void rword(uint8_t *word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint32_t bitcount_in_place(uint8_t* msg, size_t len) {
    uint8_t half_l[len], half_r[len], buff[len], counter[len], i;

    SET_RVA(counter, 0, len, 1);
    SRL_RVA(msg, half_l, len, 4, 1);
    AND_RVA(msg, half_r, len, 0xF, 1);

    for(i = 0; i < 4; i++) {
        AND_RVA(half_l, buff, len, 1, 1);
        ADD_RVA(counter, buff, counter, len, 1);
        SRL_RVA(half_l, half_l, len, 1, 1);  
        AND_RVA(half_r, buff, len, 1, 1);
        ADD_RVA(counter, buff, counter, len, 1);
        SRL_RVA(half_r, half_r, len, 1, 1);
    }

    if(len & 1) {
        counter[0] += counter[len-1];
        len = len - 1;
    }
    
    uint8_t* pivot = NULL;
    while(len > 1) {
        len = len >> 1;
        pivot = &counter[len];
        ADD_RVA(counter, pivot, counter, len, 1);  
        if(len & 1 && len > 1) {
            len++;
            counter[len-1] = 0;
        }
    }

    //for(i = 1; i < len; i++){
    //    counter[0] += counter[i];
    //}

    return counter[0];
}

int main (int argc, char* argv[]) {
    size_t len = atoi(argv[1]);
    uint8_t str[] = "0123456789ABCDEF";
    time_t t;
    uint8_t* m = (uint8_t*) malloc(len*sizeof(uint8_t));
   
    srand((unsigned)time(0)+len);
    size_t i = len;
    
    while(i--) {
        m[i] = str[rand() % 16];
    }
    
    uint32_t volatile counter = bitcount_in_place(m, len);
    //printf("%u\n", counter);
}
