/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_mult_cmplx_stride_q16_parallel.c
 * Description:  parallel 16-bit fix-point complex strided matrix matrix multiplication glue code
 *
 * $Date:        18. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and Ubiversity of Bologna. All rights reserved.
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
  @ingroup groupMatrixStride
 */

/**
  @addtogroup MatMultCmplxStride
  @{
 */

/**
  @brief      Glue code of parallel strided matrix matrix multiplication for complex 16-bit
  fix-point
  @param[in]  pSrcA   Points to the first input matrix of shape MxN
  @param[in]  pSrcB   Points to the second input matrix of shape NxO
  @param[in]  M       Height of matrix SrcA and DstC
  @param[in]  N       Width of matrix SrcA and height of matrix SrcB
  @param[in]  O       Width of matrix SrcB and DstC
  @param[in]  strideA Stride of input matrix A (elements between each row)
  @param[in]  strideB Stride of input matrix B (elements between each row)
  @param[in]  strideC Stride of output matrix C (Elements between each row)
  @param[in]  shift   Amount to shift the result of each multiplication ot the right
  @param[in]  nPE     Number of cores to use for computation
  @param[out] pDstC   Points to the output matrix of shape MxO
  @return     none

  @par Fix-Point
  Fix-Point and Shifting
  The result will be shifted by the parameter `shift` to the right (which corresponds to a
  multiplication by `2^-shift`). Assume that matrix A is represente as `pSrcA * 2^-x` and matrix B
  as `pSrcB * 2^-y` (which means that A has `x`, and B has `y` bits after the binary point). Then,
  the output matrix C is represented as `pDstC * 2^-(x + y - shift)`. The output matrix is also
  stored with the same number of bits as the inputs. Set the `shift` parameter such that no overflow
  occurrs.
 */

void plp_mat_mult_cmplx_stride_q16_parallel(const int16_t *__restrict__ pSrcA,
                                            const int16_t *__restrict__ pSrcB,
                                            uint32_t M,
                                            uint32_t N,
                                            uint32_t O,
                                            uint32_t strideA,
                                            uint32_t strideB,
                                            uint32_t strideC,
                                            uint32_t shift,
                                            uint32_t nPE,
                                            int16_t *__restrict__ pDstC) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("parallel processing supported only for cluster side\n");
        return;
    } else {
        plp_mat_mult_cmplx_stride_instance_q16 args = { .pSrcA = pSrcA,
                                                        .pSrcB = pSrcB,
                                                        .M = M,
                                                        .N = N,
                                                        .O = O,
                                                        .strideA = strideA,
                                                        .strideB = strideB,
                                                        .strideC = strideC,
                                                        .shift = shift,
                                                        .nPE = nPE,
                                                        .pDstC = pDstC };

        hal_cl_team_fork(nPE, plp_mat_mult_cmplx_stride_q16p_xpulpv2, (void *)&args);
    }
}

/**
  @} end of MatMultCmplxStride group
 */
