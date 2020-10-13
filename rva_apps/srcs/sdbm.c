#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void rword(uint8_t* word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint32_t sdbm(uint8_t* msg, size_t len) {
    uint32_t hash = 0;
    uint32_t i;
    
    for (i = 0; i < len ; i++){
        //hash = msg[i] + (hash << 6) + (hash << 16) - hash;
        hash = hash*65599;
        printf("hash -> %u\n", hash);
        hash = msg[i] + hash;
        printf("hash - add -> %u\n", hash);
    }
    
    return hash;
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
    uint32_t hash = sdbm(m, len);
    printf("Hash => %u\n", hash);
}
