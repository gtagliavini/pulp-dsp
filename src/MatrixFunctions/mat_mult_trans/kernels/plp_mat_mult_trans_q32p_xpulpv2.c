/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_mult_trans_q32p_xpulpv2.c
 * Description:  32-bit integer matrix multiplication for XPULPV2
 *
 * $Date:        18. July 2019
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna.
 *
 * Author: Tibor Schneider, ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "plp_math.h"

/**
  @ingroup groupMatrix MatMultTrans
 */

/**
  @addtogroup MatMultTransKernels
  @{
 */

/**
  @brief Parallel Matrix multiplication of 32-bit fix-point matrices kernel for XPULPV2 extension.
  @param[in]  args  pointer to plp_mat_mult_instance_q32 struct initialized by
                    plp_mat_mult_trans_q32_parallel
  @return     none

  @par Fix-Point and Shifting
  The result will be shifted by the parameter `shift` to the right (multiplied
  by 2^-shift). Assume that matrix A is represented as pSrcA * 2^-x, and matrix
  B as pSrcB * 2^-y (in other words, A has it's x last digits after the binary
  point). Then, the output is represented as pDstC * 2^-(x + y - shift).
 */

void plp_mat_mult_trans_q32p_xpulpv2(void *args) {

    int core_id = hal_core_id();

    plp_mat_mult_instance_q32 *a = (plp_mat_mult_instance_q32 *)args;

    const int32_t *__restrict__ pSrcA = a->pSrcA;
    const int32_t *__restrict__ pSrcB = a->pSrcB;
    uint32_t M = a->M;
    uint32_t N = a->N;
    uint32_t O = a->O;
    uint32_t shift = a->shift;
    uint32_t nPE = a->nPE;
    int32_t *__restrict__ pDstC = a->pDstC;

#define BASIC_VERSION // if used don't forget to also use the undefine at end of file
#ifdef BASIC_VERSION

    uint32_t m; // loop counter
    uint32_t n; // loop counter
    uint32_t o; // loop counter

    for (m = core_id; m < M; m += nPE) {
        for (o = 0; o < O; o++) {
            int32_t sum = 0;
            for (n = 0; n < N; n++) {
                int32_t valA = pSrcA[m * N + n];
                int32_t valB = pSrcB[o * N + n];
                sum += __ROUNDNORM_REG(valA * valB, shift);
            }
            pDstC[m * O + o] = sum;
        }
    }

#else

    // TODO hackathon

#endif
#undef BASIC_VERSION
}

/**
   @} end of MatMultTransKernels group
*/
