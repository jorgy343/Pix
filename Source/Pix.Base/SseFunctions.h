#pragma once

/*
    Original copyright is below. This is a heavily modified version of Julien Pommier's
    SSE conversion of the Cephes formulas.
*/

/*
    Copyright (C) 2007 Julien Pommier

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    (this is the zlib license)
*/

#include <nmmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

#include "General.h"

inline void SinCos(__m128 x, __m128* s, __m128* c)
{
    __m128 xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
    __m128i emm0, emm2, emm4;
    sign_bit_sin = x;

    // x = abs(x)
    x = _mm_and_ps(x, _mm_castsi128_ps(_mm_set1_epi32(~0x80000000)));

    // Extract the sign bit (upper one).
    sign_bit_sin = _mm_and_ps(sign_bit_sin, _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));

    // Scale by 4/Pi.
    y = _mm_mul_ps(x, _mm_set1_ps(1.27323954473516f));

    // Store the integer part of y in emm2.
    emm2 = _mm_cvttps_epi32(y);

    // j=(j+1) & (~1) (see the cephes sources).
    emm2 = _mm_add_epi32(emm2, _mm_set1_epi32(1));
    emm2 = _mm_and_si128(emm2, _mm_set1_epi32(-2));
    y = _mm_cvtepi32_ps(emm2);

    emm4 = emm2;

    // Get the swap sign flag for the sine.
    emm0 = _mm_and_si128(emm2, _mm_set1_epi32(4));
    emm0 = _mm_slli_epi32(emm0, 29);

    __m128 swap_sign_bit_sin = _mm_castsi128_ps(emm0);

    // Get the polynom selection mask for the sine.
    emm2 = _mm_and_si128(emm2, _mm_set1_epi32(2));
    emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

    __m128 poly_mask = _mm_castsi128_ps(emm2);

    // The magic pass: "Extended precision modular arithmetic"
    // x = ((x - y * DP1) - y * DP2) - y * DP3;
    x = _mm_fmadd_ps(y, _mm_set1_ps(-0.78515625f), x);
    x = _mm_fmadd_ps(y, _mm_set1_ps(-2.4187564849853515625e-4f), x);
    x = _mm_fmadd_ps(y, _mm_set1_ps(-3.77489497744594108e-8f), x);

    emm4 = _mm_sub_epi32(emm4, _mm_set1_epi32(2));
    emm4 = _mm_andnot_si128(emm4, _mm_set1_epi32(4));
    emm4 = _mm_slli_epi32(emm4, 29);

    __m128 sign_bit_cos = _mm_castsi128_ps(emm4);
    sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);

    // z = x * x
    __m128 z = _mm_mul_ps(x, x);

    // Evaluate the first polynomial (0 <= x <= Pi/4).
    // y = ((2.443315711809948E-005 * z - 1.388731625493765E-003) * z + 4.166664568298827E-002) * z * z
    y = _mm_fmadd_ps(_mm_set1_ps(2.443315711809948E-005f), z, _mm_set1_ps(-1.388731625493765E-003f));
    y = _mm_fmadd_ps(y, z, _mm_set1_ps(4.166664568298827E-002f));

    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);

    // y = y + (-0.5 * z)
    y = _mm_fmadd_ps(_mm_set1_ps(-0.5f), z, y);

    // y = y + 1.0
    y = _mm_add_ps(y, _mm_set1_ps(1.0f));

    // Evaluate the second polynomial (Pi/4 <= x <= 0).
    // y = ((-1.9515295891E-4 * z + 8.3321608736E-3) * z - 1.6666654611E-1) * z * x
    __m128 y2 = _mm_fmadd_ps(_mm_set1_ps(-1.9515295891E-4f), z, _mm_set1_ps(8.3321608736E-3f));
    y2 = _mm_fmadd_ps(y2, z, _mm_set1_ps(-1.6666654611E-1f));

    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);

    // y = y + x
    y2 = _mm_add_ps(y2, x);

    // Select the correct result from the two polynoms.
    xmm3 = poly_mask;

    __m128 ysin2 = _mm_and_ps(xmm3, y2);
    __m128 ysin1 = _mm_andnot_ps(xmm3, y);

    y2 = _mm_sub_ps(y2, ysin2);
    y = _mm_sub_ps(y, ysin1);

    xmm1 = _mm_add_ps(ysin1, ysin2);
    xmm2 = _mm_add_ps(y, y2);

    // Update the sign.
    *s = _mm_xor_ps(xmm1, sign_bit_sin);
    *c = _mm_xor_ps(xmm2, sign_bit_cos);
}