/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_scale_stride_f32_parallel.c
 * Description:  parallel 32-bit floating-point strided matrix scale glue code
 *
 * $Date:        6. July 2020
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
  @ingroup groupMatrixStride
 */

/**
  @addtogroup MatScaleStride
  @{
 */

/**
  @brief Glue code for parallel strided matrix scale of 32-bit floating-point matrices.
  @param[in]  pSrc        Points to the input matrix
  @param[in]  M           Height of both matrices
  @param[in]  N           Width of both matrices
  @param[in]  strideSrc   Stride of input matrix (elements between each row)
  @param[in]  strideDst   Stride of output matrix (elements between each row)
  @param[in]  scaleFactor Factor to mulitply all elements
  @param[in]  nPE         Number of cores to use for computation
  @param[out] pDst        Points to the output matrix
  @return     none
 */

void plp_mat_scale_stride_f32_parallel(const float *__restrict__ pSrc,
                                       uint32_t M,
                                       uint32_t N,
                                       uint32_t strideSrc,
                                       uint32_t strideDst,
                                       float scaleFactor,
                                       uint32_t nPE,
                                       float *__restrict__ pDst) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("parallel and floating-point processing supported only for cluster side\n");
        return;
    } else {
        plp_mat_scale_stride_instance_f32 args = { .pSrc = pSrc,
                                                   .M = M,
                                                   .N = N,
                                                   .strideSrc = strideSrc,
                                                   .strideDst = strideDst,
                                                   .scaleFactor = scaleFactor,
                                                   .nPE = nPE,
                                                   .pDst = pDst };

        hal_cl_team_fork(nPE, plp_mat_scale_stride_f32p_xpulpv2, (void *)&args);
    }
}

/**
  @} end of MatScaleStride group
 */
