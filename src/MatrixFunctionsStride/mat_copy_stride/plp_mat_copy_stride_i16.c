/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_copy_stride_i16.c
 * Description:  16-bit integer strided matrix copy glue code
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
  @ingroup groupMatrixStride
 */

/**
  @defgroup MatCopyStride Strided Matrix Copy
  This module contains the glue code for copying strided matrices. The kernel codes (kernels) are
  located in the module @ref MatCopyStrideKernels.

  The source and destination matrix can have different strides.

  There are functions for integer 32- 16- and 8-bit data types, as well as for floating-point. The
  naming scheme of the functions follows the following pattern (for example
  `plp_mat_copy_stride_i32`):

      `plp_<function name>_<data type><precision>[_parallel]`

  name          | description
  ------------- | ---------------------------------------------------------
  function_name | `mat_copy_stride`
  data type     | {f, i, q} respectively for floats, integers, fixed points
  precision     | {32, 16, 8} bits

  The `stride` argument tells how many elements are in between the start of each row of the matrix.
  In other words, it is the width of the original matrix. @ref groupMatrixStride
 */

/**
  @addtogroup MatCopyStride
  @{
 */

/**
  @brief      Glue code to copy an MxN strided 16-bit integers matrix
  @param[in]  pSrc      Points to the input matrix of shape MxN
  @param[in]  M         Height of both matrices
  @param[in]  N         Width of both matrices
  @param[in]  strideSrc Stride of the input matrix (elements between each row)
  @param[in]  strideDst Stride of the output matrix (elements between each row)
  @param[out] pDst      Points to the output matrix of shape MxN
  @return     none
 */

void plp_mat_copy_stride_i16(const int16_t *__restrict__ pSrc,
                             uint32_t M,
                             uint32_t N,
                             uint32_t strideSrc,
                             uint32_t strideDst,
                             int16_t *__restrict__ pDst) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        plp_mat_copy_stride_i16s_rv32im(pSrc, M, N, strideSrc, strideDst, pDst);
    } else {
        plp_mat_copy_stride_i16s_xpulpv2(pSrc, M, N, strideSrc, strideDst, pDst);
    }
}

/**
  @} end of MatCopyStride group
 */
