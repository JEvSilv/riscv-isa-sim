#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rva-fwk.h"
#include <time.h>

void rword(uint8_t* word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint32_t sdbm_in_place(uint8_t* msg, size_t len) {
    uint64_t hash[1] = { 0 };
    uint64_t c[1] = { 65599 };
    uint64_t buff[1] = { 0 };
     
    while (buff[0] = (uint64_t) *msg) {
        MULT_RVA(c, c, hash, 1, 8);
        printf("hash => %u\n", hash[0]);
        ADD_RVA(hash, buff, hash, 1, 4);
        printf("hash - add => %u\n", hash[0]);
        *msg++;
    }
    
    return hash[0];
}

int main (int argc, char* argv[]) {
    //size_t len = atoi(argv[1]);
    size_t len = 4;
    uint8_t* m = (uint8_t*) malloc(len * sizeof(uint8_t));
    m[0] = 1;
    m[1] = 2;
    m[2] = 3;
    m[3] = 4;
//    time_t t;
//    srand((unsigned) time(&t));
//    rword(m,len);
    uint32_t hash = sdbm_in_place(m, len);
    printf("Hash => %u\n", hash);
}
