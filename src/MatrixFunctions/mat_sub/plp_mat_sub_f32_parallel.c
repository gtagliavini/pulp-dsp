/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_sub_f32_parallel.c
 * Description:  parallel 32-bit floating-point matrix subtraction glue code
 *
 * $Date:        1. July 2020
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
  @ingroup groupMatrix
 */

/**
  @addtogroup MatSub
  @{
 */

/**
  @brief Glue code for parallel matrix subtraction of 32-bit floating-point matrices.
  @param[in]  pSrcA   Points to the first input matrix
  @param[in]  pSrcB   Points to the second input matrix
  @param[in]  M       Height of all matrices
  @param[in]  N       Width of all matrices
  @param[in]  nPE     Number of cores to use for computation
  @param[out] pDst    Points to the output matrix
  @return     none
 */

void plp_mat_sub_f32_parallel(const float *__restrict__ pSrcA,
                              const float *__restrict__ pSrcB,
                              uint32_t M,
                              uint32_t N,
                              uint32_t nPE,
                              float *__restrict__ pDst) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("parallel and floating-point processing supported only for cluster side\n");
        return;
    } else {
        plp_mat_sub_instance_f32 args = {
            .pSrcA = pSrcA, .pSrcB = pSrcB, .M = M, .N = N, .nPE = nPE, .pDst = pDst
        };

        hal_cl_team_fork(nPE, plp_mat_sub_f32p_xpulpv2, (void *)&args);
    }
}

/**
  @} end of MatSub group
 */
