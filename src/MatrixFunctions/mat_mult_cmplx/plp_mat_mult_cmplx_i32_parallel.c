/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_mult_cmplx_i32_parallel.c
 * Description:  parallel 16-bit integer complex matrix matrix multiplication glue code
 *
 * $Date:        17. July 2020
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
  @ingroup groupMatrix
 */

/**
  @addtogroup MatMultCmplx
  @{
 */

/**
  @brief      Glue code of parallel matrix matrix multiplication for complex 32-bit integers
  @param[in]  pSrcA Points to the first input matrix of shape MxN
  @param[in]  pSrcB Points to the second input matrix of shape NxO
  @param[in]  M     Height of matrix SrcA and DstC
  @param[in]  N     Width of matrix SrcA and height of matrix SrcB
  @param[in]  O     Width of matrix SrcB and DstC
  @param[in]  nPE   Number of cores to use for computation
  @param[out] pDstC Points to the output matrix of shape MxO
  @return     none
 */

void plp_mat_mult_cmplx_i32_parallel(const int32_t *__restrict__ pSrcA,
                                     const int32_t *__restrict__ pSrcB,
                                     uint32_t M,
                                     uint32_t N,
                                     uint32_t O,
                                     uint32_t nPE,
                                     int32_t *__restrict__ pDstC) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("parallel processing supported only for cluster side\n");
        return;
    } else {
        plp_mat_mult_cmplx_instance_i32 args = {
            .pSrcA = pSrcA, .pSrcB = pSrcB, .M = M, .N = N, .O = O, .nPE = nPE, .pDstC = pDstC
        };

        hal_cl_team_fork(nPE, plp_mat_mult_cmplx_i32p_xpulpv2, (void *)&args);
    }
}

/**
  @} end of MatMultCmplx group
 */
