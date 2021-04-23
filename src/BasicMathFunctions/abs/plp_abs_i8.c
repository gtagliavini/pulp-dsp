/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_abs_i8.c
 * Description:  8-bit integer vector absolute value glue code
 *
 * $Date:        30. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna. 
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
  @ingroup groupMath
 */

/**
  @addtogroup BasicAbs
  @{
 */

/**
  @brief Glue code for absolute value of 8-bit integer vectors.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void plp_abs_i8(const int8_t * pSrc,
                 int8_t * pDst,
                 uint32_t blockSize) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
      plp_abs_i8s_rv32im(pSrc, pDst, blockSize);
    } else {
      plp_abs_i8s_xpulpv2(pSrc, pDst, blockSize);
    }
}

/**
  @} end of BasicAbs group
 */
