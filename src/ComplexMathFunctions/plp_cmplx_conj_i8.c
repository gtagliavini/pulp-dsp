/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_cmplx_conj_i8.c
 * Description:  32-bit float complex conjugate glue code
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
  @defgroup cmplx_conj Complex Conjugate
  Conjugates the elements of a complex data vector.
  The <code>pSrc</code> points to the source data and
  <code>pDst</code> points to the destination data where the result should be written.
  <code>numSamples</code> specifies the number of complex samples
  and the data in each array is stored in an interleaved fashion
  (real, imag, real, imag, ...).
  Each array has a total of <code>2*numSamples</code> values.
  The underlying algorithm is used:
  <pre>
  for (n = 0; n < numSamples; n++) {
      pDst[(2*n)  ] =  pSrc[(2*n)  ];    // real part
      pDst[(2*n)+1] = -pSrc[(2*n)+1];    // imag part
  }
  </pre>
 */

/**
  @addtogroup cmplx_conj
  @{
 */

/**
  @brief Glue code for complex conjugate of 8-bit integer vectors.
  @param[in]     pSrc        points to the input vector
  @param[out]    pDst        points to the output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none
 */

void plp_cmplx_conj_i8(const int8_t *__restrict__ pSrc,
                       int8_t *__restrict__ pDst,
                       uint32_t numSamples) {

    if (hal_cluster_id() == ARCHI_FC_CID) {
        plp_cmplx_conj_i8_rv32im(pSrc, pDst, numSamples);
        return;
    } else {
        plp_cmplx_conj_i8_xpulpv2(pSrc, pDst, numSamples);
    }
}

/**
  @} end of BasicDotProd group
 */
