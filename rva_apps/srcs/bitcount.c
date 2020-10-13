#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>


void rword(uint8_t *word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint8_t count_ones (uint8_t byte)
{
    static const uint8_t NIBBLE_LOOKUP [16] =
    {
        0, 1, 1, 2, 1, 2, 2, 3, 
        1, 2, 2, 3, 2, 3, 3, 4                  
    };

    return NIBBLE_LOOKUP[byte & 0x0F] + NIBBLE_LOOKUP[byte >> 4];  
}

uint32_t bitcount(uint8_t* msg, size_t len) {
    uint32_t counter = 0, i;
    for(i = 0; i < len; i++)
        counter += count_ones(msg[i]);
    return counter;
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
    
    uint32_t volatile counter = bitcount(m, len);
    //printf("%u\n", counter);
}
