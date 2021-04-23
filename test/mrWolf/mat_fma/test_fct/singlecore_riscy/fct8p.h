
#ifndef __FCT_H__
#define __FCT_H__

#include "rtos_hal.h"
#include <stdint.h>

typedef struct{
	const int8_t * __restrict__ pSrcA;
	const int8_t * __restrict__ pSrcB;
	uint32_t M;
	uint32_t N;
	uint32_t O;
	uint32_t nPE;
	int32_t * __restrict__ pDstC;
}mat_mult_p_args;

void plp_mat_mult_i8vp_xpulpv2(
        void* args
        );

#endif
