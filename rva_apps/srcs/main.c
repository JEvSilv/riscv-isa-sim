#include <stdio.h>
#include <stdint.h>
#define POLYNOMIAL 0x04c11db7

uint32_t crc_naive(uint8_t message[], uint32_t length)
{
  uint32_t i, j, crc = 0;
  //printf("naive length: %d\n", length);
  for (i = 0; i < length; i++)
  {
    crc ^= message[i];
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc ^= POLYNOMIAL;
      crc >>= 1;
    }
  }
  return crc;
}

int main()
{
    uint8_t pack[] = {0};
    for(uint8_t i = 0; i < 8; i++)
    {
	pack[0] = i+1;
	printf("%d\n", (uint8_t) crc_naive(pack,1));
    }

    return 0;
}
