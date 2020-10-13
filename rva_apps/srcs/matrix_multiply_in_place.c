#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "rva-fwk.h"

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
    uint8_t* buff = (uint8_t *) malloc(len*sizeof (uint8_t));
   
    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            SET_RVA(buff, len, A[i][j], 1);
            MULT_RVA(buff, B[j], buff, len, 1); 
            ADD_RVA(C[i], buff, C[i], len, 1);
        }
    }

    free(buff);


     for(i = 0; i < len; i++) {
         for(j = 0; j < len; j++) {  
            printf("%d ", C[i][j]);
         } 
         printf("\n");
     }

    return 0;
}

// printf("buff[%u] => %u\n", k, buff[k]);
/*    int A[SIZE][SIZE] = {{1,2,3},
                        {2,3,1},
                        {2,1,2}};

    int B[SIZE][SIZE] = {{1,2,3},
                        {2,3,1},
                        {2,1,2}};

    int C[SIZE][SIZE] = {{0,0,0},
                        {0,0,0},
                        {0,0,0}};

    uint8_t A[SIZE][SIZE] = {{1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8}};

    uint8_t B[SIZE][SIZE] = {{1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8},
                        {1,2,3,4,5,6,7,8}};

    uint8_t C[SIZE][SIZE] = {{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}}
    uint8_t A[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10}};

    uint8_t B[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10},
                            {1,2,3,4,5,6,7,8,9,10}};
  
    uint8_t C[SIZE][SIZE] = {{0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}};
*/
