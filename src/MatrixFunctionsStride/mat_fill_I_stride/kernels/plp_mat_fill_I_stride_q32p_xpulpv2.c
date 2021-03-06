/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_fill_I_stride_q32p_xpulpv2.c
 * Description:  parallel 32-bit fix-point strided identity matrix creation for XPULPV2
 *
 * $Date:        strided identity matrix creation
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
  @ingroup MatFillIStride
 */

/**
  @addtogroup MatFillIStrideKernels
  @{
 */

/**
  @brief      Create a strided 32-bit fix-point identity matrix on XpulpV2 in parallel
  @param[in]  args  pointer to plp_mat_mat_fill_I_stride_instance_q32 struct initialized by
                    plp_mat_fill_I_stride_q32_parallel
  @return     none

  @par Fix-Point
  The diagonal elements will be filled with the value: `1 << fracBits`.
 */

void plp_mat_fill_I_stride_q32p_xpulpv2(void *args) {

    int core_id = hal_core_id();

    plp_mat_fill_I_stride_instance_q32 *a = (plp_mat_fill_I_stride_instance_q32 *)args;

    uint32_t N = a->N;
    uint32_t stride = a->stride;
    int32_t fracBits = a->fracBits;
    uint32_t nPE = a->nPE;
    int32_t *__restrict__ pDst = a->pDst;

#define BASIC_VERSION // if used don't forget to also use the undefine at end of file
#ifdef BASIC_VERSION

    for (int i = core_id; i < N; i += nPE) {
        for (int j = 0; j < N; j++) {
            pDst[i * stride + j] = (int32_t)(i == j) << fracBits;
        }
    }

#else

    // TODO: Hackathon

#endif
#undef BASIC_VERSION
}

/**
   @} end of MatFillIStrideKernels group
*/
