#include "fct8p.h"
#include <stdio.h>

#define BLOCK_VERSION

HAL_CL_L1 static v4s mask0 = {0,1,4,5};
HAL_CL_L1 static v4s mask1 = {2,3,6,7};
HAL_CL_L1 static v4s mask2 = {0,2,4,6};
HAL_CL_L1 static v4s mask3 = {1,3,5,7};

#if defined(BLOCK_VERSION)

void plp_mat_mult_i8vp_xpulpv2(void* args) {
        
        mat_mult_p_args* arguments = (mat_mult_p_args*) args;
        const int8_t * __restrict__ pSrcA = arguments->pSrcA;
        const int8_t * __restrict__ pSrcB = arguments->pSrcB;
        uint32_t M = arguments->M;
        uint32_t N = arguments->N;
        uint32_t O = arguments->O;
        uint32_t nPE = arguments->nPE;
        int32_t * __restrict__ pDstC = arguments->pDstC;

        uint32_t i=0; // loop counter for M
        uint32_t j=0; // loop counter for N
        uint32_t k=0; // loop counter for O
        
        uint32_t core_id = hal_core_id();

        for(k=core_id; k < O/4; k+=nPE){
          for(i=0; i < M/2; i++){

            int32_t sum00 = 0;
            int32_t sum01 = 0;
            int32_t sum02 = 0;
            int32_t sum03 = 0;
            int32_t sum10 = 0;
            int32_t sum11 = 0;
            int32_t sum12 = 0;
            int32_t sum13 = 0;

            // v2s* Bpoint = (v2s*) &(pSrcB[k]);

            for(j=0; j<N/4; j++){
              
              v4s aVec0 = *((v4s*)&(pSrcA[(i*2  )*N + (j*4  )]));
              v4s aVec1 = *((v4s*)&(pSrcA[(i*2+1)*N + (j*4  )]));

              v4s temp0 = *((v4s*)&(pSrcB[(j*4  )*O + (k*4  )]));
              v4s temp1 = *((v4s*)&(pSrcB[(j*4+1)*O + (k*4  )]));
              v4s temp2 = *((v4s*)&(pSrcB[(j*4+2)*O + (k*4  )]));
              v4s temp3 = *((v4s*)&(pSrcB[(j*4+3)*O + (k*4  )]));

              v4s temp4 = __builtin_shuffle(temp0,temp1,mask0); // 0,1,4,5
              v4s temp5 = __builtin_shuffle(temp2,temp3,mask0); // 8,9,12,13
              v4s temp6 = __builtin_shuffle(temp0,temp1,mask1); // 2,3,6,7
              v4s temp7 = __builtin_shuffle(temp2,temp3,mask1); // 3,7,11,15

              v4s bVec0 = __builtin_shuffle(temp4,temp5,mask2);
              v4s bVec1 = __builtin_shuffle(temp4,temp5,mask3);
              v4s bVec2 = __builtin_shuffle(temp6,temp7,mask2);
              v4s bVec3 = __builtin_shuffle(temp6,temp7,mask3);

              sum00 = __SUMDOTP4(aVec0,bVec0,sum00);
              sum01 = __SUMDOTP4(aVec0,bVec1,sum01);
              sum02 = __SUMDOTP4(aVec0,bVec2,sum02);
              sum03 = __SUMDOTP4(aVec0,bVec3,sum03);
              sum10 = __SUMDOTP4(aVec1,bVec0,sum10);
              sum11 = __SUMDOTP4(aVec1,bVec1,sum11);
              sum12 = __SUMDOTP4(aVec1,bVec2,sum12);
              sum13 = __SUMDOTP4(aVec1,bVec3,sum13);

            }

            pDstC[(i*2  )*O +(k*4  )] = sum00;
            pDstC[(i*2  )*O +(k*4+1)] = sum01;
            pDstC[(i*2  )*O +(k*4+2)] = sum02;
            pDstC[(i*2  )*O +(k*4+3)] = sum03;
            pDstC[(i*2+1)*O +(k*4  )] = sum10;
            pDstC[(i*2+1)*O +(k*4+1)] = sum11;
            pDstC[(i*2+1)*O +(k*4+2)] = sum12;
            pDstC[(i*2+1)*O +(k*4+3)] = sum13;

          }
        }
                
                
        // clean up code
        i = i*2;
        j = j*4;
        k = k*4;
        //check if every index is nicely finished
        if(i == M && j == N && k >= O){
          
        } else {
          uint32_t iEnd = i;
          uint32_t jEnd = j;
          uint32_t kEnd = k >= O ? O : k;

          // clean up for j
          if(jEnd != N){
            for(k = core_id*4; k < kEnd; k+=nPE*4){
              for(int step = 0; step < 4; step++){
                for(i = 0; i < iEnd; i++){
                  int32_t sum = 0;
                  for(j = jEnd; j < N; j++){
                    sum = sum + pSrcA[i*N + j]*pSrcB[j*O + k + step];
                  }
                  pDstC[i*O+k+step] += sum;
                }
              }
            }
          }

          // clean up for i
          if(iEnd != M){
            for(k = core_id*4; k < kEnd; k+=nPE*4){
              for(int step = 0; step < 4; step++){
                for(i = iEnd; i < M; i++){
                  int32_t sum = 0;
                  for(j = 0; j < N; j++){
                    sum = sum + pSrcA[i*N + j]*pSrcB[j*O + k + step];
                  }
                  pDstC[i*O + k + step] = sum;
                }
              }
            }
          }

          // clean up for k
          for(k = kEnd; k < O; k++){
            for(i = 0; i < M; i++){
              int32_t sum = 0;
              for(j=0; j<N; j++){
                sum = sum + pSrcA[i*N + j]*pSrcB[j*O + k];
              }
              pDstC[i*O + k] = sum;
            }
          }

        }

      hal_team_barrier();
}

#else

void plp_mat_mult_i8vp_xpulpv2(void* args) {
        
        mat_mult_p_args* arguments = (mat_mult_p_args*) args;
        const int8_t * __restrict__ pSrcA = arguments->pSrcA;
        const int8_t * __restrict__ pSrcB = arguments->pSrcB;
        uint32_t M = arguments->M;
        uint32_t N = arguments->N;
        uint32_t O = arguments->O;
        uint32_t nPE = arguments->nPE;
        int32_t * __restrict__ pDstC = arguments->pDstC;

        uint32_t i; // loop counter
        uint32_t j; // loop counter
        uint32_t k; // loop counter

        for(i=0; i < M; i++){
          for(k=0; k < O; k++){
            int32_t sum = 0;
            for(j=0; j<N; j++){
              sum = sum + pSrcA[i*N + j]*pSrcB[j*O+k];
            }
            pDstC[i*O +k] = sum;
          }
        }

        hal_team_barrier();
}

#endif
