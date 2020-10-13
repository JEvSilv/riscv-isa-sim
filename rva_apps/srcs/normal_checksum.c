#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void rword(uint8_t *word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint8_t checksum(const uint8_t* buff, size_t len)
{
    uint32_t sum;      
    for ( sum = 0 ; len != 0 ; len--  )
        sum += *(buff++);   

    return sum;
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
    
    uint8_t volatile check = checksum(m, len);
    //printf("%u\n", check);
}
