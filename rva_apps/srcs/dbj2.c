#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void rword(uint8_t* word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint64_t djb2(uint8_t* msg, size_t len) {
    uint64_t hash = 5381;
    int i;
    
    for(i = 0; i < len; i++) {
	hash = ((hash << 5) + hash) + msg[i];
	//hash = hash * 33 + msg[i];
    }
    
    return hash;
}

int main (int argc, char* argv[]) {
    size_t len = atoi(argv[1]);
    //size_t len = 4;
    uint8_t* m = (uint8_t*) malloc(len * sizeof(uint8_t));
    //m[0] = 1;
    //m[1] = 2;
    //m[2] = 3;
    //m[3] = 4;
    time_t t;
    srand((unsigned) time(&t));
    rword(m,len);
    uint64_t hash = djb2(m, len);
    //printf("Hash => %lu\n", hash);
}
