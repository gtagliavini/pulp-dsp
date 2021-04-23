/* ----------------------------------------------------------------------
 * Project:      PULP DSP Library
 * Title:        plp_copy_i32.c
 * Description:  Glue code for copying the elements of a 32-bit integer vector
 *
 * $Date:        02. June 2019
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna.
 *
 * Author: Xiaying Wang, ETH Zurich
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
 *
 * Notice: project inspired by ARM CMSIS DSP and parts of source code
 * ported and adopted for RISC-V PULP platform from ARM CMSIS DSP
 * released under Copyright (C) 2010-2019 ARM Limited or its affiliates
 * with Apache-2.0.
 */

#include "plp_math.h"

/**
  @ingroup groupSupport
 */

/**
  @defgroup Copy Vector Copy
  Copies sample by sample from source vector to destination vector.
  <pre>
  pDst[n] = pSrc[n];   0 <= n < blockSize.
  </pre>
  There are separate functions for floating point, integer, and fixed point 32- 16- 8-bit data
  types. For lower precision integers (16- and 8-bit), functions exploiting SIMD instructions are
  provided.

  The naming scheme of the functions follows the following pattern (for example plp_dot_prod_i32s):
  <pre>
  \<pulp\> _ \<function name\> _ \<data type\> \<precision\> \<method\> _ \<isa extension\>, with

  data type = {f, i, q} respectively for floats, integers, fixed points

  precision = {32, 16, 8} bits

  method = {s, p} respectively meaning single core or parallel multicore implementation.

  isa extension = rv32im, xpulpv2, etc. of which rv32im is the most general one.

  </pre>

 */

/**
  @addtogroup Copy
  @{
 */

/**
  @brief         Glue code for copying the elements of a 32-bit integer vector
  @param[in]     pSrc       points to input vector
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
*/

void plp_copy_i32(int32_t *__restrict__ pSrc, int32_t *__restrict__ pDst, uint32_t blockSize) {

    uint32_t blkCnt; /* Loop counter */

    if (hal_cluster_id() == ARCHI_FC_CID) {
        plp_copy_i32s_rv32im(pSrc, pDst, blockSize);
    } else {
        plp_copy_i32s_xpulpv2(pSrc, pDst, blockSize);
    }
}

/**
  @} end of Copy group
 */
