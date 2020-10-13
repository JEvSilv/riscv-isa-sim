#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#define SIZE 10 

uint8_t** init_matrix(size_t len, uint8_t init) {
   uint8_t **M; 
   int i, j;
   M = (uint8_t**) calloc (len, sizeof (uint8_t *));
   for (i = 0; i < len; ++i)
      M[i] = (uint8_t*) calloc (len, sizeof (uint8_t));

   if(init == 1){ 
       for(i = 0; i < len; i++)
           for(j = 0; j < len; j++)
	       M[i][j] = i+j;
   }

   return M;
}

uint8_t** init_random_matrix(size_t len, uint8_t init) {
   uint8_t **M; 
   int i, j;
   M = (uint8_t**) calloc (len, sizeof (uint8_t *));
   for (i = 0; i < len; ++i)
      M[i] = (uint8_t*) calloc (len, sizeof (uint8_t));

   if(init == 1){ 
        uint8_t str[] = "0123456789ABCDEF";
        srand((unsigned)time(0)+len);
        size_t i = len;
        for(i = 0; i < len; i++)
           for(j = 0; j < len; j++)
	       M[i][j] = str[rand() % 16];
   }

   return M;
}

int main(int argc, char* argv[])
{
    size_t len = atoi(argv[1]);
    uint8_t** A = init_random_matrix(len, 1); 
    uint8_t** B = init_random_matrix(len, 1);                     
    uint8_t** C = init_matrix(len, 0);

    uint64_t i, j, k;

    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            for(k = 0; k < len; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
     }

     for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {  
            printf("%d ", C[i][j]);
        }
        printf("\n") ;
     }
  
    return 0;
}
