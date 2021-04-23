/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_cmplx_mult_cmplx_f32.c
 * Description:  32-bit Floating-point complex by real multiplication
 *
 * $Date:        29. Jun 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna. All rights reserved.
 *
 * Author: Hanna Mueller, ETH Zurich
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
  @ingroup groupCmplxMath
 */

/**
  @defgroup CmplxByCmplxMult Complex-by-Complex Multiplication
  Multiplies a complex vector by another complex vector and generates a complex result.
  The data in the complex arrays is stored in an interleaved fashion
  (real, imag, real, imag, ...).
  The parameter <code>numSamples</code> represents the number of complex
  samples processed.  The complex arrays have a total of <code>2*numSamples</code>
  real values.
  The underlying algorithm is used:
  <pre>
  for (n = 0; n < numSamples; n++) {
      pDst[(2*n)+0] = pSrcA[(2*n)+0] * pSrcB[(2*n)+0] - pSrcA[(2*n)+1] * pSrcB[(2*n)+1];
      pDst[(2*n)+1] = pSrcA[(2*n)+0] * pSrcB[(2*n)+1] + pSrcA[(2*n)+1] * pSrcB[(2*n)+0];
  }
  </pre>
  There are separate functions for floating point, integer, and fixed point 32- 16- 8-bit data
  types.
 */

/**
  @addtogroup CmplxByCmplxMult
  @{
 */

/**
  @brief         Floating-point complex-by-complex multiplication.
  @param[in]     pSrcA       points to first input vector
  @param[in]     pSrcB       points to second input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none
 */

void plp_cmplx_mult_cmplx_f32(const float32_t *__restrict__ pSrcA,
                              const float32_t *__restrict__ pSrcB,
                              float32_t *__restrict__ pDst,
                              uint32_t numSamples) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        printf("error: FC doesn't have FPU\n");
        return;
    } else {
        plp_cmplx_mult_cmplx_f32_xpulpv2(pSrcA, pSrcB, pDst, numSamples);
    }
}

/**
  @} end of BasicDotProd group
 */
