#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "rva-fwk.h"
/*
uint8_t* migration(uint8_t* m, size_t* len) {
    if(*len & 1) {
        m[0] = m[0] + m[(*len)-1];
       *len = *len - 1;
    }

    uint8_t* buff = NULL;
    uint8_t* pivot = NULL;
    *len = *len/2;
    pivot = &m[*len];
    buff = (uint8_t*) calloc(*len, sizeof(uint8_t));
    ADD_RIM(buff, pivot, buff, *len, 1);  
    return buff;
}

uint8_t checksum(uint8_t* m, size_t len)
{
    uint8_t* buff = migration(m, &len);   
    uint8_t* pivot = NULL;

    while(len > 1) {
        len = len/2;
        pivot = &buff[len];
        ADD_RIM(buff, pivot, buff, len, 1);  
        if(len & 1 && len > 1) {
            len++;
            buff[len-1] = 0;
        }
    }

    uint32_t sum = buff[0];
    free(buff);
    return sum;
}
*/
uint8_t _checksum(uint8_t* counter, size_t len)    {
    //uint8_t* counter_f = (uint8_t*) calloc(len, sizeof(uint8_t));
    //ADD_RIM(counter, m, counter, len, 1);  
    //uint8_t* counter = m;
    //printf("dentr\n");

    if(len & 1) {
        counter[0] += counter[len-1];
        len = len - 1;
    }

    uint8_t* pivot = NULL;
    while(len > 4) {
        len = len >> 1;
        pivot = &counter[len];
        ADD_RVA(counter, pivot, counter, len, 1);  
        if(len & 1 && len > 1) {
            len++;
            counter[len-1] = 0;
        }
    }   
    
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
    
    uint8_t volatile check = _checksum(m,len);
    //printf("%u\n", check);
    return 0;
}
