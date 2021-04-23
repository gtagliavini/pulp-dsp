/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_trans_f32_parallel.c
 * Description:  parallel 32-bit floating-point matrix transpose glue code
 *
 * $Date:        14. July 2020
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
  @addtogroup MatTrans
  @{
 */

/**
  @brief Glue code for parallel matrix transpose of 32-bit floating-point matrices.
  @param[in]  pSrc Points to the input matrix of shape MxN
  @param[in]  M    Height of the input matrix and width of the output matrix
  @param[in]  N    Width of the input matrix and height of the output matrix
  @param[in]  nPE  Number of cores to use for computation
  @param[out] pDst Points to the output matrix of shape NxM
  @return     none

  @par This function will use plp_mat_trans_i32p_xpulpv2 for its computation.
 */

void plp_mat_trans_f32_parallel(const float *__restrict__ pSrc,
                                uint32_t M,
                                uint32_t N,
                                uint32_t nPE,
                                float *__restrict__ pDst) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("parallel and floating-point processing supported only for cluster side\n");
        return;
    } else {
        plp_mat_trans_instance_i32 args = {
            .pSrc = (int32_t *)pSrc, .M = M, .N = N, .nPE = nPE, .pDst = (int32_t *)pDst
        };

        hal_cl_team_fork(nPE, plp_mat_trans_i32p_xpulpv2, (void *)&args);
    }
}

/**
  @} end of MatTrans group
 */
