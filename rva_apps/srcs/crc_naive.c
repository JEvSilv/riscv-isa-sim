#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define POLYNOMIAL 0x04c11db7

void rword(uint8_t *word, int len)
{
    word[len] = 0;
    while (len) word[--len] = 'a' + rand() % 26;
}

uint32_t crc_naive(uint8_t* message, size_t length)
{
  uint32_t i, j, crc = 0;
  for (i = 0; i < length; i++)
  {
    crc ^= (uint32_t) (message[i] << 24);
    for (j = 0; j < 8; j++)
    {
	if ((crc & 0x80000000) != 0)
	{
	    crc = (uint32_t)((crc << 1) ^ POLYNOMIAL);
	}else
	{
	    crc <<= 1;
	}
    }
  }
  return crc;
}


int main (int argc, char* argv[]) {
    size_t len = atoi(argv[1]);
    uint8_t* m = (uint8_t*) malloc(len*sizeof(uint8_t));
    time_t t;
    srand((unsigned) time(&t));
    rword(m,len);
    uint32_t crc = crc_naive(m, len);
}

