/* MIT License
 *
 * Copyright (c) 2016-2022 INRIA, CMU and Microsoft Corporation
 * Copyright (c) 2022-2023 HACL* Contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Hacl_P521.h"

#include "internal/Hacl_Krmllib.h"
#include "internal/Hacl_Bignum_Base.h"

static inline uint64_t
bn_is_eq_mask(uint64_t *x, uint64_t *y)
{
    uint64_t mask = 0xFFFFFFFFFFFFFFFFULL;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t uu____0 = FStar_UInt64_eq_mask(x[i], y[i]);
                    mask = uu____0 & mask;);
    uint64_t mask1 = mask;
    return mask1;
}

static inline void
bn_cmovznz(uint64_t *a, uint64_t b, uint64_t *c, uint64_t *d)
{
    uint64_t mask = ~FStar_UInt64_eq_mask(b, 0ULL);
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = a;
                    uint64_t uu____0 = c[i];
                    uint64_t x = uu____0 ^ (mask & (d[i] ^ uu____0));
                    os[i] = x;);
}

static inline void
bn_add_mod(uint64_t *a, uint64_t *b, uint64_t *c, uint64_t *d)
{
    uint64_t c10 = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = c[4U * i];
                    uint64_t t20 = d[4U * i];
                    uint64_t *res_i0 = a + 4U * i;
                    c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t1, t20, res_i0);
                    uint64_t t10 = c[4U * i + 1U];
                    uint64_t t21 = d[4U * i + 1U];
                    uint64_t *res_i1 = a + 4U * i + 1U;
                    c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t10, t21, res_i1);
                    uint64_t t11 = c[4U * i + 2U];
                    uint64_t t22 = d[4U * i + 2U];
                    uint64_t *res_i2 = a + 4U * i + 2U;
                    c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t11, t22, res_i2);
                    uint64_t t12 = c[4U * i + 3U];
                    uint64_t t2 = d[4U * i + 3U];
                    uint64_t *res_i = a + 4U * i + 3U;
                    c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t12, t2, res_i););
    {
        uint64_t t1 = c[8U];
        uint64_t t2 = d[8U];
        uint64_t *res_i = a + 8U;
        c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t1, t2, res_i);
    }
    uint64_t c0 = c10;
    uint64_t tmp[9U] = { 0U };
    uint64_t c1 = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = a[4U * i];
                    uint64_t t20 = b[4U * i];
                    uint64_t *res_i0 = tmp + 4U * i;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t20, res_i0);
                    uint64_t t10 = a[4U * i + 1U];
                    uint64_t t21 = b[4U * i + 1U];
                    uint64_t *res_i1 = tmp + 4U * i + 1U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t10, t21, res_i1);
                    uint64_t t11 = a[4U * i + 2U];
                    uint64_t t22 = b[4U * i + 2U];
                    uint64_t *res_i2 = tmp + 4U * i + 2U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t11, t22, res_i2);
                    uint64_t t12 = a[4U * i + 3U];
                    uint64_t t2 = b[4U * i + 3U];
                    uint64_t *res_i = tmp + 4U * i + 3U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t12, t2, res_i););
    {
        uint64_t t1 = a[8U];
        uint64_t t2 = b[8U];
        uint64_t *res_i = tmp + 8U;
        c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t2, res_i);
    }
    uint64_t c11 = c1;
    uint64_t c2 = c0 - c11;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = a;
                    uint64_t x = (c2 & a[i]) | (~c2 & tmp[i]);
                    os[i] = x;);
}

static inline uint64_t
bn_sub(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t c1 = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = b[4U * i];
                    uint64_t t20 = c[4U * i];
                    uint64_t *res_i0 = a + 4U * i;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t20, res_i0);
                    uint64_t t10 = b[4U * i + 1U];
                    uint64_t t21 = c[4U * i + 1U];
                    uint64_t *res_i1 = a + 4U * i + 1U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t10, t21, res_i1);
                    uint64_t t11 = b[4U * i + 2U];
                    uint64_t t22 = c[4U * i + 2U];
                    uint64_t *res_i2 = a + 4U * i + 2U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t11, t22, res_i2);
                    uint64_t t12 = b[4U * i + 3U];
                    uint64_t t2 = c[4U * i + 3U];
                    uint64_t *res_i = a + 4U * i + 3U;
                    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t12, t2, res_i););
    {
        uint64_t t1 = b[8U];
        uint64_t t2 = c[8U];
        uint64_t *res_i = a + 8U;
        c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t2, res_i);
    }
    uint64_t c10 = c1;
    return c10;
}

static inline void
bn_sub_mod(uint64_t *a, uint64_t *b, uint64_t *c, uint64_t *d)
{
    uint64_t c10 = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = c[4U * i];
                    uint64_t t20 = d[4U * i];
                    uint64_t *res_i0 = a + 4U * i;
                    c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t1, t20, res_i0);
                    uint64_t t10 = c[4U * i + 1U];
                    uint64_t t21 = d[4U * i + 1U];
                    uint64_t *res_i1 = a + 4U * i + 1U;
                    c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t10, t21, res_i1);
                    uint64_t t11 = c[4U * i + 2U];
                    uint64_t t22 = d[4U * i + 2U];
                    uint64_t *res_i2 = a + 4U * i + 2U;
                    c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t11, t22, res_i2);
                    uint64_t t12 = c[4U * i + 3U];
                    uint64_t t2 = d[4U * i + 3U];
                    uint64_t *res_i = a + 4U * i + 3U;
                    c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t12, t2, res_i););
    {
        uint64_t t1 = c[8U];
        uint64_t t2 = d[8U];
        uint64_t *res_i = a + 8U;
        c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t1, t2, res_i);
    }
    uint64_t c0 = c10;
    uint64_t tmp[9U] = { 0U };
    uint64_t c1 = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = a[4U * i];
                    uint64_t t20 = b[4U * i];
                    uint64_t *res_i0 = tmp + 4U * i;
                    c1 = Lib_IntTypes_Intrinsics_add_carry_u64(c1, t1, t20, res_i0);
                    uint64_t t10 = a[4U * i + 1U];
                    uint64_t t21 = b[4U * i + 1U];
                    uint64_t *res_i1 = tmp + 4U * i + 1U;
                    c1 = Lib_IntTypes_Intrinsics_add_carry_u64(c1, t10, t21, res_i1);
                    uint64_t t11 = a[4U * i + 2U];
                    uint64_t t22 = b[4U * i + 2U];
                    uint64_t *res_i2 = tmp + 4U * i + 2U;
                    c1 = Lib_IntTypes_Intrinsics_add_carry_u64(c1, t11, t22, res_i2);
                    uint64_t t12 = a[4U * i + 3U];
                    uint64_t t2 = b[4U * i + 3U];
                    uint64_t *res_i = tmp + 4U * i + 3U;
                    c1 = Lib_IntTypes_Intrinsics_add_carry_u64(c1, t12, t2, res_i););
    {
        uint64_t t1 = a[8U];
        uint64_t t2 = b[8U];
        uint64_t *res_i = tmp + 8U;
        c1 = Lib_IntTypes_Intrinsics_add_carry_u64(c1, t1, t2, res_i);
    }
    uint64_t c11 = c1;
    KRML_MAYBE_UNUSED_VAR(c11);
    uint64_t c2 = 0ULL - c0;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = a;
                    uint64_t x = (c2 & tmp[i]) | (~c2 & a[i]);
                    os[i] = x;);
}

static inline void
bn_mul(uint64_t *a, uint64_t *b, uint64_t *c)
{
    memset(a, 0U, 18U * sizeof(uint64_t));
    KRML_MAYBE_FOR9(
        i0,
        0U,
        9U,
        1U,
        uint64_t bj = c[i0];
        uint64_t *res_j = a + i0;
        uint64_t c1 = 0ULL;
        KRML_MAYBE_FOR2(i,
                        0U,
                        2U,
                        1U,
                        uint64_t a_i = b[4U * i];
                        uint64_t *res_i0 = res_j + 4U * i;
                        c1 = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, bj, c1, res_i0);
                        uint64_t a_i0 = b[4U * i + 1U];
                        uint64_t *res_i1 = res_j + 4U * i + 1U;
                        c1 = Hacl_Bignum_Base_mul_wide_add2_u64(a_i0, bj, c1, res_i1);
                        uint64_t a_i1 = b[4U * i + 2U];
                        uint64_t *res_i2 = res_j + 4U * i + 2U;
                        c1 = Hacl_Bignum_Base_mul_wide_add2_u64(a_i1, bj, c1, res_i2);
                        uint64_t a_i2 = b[4U * i + 3U];
                        uint64_t *res_i = res_j + 4U * i + 3U;
                        c1 = Hacl_Bignum_Base_mul_wide_add2_u64(a_i2, bj, c1, res_i););
        {
            uint64_t a_i = b[8U];
            uint64_t *res_i = res_j + 8U;
            c1 = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, bj, c1, res_i);
        } uint64_t r = c1;
        a[9U + i0] = r;);
}

static inline void
bn_sqr(uint64_t *a, uint64_t *b)
{
    memset(a, 0U, 18U * sizeof(uint64_t));
    KRML_MAYBE_FOR9(
        i0,
        0U,
        9U,
        1U,
        uint64_t *ab = b;
        uint64_t a_j = b[i0];
        uint64_t *res_j = a + i0;
        uint64_t c = 0ULL;
        for (uint32_t i = 0U; i < i0 / 4U; i++) {
            uint64_t a_i = ab[4U * i];
            uint64_t *res_i0 = res_j + 4U * i;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, a_j, c, res_i0);
            uint64_t a_i0 = ab[4U * i + 1U];
            uint64_t *res_i1 = res_j + 4U * i + 1U;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i0, a_j, c, res_i1);
            uint64_t a_i1 = ab[4U * i + 2U];
            uint64_t *res_i2 = res_j + 4U * i + 2U;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i1, a_j, c, res_i2);
            uint64_t a_i2 = ab[4U * i + 3U];
            uint64_t *res_i = res_j + 4U * i + 3U;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i2, a_j, c, res_i);
        } for (uint32_t i = i0 / 4U * 4U; i < i0; i++) {
            uint64_t a_i = ab[i];
            uint64_t *res_i = res_j + i;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, a_j, c, res_i);
        } uint64_t r = c;
        a[i0 + i0] = r;);
    uint64_t c0 = Hacl_Bignum_Addition_bn_add_eq_len_u64(18U, a, a, a);
    KRML_MAYBE_UNUSED_VAR(c0);
    uint64_t tmp[18U] = { 0U };
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    FStar_UInt128_uint128 res = FStar_UInt128_mul_wide(b[i], b[i]);
                    uint64_t hi = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res, 64U));
                    uint64_t lo = FStar_UInt128_uint128_to_uint64(res);
                    tmp[2U * i] = lo;
                    tmp[2U * i + 1U] = hi;);
    uint64_t c1 = Hacl_Bignum_Addition_bn_add_eq_len_u64(18U, a, tmp, a);
    KRML_MAYBE_UNUSED_VAR(c1);
}

static inline void
bn_to_bytes_be(uint8_t *a, uint64_t *b)
{
    uint8_t tmp[72U] = { 0U };
    KRML_MAYBE_FOR9(i, 0U, 9U, 1U, store64_be(tmp + i * 8U, b[9U - i - 1U]););
    memcpy(a, tmp + 6U, 66U * sizeof(uint8_t));
}

static inline void
bn_from_bytes_be(uint64_t *a, uint8_t *b)
{
    uint8_t tmp[72U] = { 0U };
    memcpy(tmp + 6U, b, 66U * sizeof(uint8_t));
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = a;
                    uint64_t u = load64_be(tmp + (9U - i - 1U) * 8U);
                    uint64_t x = u;
                    os[i] = x;);
}

static inline void
p521_make_prime(uint64_t *n)
{
    n[0U] = 0xffffffffffffffffULL;
    n[1U] = 0xffffffffffffffffULL;
    n[2U] = 0xffffffffffffffffULL;
    n[3U] = 0xffffffffffffffffULL;
    n[4U] = 0xffffffffffffffffULL;
    n[5U] = 0xffffffffffffffffULL;
    n[6U] = 0xffffffffffffffffULL;
    n[7U] = 0xffffffffffffffffULL;
    n[8U] = 0x1ffULL;
}

static inline void
p521_make_order(uint64_t *n)
{
    n[0U] = 0xbb6fb71e91386409ULL;
    n[1U] = 0x3bb5c9b8899c47aeULL;
    n[2U] = 0x7fcc0148f709a5d0ULL;
    n[3U] = 0x51868783bf2f966bULL;
    n[4U] = 0xfffffffffffffffaULL;
    n[5U] = 0xffffffffffffffffULL;
    n[6U] = 0xffffffffffffffffULL;
    n[7U] = 0xffffffffffffffffULL;
    n[8U] = 0x1ffULL;
}

static inline void
p521_make_a_coeff(uint64_t *a)
{
    a[0U] = 0xfe7fffffffffffffULL;
    a[1U] = 0xffffffffffffffffULL;
    a[2U] = 0xffffffffffffffffULL;
    a[3U] = 0xffffffffffffffffULL;
    a[4U] = 0xffffffffffffffffULL;
    a[5U] = 0xffffffffffffffffULL;
    a[6U] = 0xffffffffffffffffULL;
    a[7U] = 0xffffffffffffffffULL;
    a[8U] = 0x01ffULL;
}

static inline void
p521_make_b_coeff(uint64_t *b)
{
    b[0U] = 0x8014654fae586387ULL;
    b[1U] = 0x78f7a28fea35a81fULL;
    b[2U] = 0x839ab9efc41e961aULL;
    b[3U] = 0xbd8b29605e9dd8dfULL;
    b[4U] = 0xf0ab0c9ca8f63f49ULL;
    b[5U] = 0xf9dc5a44c8c77884ULL;
    b[6U] = 0x77516d392dccd98aULL;
    b[7U] = 0x0fc94d10d05b42a0ULL;
    b[8U] = 0x4dULL;
}

static inline void
p521_make_g_x(uint64_t *n)
{
    n[0U] = 0xb331a16381adc101ULL;
    n[1U] = 0x4dfcbf3f18e172deULL;
    n[2U] = 0x6f19a459e0c2b521ULL;
    n[3U] = 0x947f0ee093d17fd4ULL;
    n[4U] = 0xdd50a5af3bf7f3acULL;
    n[5U] = 0x90fc1457b035a69eULL;
    n[6U] = 0x214e32409c829fdaULL;
    n[7U] = 0xe6cf1f65b311cadaULL;
    n[8U] = 0x74ULL;
}

static inline void
p521_make_g_y(uint64_t *n)
{
    n[0U] = 0x28460e4a5a9e268eULL;
    n[1U] = 0x20445f4a3b4fe8b3ULL;
    n[2U] = 0xb09a9e3843513961ULL;
    n[3U] = 0x2062a85c809fd683ULL;
    n[4U] = 0x164bf7394caf7a13ULL;
    n[5U] = 0x340bd7de8b939f33ULL;
    n[6U] = 0xeccc7aa224abcda2ULL;
    n[7U] = 0x022e452fda163e8dULL;
    n[8U] = 0x1e0ULL;
}

static inline void
p521_make_fmont_R2(uint64_t *n)
{
    n[0U] = 0x0ULL;
    n[1U] = 0x400000000000ULL;
    n[2U] = 0x0ULL;
    n[3U] = 0x0ULL;
    n[4U] = 0x0ULL;
    n[5U] = 0x0ULL;
    n[6U] = 0x0ULL;
    n[7U] = 0x0ULL;
    n[8U] = 0x0ULL;
}

static inline void
p521_make_fzero(uint64_t *n)
{
    memset(n, 0U, 9U * sizeof(uint64_t));
    n[0U] = 0ULL;
}

static inline void
p521_make_fone(uint64_t *n)
{
    n[0U] = 0x80000000000000ULL;
    n[1U] = 0x0ULL;
    n[2U] = 0x0ULL;
    n[3U] = 0x0ULL;
    n[4U] = 0x0ULL;
    n[5U] = 0x0ULL;
    n[6U] = 0x0ULL;
    n[7U] = 0x0ULL;
    n[8U] = 0x0ULL;
}

static inline void
p521_make_qone(uint64_t *f)
{
    f[0U] = 0xfb80000000000000ULL;
    f[1U] = 0x28a2482470b763cdULL;
    f[2U] = 0x17e2251b23bb31dcULL;
    f[3U] = 0xca4019ff5b847b2dULL;
    f[4U] = 0x2d73cbc3e206834ULL;
    f[5U] = 0x0ULL;
    f[6U] = 0x0ULL;
    f[7U] = 0x0ULL;
    f[8U] = 0x0ULL;
}

static inline void
fmont_reduction(uint64_t *res, uint64_t *x)
{
    uint64_t n[9U] = { 0U };
    p521_make_prime(n);
    uint64_t c0 = 0ULL;
    KRML_MAYBE_FOR9(
        i0,
        0U,
        9U,
        1U,
        uint64_t qj = 1ULL * x[i0];
        uint64_t *res_j0 = x + i0;
        uint64_t c = 0ULL;
        KRML_MAYBE_FOR2(i,
                        0U,
                        2U,
                        1U,
                        uint64_t a_i = n[4U * i];
                        uint64_t *res_i0 = res_j0 + 4U * i;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, qj, c, res_i0);
                        uint64_t a_i0 = n[4U * i + 1U];
                        uint64_t *res_i1 = res_j0 + 4U * i + 1U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i0, qj, c, res_i1);
                        uint64_t a_i1 = n[4U * i + 2U];
                        uint64_t *res_i2 = res_j0 + 4U * i + 2U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i1, qj, c, res_i2);
                        uint64_t a_i2 = n[4U * i + 3U];
                        uint64_t *res_i = res_j0 + 4U * i + 3U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i2, qj, c, res_i););
        {
            uint64_t a_i = n[8U];
            uint64_t *res_i = res_j0 + 8U;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, qj, c, res_i);
        } uint64_t r = c;
        uint64_t c1 = r;
        uint64_t *resb = x + 9U + i0;
        uint64_t res_j = x[9U + i0];
        c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, c1, res_j, resb););
    memcpy(res, x + 9U, 9U * sizeof(uint64_t));
    uint64_t c00 = c0;
    uint64_t tmp[9U] = { 0U };
    uint64_t c = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = res[4U * i];
                    uint64_t t20 = n[4U * i];
                    uint64_t *res_i0 = tmp + 4U * i;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, res_i0);
                    uint64_t t10 = res[4U * i + 1U];
                    uint64_t t21 = n[4U * i + 1U];
                    uint64_t *res_i1 = tmp + 4U * i + 1U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, res_i1);
                    uint64_t t11 = res[4U * i + 2U];
                    uint64_t t22 = n[4U * i + 2U];
                    uint64_t *res_i2 = tmp + 4U * i + 2U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, res_i2);
                    uint64_t t12 = res[4U * i + 3U];
                    uint64_t t2 = n[4U * i + 3U];
                    uint64_t *res_i = tmp + 4U * i + 3U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, res_i););
    {
        uint64_t t1 = res[8U];
        uint64_t t2 = n[8U];
        uint64_t *res_i = tmp + 8U;
        c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, res_i);
    }
    uint64_t c1 = c;
    uint64_t c2 = c00 - c1;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = res;
                    uint64_t x1 = (c2 & res[i]) | (~c2 & tmp[i]);
                    os[i] = x1;);
}

static inline void
qmont_reduction(uint64_t *res, uint64_t *x)
{
    uint64_t n[9U] = { 0U };
    p521_make_order(n);
    uint64_t c0 = 0ULL;
    KRML_MAYBE_FOR9(
        i0,
        0U,
        9U,
        1U,
        uint64_t qj = 2103001588584519111ULL * x[i0];
        uint64_t *res_j0 = x + i0;
        uint64_t c = 0ULL;
        KRML_MAYBE_FOR2(i,
                        0U,
                        2U,
                        1U,
                        uint64_t a_i = n[4U * i];
                        uint64_t *res_i0 = res_j0 + 4U * i;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, qj, c, res_i0);
                        uint64_t a_i0 = n[4U * i + 1U];
                        uint64_t *res_i1 = res_j0 + 4U * i + 1U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i0, qj, c, res_i1);
                        uint64_t a_i1 = n[4U * i + 2U];
                        uint64_t *res_i2 = res_j0 + 4U * i + 2U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i1, qj, c, res_i2);
                        uint64_t a_i2 = n[4U * i + 3U];
                        uint64_t *res_i = res_j0 + 4U * i + 3U;
                        c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i2, qj, c, res_i););
        {
            uint64_t a_i = n[8U];
            uint64_t *res_i = res_j0 + 8U;
            c = Hacl_Bignum_Base_mul_wide_add2_u64(a_i, qj, c, res_i);
        } uint64_t r = c;
        uint64_t c1 = r;
        uint64_t *resb = x + 9U + i0;
        uint64_t res_j = x[9U + i0];
        c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, c1, res_j, resb););
    memcpy(res, x + 9U, 9U * sizeof(uint64_t));
    uint64_t c00 = c0;
    uint64_t tmp[9U] = { 0U };
    uint64_t c = 0ULL;
    KRML_MAYBE_FOR2(i,
                    0U,
                    2U,
                    1U,
                    uint64_t t1 = res[4U * i];
                    uint64_t t20 = n[4U * i];
                    uint64_t *res_i0 = tmp + 4U * i;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, res_i0);
                    uint64_t t10 = res[4U * i + 1U];
                    uint64_t t21 = n[4U * i + 1U];
                    uint64_t *res_i1 = tmp + 4U * i + 1U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, res_i1);
                    uint64_t t11 = res[4U * i + 2U];
                    uint64_t t22 = n[4U * i + 2U];
                    uint64_t *res_i2 = tmp + 4U * i + 2U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, res_i2);
                    uint64_t t12 = res[4U * i + 3U];
                    uint64_t t2 = n[4U * i + 3U];
                    uint64_t *res_i = tmp + 4U * i + 3U;
                    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, res_i););
    {
        uint64_t t1 = res[8U];
        uint64_t t2 = n[8U];
        uint64_t *res_i = tmp + 8U;
        c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, res_i);
    }
    uint64_t c1 = c;
    uint64_t c2 = c00 - c1;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = res;
                    uint64_t x1 = (c2 & res[i]) | (~c2 & tmp[i]);
                    os[i] = x1;);
}

static inline uint64_t
bn_is_lt_prime_mask(uint64_t *f)
{
    uint64_t tmp[9U] = { 0U };
    p521_make_prime(tmp);
    uint64_t c = bn_sub(tmp, f, tmp);
    uint64_t m = FStar_UInt64_gte_mask(c, 0ULL) & ~FStar_UInt64_eq_mask(c, 0ULL);
    return m;
}

static inline void
fadd0(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t n[9U] = { 0U };
    p521_make_prime(n);
    bn_add_mod(a, n, b, c);
}

static inline void
fsub0(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t n[9U] = { 0U };
    p521_make_prime(n);
    bn_sub_mod(a, n, b, c);
}

static inline void
fmul0(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t tmp[18U] = { 0U };
    bn_mul(tmp, b, c);
    fmont_reduction(a, tmp);
}

static inline void
fsqr0(uint64_t *a, uint64_t *b)
{
    uint64_t tmp[18U] = { 0U };
    bn_sqr(tmp, b);
    fmont_reduction(a, tmp);
}

static inline void
from_mont(uint64_t *a, uint64_t *b)
{
    uint64_t tmp[18U] = { 0U };
    memcpy(tmp, b, 9U * sizeof(uint64_t));
    fmont_reduction(a, tmp);
}

static inline void
to_mont(uint64_t *a, uint64_t *b)
{
    uint64_t r2modn[9U] = { 0U };
    p521_make_fmont_R2(r2modn);
    uint64_t tmp[18U] = { 0U };
    bn_mul(tmp, b, r2modn);
    fmont_reduction(a, tmp);
}

static inline void
p521_finv(uint64_t *res, uint64_t *a)
{
    uint64_t b[9U] = { 0U };
    b[0U] = 0xfffffffffffffffdULL;
    b[1U] = 0xffffffffffffffffULL;
    b[2U] = 0xffffffffffffffffULL;
    b[3U] = 0xffffffffffffffffULL;
    b[4U] = 0xffffffffffffffffULL;
    b[5U] = 0xffffffffffffffffULL;
    b[6U] = 0xffffffffffffffffULL;
    b[7U] = 0xffffffffffffffffULL;
    b[8U] = 0x1ffULL;
    uint64_t tmp[9U] = { 0U };
    memcpy(tmp, a, 9U * sizeof(uint64_t));
    uint64_t table[288U] = { 0U };
    uint64_t tmp1[9U] = { 0U };
    uint64_t *t0 = table;
    uint64_t *t1 = table + 9U;
    p521_make_fone(t0);
    memcpy(t1, tmp, 9U * sizeof(uint64_t));
    KRML_MAYBE_FOR15(i,
                     0U,
                     15U,
                     1U,
                     uint64_t *t11 = table + (i + 1U) * 9U;
                     fsqr0(tmp1, t11);
                     memcpy(table + (2U * i + 2U) * 9U, tmp1, 9U * sizeof(uint64_t));
                     uint64_t *t2 = table + (2U * i + 2U) * 9U;
                     fmul0(tmp1, tmp, t2);
                     memcpy(table + (2U * i + 3U) * 9U, tmp1, 9U * sizeof(uint64_t)););
    uint32_t i0 = 520U;
    uint64_t bits_c = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, i0, 5U);
    memcpy(res, (uint64_t *)table, 9U * sizeof(uint64_t));
    for (uint32_t i1 = 0U; i1 < 31U; i1++) {
        uint64_t c = FStar_UInt64_eq_mask(bits_c, (uint64_t)(i1 + 1U));
        const uint64_t *res_j = table + (i1 + 1U) * 9U;
        KRML_MAYBE_FOR9(i,
                        0U,
                        9U,
                        1U,
                        uint64_t *os = res;
                        uint64_t x = (c & res_j[i]) | (~c & res[i]);
                        os[i] = x;);
    }
    uint64_t tmp10[9U] = { 0U };
    for (uint32_t i1 = 0U; i1 < 104U; i1++) {
        KRML_MAYBE_FOR5(i, 0U, 5U, 1U, fsqr0(res, res););
        uint32_t k = 520U - 5U * i1 - 5U;
        uint64_t bits_l = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, k, 5U);
        memcpy(tmp10, (uint64_t *)table, 9U * sizeof(uint64_t));
        for (uint32_t i2 = 0U; i2 < 31U; i2++) {
            uint64_t c = FStar_UInt64_eq_mask(bits_l, (uint64_t)(i2 + 1U));
            const uint64_t *res_j = table + (i2 + 1U) * 9U;
            KRML_MAYBE_FOR9(i,
                            0U,
                            9U,
                            1U,
                            uint64_t *os = tmp10;
                            uint64_t x = (c & res_j[i]) | (~c & tmp10[i]);
                            os[i] = x;);
        }
        fmul0(res, res, tmp10);
    }
}

static inline void
p521_fsqrt(uint64_t *res, uint64_t *a)
{
    uint64_t b[9U] = { 0U };
    b[0U] = 0x0ULL;
    b[1U] = 0x0ULL;
    b[2U] = 0x0ULL;
    b[3U] = 0x0ULL;
    b[4U] = 0x0ULL;
    b[5U] = 0x0ULL;
    b[6U] = 0x0ULL;
    b[7U] = 0x0ULL;
    b[8U] = 0x80ULL;
    uint64_t tmp[9U] = { 0U };
    memcpy(tmp, a, 9U * sizeof(uint64_t));
    uint64_t table[288U] = { 0U };
    uint64_t tmp1[9U] = { 0U };
    uint64_t *t0 = table;
    uint64_t *t1 = table + 9U;
    p521_make_fone(t0);
    memcpy(t1, tmp, 9U * sizeof(uint64_t));
    KRML_MAYBE_FOR15(i,
                     0U,
                     15U,
                     1U,
                     uint64_t *t11 = table + (i + 1U) * 9U;
                     fsqr0(tmp1, t11);
                     memcpy(table + (2U * i + 2U) * 9U, tmp1, 9U * sizeof(uint64_t));
                     uint64_t *t2 = table + (2U * i + 2U) * 9U;
                     fmul0(tmp1, tmp, t2);
                     memcpy(table + (2U * i + 3U) * 9U, tmp1, 9U * sizeof(uint64_t)););
    uint32_t i0 = 520U;
    uint64_t bits_c = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, i0, 5U);
    memcpy(res, (uint64_t *)table, 9U * sizeof(uint64_t));
    for (uint32_t i1 = 0U; i1 < 31U; i1++) {
        uint64_t c = FStar_UInt64_eq_mask(bits_c, (uint64_t)(i1 + 1U));
        const uint64_t *res_j = table + (i1 + 1U) * 9U;
        KRML_MAYBE_FOR9(i,
                        0U,
                        9U,
                        1U,
                        uint64_t *os = res;
                        uint64_t x = (c & res_j[i]) | (~c & res[i]);
                        os[i] = x;);
    }
    uint64_t tmp10[9U] = { 0U };
    for (uint32_t i1 = 0U; i1 < 104U; i1++) {
        KRML_MAYBE_FOR5(i, 0U, 5U, 1U, fsqr0(res, res););
        uint32_t k = 520U - 5U * i1 - 5U;
        uint64_t bits_l = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, k, 5U);
        memcpy(tmp10, (uint64_t *)table, 9U * sizeof(uint64_t));
        for (uint32_t i2 = 0U; i2 < 31U; i2++) {
            uint64_t c = FStar_UInt64_eq_mask(bits_l, (uint64_t)(i2 + 1U));
            const uint64_t *res_j = table + (i2 + 1U) * 9U;
            KRML_MAYBE_FOR9(i,
                            0U,
                            9U,
                            1U,
                            uint64_t *os = tmp10;
                            uint64_t x = (c & res_j[i]) | (~c & tmp10[i]);
                            os[i] = x;);
        }
        fmul0(res, res, tmp10);
    }
}

static inline uint64_t
load_qelem_conditional(uint64_t *a, uint8_t *b)
{
    bn_from_bytes_be(a, b);
    uint64_t tmp[9U] = { 0U };
    p521_make_order(tmp);
    uint64_t c = bn_sub(tmp, a, tmp);
    uint64_t is_lt_order = FStar_UInt64_gte_mask(c, 0ULL) & ~FStar_UInt64_eq_mask(c, 0ULL);
    uint64_t bn_zero[9U] = { 0U };
    uint64_t res = bn_is_eq_mask(a, bn_zero);
    uint64_t is_eq_zero = res;
    uint64_t is_b_valid = is_lt_order & ~is_eq_zero;
    uint64_t oneq[9U] = { 0U };
    memset(oneq, 0U, 9U * sizeof(uint64_t));
    oneq[0U] = 1ULL;
    KRML_MAYBE_FOR9(i,
                    0U,
                    9U,
                    1U,
                    uint64_t *os = a;
                    uint64_t uu____0 = oneq[i];
                    uint64_t x = uu____0 ^ (is_b_valid & (a[i] ^ uu____0));
                    os[i] = x;);
    return is_b_valid;
}

static inline void
qmod_short(uint64_t *a, uint64_t *b)
{
    uint64_t tmp[9U] = { 0U };
    p521_make_order(tmp);
    uint64_t c = bn_sub(tmp, b, tmp);
    bn_cmovznz(a, c, tmp, b);
}

static inline void
qadd(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t n[9U] = { 0U };
    p521_make_order(n);
    bn_add_mod(a, n, b, c);
}

static inline void
qmul(uint64_t *a, uint64_t *b, uint64_t *c)
{
    uint64_t tmp[18U] = { 0U };
    bn_mul(tmp, b, c);
    qmont_reduction(a, tmp);
}

static inline void
qsqr(uint64_t *a, uint64_t *b)
{
    uint64_t tmp[18U] = { 0U };
    bn_sqr(tmp, b);
    qmont_reduction(a, tmp);
}

static inline void
from_qmont(uint64_t *a, uint64_t *b)
{
    uint64_t tmp[18U] = { 0U };
    memcpy(tmp, b, 9U * sizeof(uint64_t));
    qmont_reduction(a, tmp);
}

static inline void
p521_qinv(uint64_t *res, uint64_t *a)
{
    uint64_t b[9U] = { 0U };
    b[0U] = 0xbb6fb71e91386407ULL;
    b[1U] = 0x3bb5c9b8899c47aeULL;
    b[2U] = 0x7fcc0148f709a5d0ULL;
    b[3U] = 0x51868783bf2f966bULL;
    b[4U] = 0xfffffffffffffffaULL;
    b[5U] = 0xffffffffffffffffULL;
    b[6U] = 0xffffffffffffffffULL;
    b[7U] = 0xffffffffffffffffULL;
    b[8U] = 0x1ffULL;
    uint64_t tmp[9U] = { 0U };
    memcpy(tmp, a, 9U * sizeof(uint64_t));
    uint64_t table[288U] = { 0U };
    uint64_t tmp1[9U] = { 0U };
    uint64_t *t0 = table;
    uint64_t *t1 = table + 9U;
    p521_make_qone(t0);
    memcpy(t1, tmp, 9U * sizeof(uint64_t));
    KRML_MAYBE_FOR15(i,
                     0U,
                     15U,
                     1U,
                     uint64_t *t11 = table + (i + 1U) * 9U;
                     qsqr(tmp1, t11);
                     memcpy(table + (2U * i + 2U) * 9U, tmp1, 9U * sizeof(uint64_t));
                     uint64_t *t2 = table + (2U * i + 2U) * 9U;
                     qmul(tmp1, tmp, t2);
                     memcpy(table + (2U * i + 3U) * 9U, tmp1, 9U * sizeof(uint64_t)););
    uint32_t i0 = 520U;
    uint64_t bits_c = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, i0, 5U);
    memcpy(res, (uint64_t *)table, 9U * sizeof(uint64_t));
    for (uint32_t i1 = 0U; i1 < 31U; i1++) {
        uint64_t c = FStar_UInt64_eq_mask(bits_c, (uint64_t)(i1 + 1U));
        const uint64_t *res_j = table + (i1 + 1U) * 9U;
        KRML_MAYBE_FOR9(i,
                        0U,
                        9U,
                        1U,
                        uint64_t *os = res;
                        uint64_t x = (c & res_j[i]) | (~c & res[i]);
                        os[i] = x;);
    }
    uint64_t tmp10[9U] = { 0U };
    for (uint32_t i1 = 0U; i1 < 104U; i1++) {
        KRML_MAYBE_FOR5(i, 0U, 5U, 1U, qsqr(res, res););
        uint32_t k = 520U - 5U * i1 - 5U;
        uint64_t bits_l = Hacl_Bignum_Lib_bn_get_bits_u64(9U, b, k, 5U);
        memcpy(tmp10, (uint64_t *)table, 9U * sizeof(uint64_t));
        for (uint32_t i2 = 0U; i2 < 31U; i2++) {
            uint64_t c = FStar_UInt64_eq_mask(bits_l, (uint64_t)(i2 + 1U));
            const uint64_t *res_j = table + (i2 + 1U) * 9U;
            KRML_MAYBE_FOR9(i,
                            0U,
                            9U,
                            1U,
                            uint64_t *os = tmp10;
                            uint64_t x = (c & res_j[i]) | (~c & tmp10[i]);
                            os[i] = x;);
        }
        qmul(res, res, tmp10);
    }
}

static inline void
point_add(uint64_t *x, uint64_t *y, uint64_t *xy)
{
    uint64_t tmp[81U] = { 0U };
    uint64_t *t0 = tmp;
    uint64_t *t1 = tmp + 54U;
    uint64_t *x3 = t1;
    uint64_t *y3 = t1 + 9U;
    uint64_t *z3 = t1 + 18U;
    uint64_t *t01 = t0;
    uint64_t *t11 = t0 + 9U;
    uint64_t *t2 = t0 + 18U;
    uint64_t *t3 = t0 + 27U;
    uint64_t *t4 = t0 + 36U;
    uint64_t *t5 = t0 + 45U;
    uint64_t *x1 = x;
    uint64_t *y1 = x + 9U;
    uint64_t *z10 = x + 18U;
    uint64_t *x20 = y;
    uint64_t *y20 = y + 9U;
    uint64_t *z20 = y + 18U;
    fmul0(t01, x1, x20);
    fmul0(t11, y1, y20);
    fmul0(t2, z10, z20);
    fadd0(t3, x1, y1);
    fadd0(t4, x20, y20);
    fmul0(t3, t3, t4);
    fadd0(t4, t01, t11);
    uint64_t *y10 = x + 9U;
    uint64_t *z11 = x + 18U;
    uint64_t *y2 = y + 9U;
    uint64_t *z21 = y + 18U;
    fsub0(t3, t3, t4);
    fadd0(t4, y10, z11);
    fadd0(t5, y2, z21);
    fmul0(t4, t4, t5);
    fadd0(t5, t11, t2);
    fsub0(t4, t4, t5);
    uint64_t *x10 = x;
    uint64_t *z1 = x + 18U;
    uint64_t *x2 = y;
    uint64_t *z2 = y + 18U;
    fadd0(x3, x10, z1);
    fadd0(y3, x2, z2);
    fmul0(x3, x3, y3);
    fadd0(y3, t01, t2);
    fsub0(y3, x3, y3);
    uint64_t b_coeff[9U] = { 0U };
    p521_make_b_coeff(b_coeff);
    fmul0(z3, b_coeff, t2);
    fsub0(x3, y3, z3);
    fadd0(z3, x3, x3);
    fadd0(x3, x3, z3);
    fsub0(z3, t11, x3);
    fadd0(x3, t11, x3);
    uint64_t b_coeff0[9U] = { 0U };
    p521_make_b_coeff(b_coeff0);
    fmul0(y3, b_coeff0, y3);
    fadd0(t11, t2, t2);
    fadd0(t2, t11, t2);
    fsub0(y3, y3, t2);
    fsub0(y3, y3, t01);
    fadd0(t11, y3, y3);
    fadd0(y3, t11, y3);
    fadd0(t11, t01, t01);
    fadd0(t01, t11, t01);
    fsub0(t01, t01, t2);
    fmul0(t11, t4, y3);
    fmul0(t2, t01, y3);
    fmul0(y3, x3, z3);
    fadd0(y3, y3, t2);
    fmul0(x3, t3, x3);
    fsub0(x3, x3, t11);
    fmul0(z3, t4, z3);
    fmul0(t11, t3, t01);
    fadd0(z3, z3, t11);
    memcpy(xy, t1, 27U * sizeof(uint64_t));
}

static inline void
point_double(uint64_t *x, uint64_t *xx)
{
    uint64_t tmp[45U] = { 0U };
    uint64_t *x1 = x;
    uint64_t *z = x + 18U;
    uint64_t *x3 = xx;
    uint64_t *y3 = xx + 9U;
    uint64_t *z3 = xx + 18U;
    uint64_t *t0 = tmp;
    uint64_t *t1 = tmp + 9U;
    uint64_t *t2 = tmp + 18U;
    uint64_t *t3 = tmp + 27U;
    uint64_t *t4 = tmp + 36U;
    uint64_t *x2 = x;
    uint64_t *y = x + 9U;
    uint64_t *z1 = x + 18U;
    fsqr0(t0, x2);
    fsqr0(t1, y);
    fsqr0(t2, z1);
    fmul0(t3, x2, y);
    fadd0(t3, t3, t3);
    fmul0(t4, y, z1);
    fmul0(z3, x1, z);
    fadd0(z3, z3, z3);
    uint64_t b_coeff[9U] = { 0U };
    p521_make_b_coeff(b_coeff);
    fmul0(y3, b_coeff, t2);
    fsub0(y3, y3, z3);
    fadd0(x3, y3, y3);
    fadd0(y3, x3, y3);
    fsub0(x3, t1, y3);
    fadd0(y3, t1, y3);
    fmul0(y3, x3, y3);
    fmul0(x3, x3, t3);
    fadd0(t3, t2, t2);
    fadd0(t2, t2, t3);
    uint64_t b_coeff0[9U] = { 0U };
    p521_make_b_coeff(b_coeff0);
    fmul0(z3, b_coeff0, z3);
    fsub0(z3, z3, t2);
    fsub0(z3, z3, t0);
    fadd0(t3, z3, z3);
    fadd0(z3, z3, t3);
    fadd0(t3, t0, t0);
    fadd0(t0, t3, t0);
    fsub0(t0, t0, t2);
    fmul0(t0, t0, z3);
    fadd0(y3, y3, t0);
    fadd0(t0, t4, t4);
    fmul0(z3, t0, z3);
    fsub0(x3, x3, z3);
    fmul0(z3, t0, t1);
    fadd0(z3, z3, z3);
    fadd0(z3, z3, z3);
}

static inline void
point_zero(uint64_t *one)
{
    uint64_t *x = one;
    uint64_t *y = one + 9U;
    uint64_t *z = one + 18U;
    p521_make_fzero(x);
    p521_make_fone(y);
    p521_make_fzero(z);
}

static inline void
point_mul(uint64_t *res, uint64_t *scalar, uint64_t *p)
{
    uint64_t table[432U] = { 0U };
    uint64_t tmp[27U] = { 0U };
    uint64_t *t0 = table;
    uint64_t *t1 = table + 27U;
    point_zero(t0);
    memcpy(t1, p, 27U * sizeof(uint64_t));
    KRML_MAYBE_FOR7(i,
                    0U,
                    7U,
                    1U,
                    uint64_t *t11 = table + (i + 1U) * 27U;
                    point_double(t11, tmp);
                    memcpy(table + (2U * i + 2U) * 27U, tmp, 27U * sizeof(uint64_t));
                    uint64_t *t2 = table + (2U * i + 2U) * 27U;
                    point_add(p, t2, tmp);
                    memcpy(table + (2U * i + 3U) * 27U, tmp, 27U * sizeof(uint64_t)););
    uint32_t i0 = 520U;
    uint64_t bits_c = Hacl_Bignum_Lib_bn_get_bits_u64(9U, scalar, i0, 4U);
    memcpy(res, (uint64_t *)table, 27U * sizeof(uint64_t));
    KRML_MAYBE_FOR15(
        i1,
        0U,
        15U,
        1U,
        uint64_t c = FStar_UInt64_eq_mask(bits_c, (uint64_t)(i1 + 1U));
        const uint64_t *res_j = table + (i1 + 1U) * 27U;
        for (uint32_t i = 0U; i < 27U; i++) {
            uint64_t *os = res;
            uint64_t x = (c & res_j[i]) | (~c & res[i]);
            os[i] = x;
        });
    uint64_t tmp0[27U] = { 0U };
    for (uint32_t i1 = 0U; i1 < 130U; i1++) {
        KRML_MAYBE_FOR4(i, 0U, 4U, 1U, point_double(res, res););
        uint32_t k = 520U - 4U * i1 - 4U;
        uint64_t bits_l = Hacl_Bignum_Lib_bn_get_bits_u64(9U, scalar, k, 4U);
        memcpy(tmp0, (uint64_t *)table, 27U * sizeof(uint64_t));
        KRML_MAYBE_FOR15(
            i2,
            0U,
            15U,
            1U,
            uint64_t c = FStar_UInt64_eq_mask(bits_l, (uint64_t)(i2 + 1U));
            const uint64_t *res_j = table + (i2 + 1U) * 27U;
            for (uint32_t i = 0U; i < 27U; i++) {
                uint64_t *os = tmp0;
                uint64_t x = (c & res_j[i]) | (~c & tmp0[i]);
                os[i] = x;
            });
        point_add(res, tmp0, res);
    }
}

static inline void
point_mul_g(uint64_t *res, uint64_t *scalar)
{
    uint64_t g[27U] = { 0U };
    uint64_t *x = g;
    uint64_t *y = g + 9U;
    uint64_t *z = g + 18U;
    p521_make_g_x(x);
    p521_make_g_y(y);
    p521_make_fone(z);
    point_mul(res, scalar, g);
}

static inline void
point_mul_double_g(uint64_t *res, uint64_t *scalar1, uint64_t *scalar2, uint64_t *p)
{
    uint64_t tmp[27U] = { 0U };
    point_mul_g(tmp, scalar1);
    point_mul(res, scalar2, p);
    point_add(res, tmp, res);
}

static inline bool
ecdsa_sign_msg_as_qelem(
    uint8_t *signature,
    uint64_t *m_q,
    uint8_t *private_key,
    uint8_t *nonce)
{
    uint64_t rsdk_q[36U] = { 0U };
    uint64_t *r_q = rsdk_q;
    uint64_t *s_q = rsdk_q + 9U;
    uint64_t *d_a = rsdk_q + 18U;
    uint64_t *k_q = rsdk_q + 27U;
    uint64_t is_sk_valid = load_qelem_conditional(d_a, private_key);
    uint64_t is_nonce_valid = load_qelem_conditional(k_q, nonce);
    uint64_t are_sk_nonce_valid = is_sk_valid & is_nonce_valid;
    uint64_t p[27U] = { 0U };
    point_mul_g(p, k_q);
    uint64_t zinv[9U] = { 0U };
    uint64_t *px = p;
    uint64_t *pz = p + 18U;
    p521_finv(zinv, pz);
    fmul0(r_q, px, zinv);
    from_mont(r_q, r_q);
    qmod_short(r_q, r_q);
    uint64_t kinv[9U] = { 0U };
    p521_qinv(kinv, k_q);
    qmul(s_q, r_q, d_a);
    from_qmont(m_q, m_q);
    qadd(s_q, m_q, s_q);
    qmul(s_q, kinv, s_q);
    bn_to_bytes_be(signature, r_q);
    bn_to_bytes_be(signature + 66U, s_q);
    uint64_t bn_zero0[9U] = { 0U };
    uint64_t res = bn_is_eq_mask(r_q, bn_zero0);
    uint64_t is_r_zero = res;
    uint64_t bn_zero[9U] = { 0U };
    uint64_t res0 = bn_is_eq_mask(s_q, bn_zero);
    uint64_t is_s_zero = res0;
    uint64_t m = are_sk_nonce_valid & (~is_r_zero & ~is_s_zero);
    bool res1 = m == 0xFFFFFFFFFFFFFFFFULL;
    return res1;
}

static inline bool
ecdsa_verify_msg_as_qelem(
    uint64_t *m_q,
    uint8_t *public_key,
    uint8_t *signature_r,
    uint8_t *signature_s)
{
    uint64_t tmp[63U] = { 0U };
    uint64_t *pk = tmp;
    uint64_t *r_q = tmp + 27U;
    uint64_t *s_q = tmp + 36U;
    uint64_t *u1 = tmp + 45U;
    uint64_t *u2 = tmp + 54U;
    uint64_t p_aff[18U] = { 0U };
    uint8_t *p_x = public_key;
    uint8_t *p_y = public_key + 66U;
    uint64_t *bn_p_x = p_aff;
    uint64_t *bn_p_y = p_aff + 9U;
    bn_from_bytes_be(bn_p_x, p_x);
    bn_from_bytes_be(bn_p_y, p_y);
    uint64_t *px0 = p_aff;
    uint64_t *py0 = p_aff + 9U;
    uint64_t lessX = bn_is_lt_prime_mask(px0);
    uint64_t lessY = bn_is_lt_prime_mask(py0);
    uint64_t res0 = lessX & lessY;
    bool is_xy_valid = res0 == 0xFFFFFFFFFFFFFFFFULL;
    bool res;
    if (!is_xy_valid) {
        res = false;
    } else {
        uint64_t rp[9U] = { 0U };
        uint64_t tx[9U] = { 0U };
        uint64_t ty[9U] = { 0U };
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        to_mont(tx, px);
        to_mont(ty, py);
        uint64_t tmp1[9U] = { 0U };
        fsqr0(rp, tx);
        fmul0(rp, rp, tx);
        p521_make_a_coeff(tmp1);
        fmul0(tmp1, tmp1, tx);
        fadd0(rp, tmp1, rp);
        p521_make_b_coeff(tmp1);
        fadd0(rp, tmp1, rp);
        fsqr0(ty, ty);
        uint64_t r = bn_is_eq_mask(ty, rp);
        uint64_t r0 = r;
        bool r1 = r0 == 0xFFFFFFFFFFFFFFFFULL;
        res = r1;
    }
    if (res) {
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        uint64_t *rx = pk;
        uint64_t *ry = pk + 9U;
        uint64_t *rz = pk + 18U;
        to_mont(rx, px);
        to_mont(ry, py);
        p521_make_fone(rz);
    }
    bool is_pk_valid = res;
    bn_from_bytes_be(r_q, signature_r);
    bn_from_bytes_be(s_q, signature_s);
    uint64_t tmp10[9U] = { 0U };
    p521_make_order(tmp10);
    uint64_t c = bn_sub(tmp10, r_q, tmp10);
    uint64_t is_lt_order = FStar_UInt64_gte_mask(c, 0ULL) & ~FStar_UInt64_eq_mask(c, 0ULL);
    uint64_t bn_zero0[9U] = { 0U };
    uint64_t res1 = bn_is_eq_mask(r_q, bn_zero0);
    uint64_t is_eq_zero = res1;
    uint64_t is_r_valid = is_lt_order & ~is_eq_zero;
    uint64_t tmp11[9U] = { 0U };
    p521_make_order(tmp11);
    uint64_t c0 = bn_sub(tmp11, s_q, tmp11);
    uint64_t is_lt_order0 = FStar_UInt64_gte_mask(c0, 0ULL) & ~FStar_UInt64_eq_mask(c0, 0ULL);
    uint64_t bn_zero1[9U] = { 0U };
    uint64_t res2 = bn_is_eq_mask(s_q, bn_zero1);
    uint64_t is_eq_zero0 = res2;
    uint64_t is_s_valid = is_lt_order0 & ~is_eq_zero0;
    bool is_rs_valid = is_r_valid == 0xFFFFFFFFFFFFFFFFULL && is_s_valid == 0xFFFFFFFFFFFFFFFFULL;
    if (!(is_pk_valid && is_rs_valid)) {
        return false;
    }
    uint64_t sinv[9U] = { 0U };
    p521_qinv(sinv, s_q);
    uint64_t tmp1[9U] = { 0U };
    from_qmont(tmp1, m_q);
    qmul(u1, sinv, tmp1);
    uint64_t tmp12[9U] = { 0U };
    from_qmont(tmp12, r_q);
    qmul(u2, sinv, tmp12);
    uint64_t res3[27U] = { 0U };
    point_mul_double_g(res3, u1, u2, pk);
    uint64_t *pz0 = res3 + 18U;
    uint64_t bn_zero[9U] = { 0U };
    uint64_t res10 = bn_is_eq_mask(pz0, bn_zero);
    uint64_t m = res10;
    if (m == 0xFFFFFFFFFFFFFFFFULL) {
        return false;
    }
    uint64_t x[9U] = { 0U };
    uint64_t zinv[9U] = { 0U };
    uint64_t *px = res3;
    uint64_t *pz = res3 + 18U;
    p521_finv(zinv, pz);
    fmul0(x, px, zinv);
    from_mont(x, x);
    qmod_short(x, x);
    uint64_t m0 = bn_is_eq_mask(x, r_q);
    bool res11 = m0 == 0xFFFFFFFFFFFFFFFFULL;
    return res11;
}

/*******************************************************************************

 Verified C library for ECDSA and ECDH functions over the P-521 NIST curve.

 This module implements signing and verification, key validation, conversions
 between various point representations, and ECDH key agreement.

*******************************************************************************/

/*****************/
/* ECDSA signing */
/*****************/

/**
Create an ECDSA signature WITHOUT hashing first.

  This function is intended to receive a hash of the input.
  For convenience, we recommend using one of the hash-and-sign combined functions above.

  The argument `msg` MUST be at least 66 bytes (i.e. `msg_len >= 66`).

  NOTE: The equivalent functions in OpenSSL and Fiat-Crypto both accept inputs
  smaller than 66 bytes. These libraries left-pad the input with enough zeroes to
  reach the minimum 66 byte size. Clients who need behavior identical to OpenSSL
  need to perform the left-padding themselves.

  The function returns `true` for successful creation of an ECDSA signature and `false` otherwise.

  The outparam `signature` (R || S) points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `msg` points to `msg_len` bytes of valid memory, i.e., uint8_t[msg_len].
  The arguments `private_key` and `nonce` point to 66 bytes of valid memory, i.e., uint8_t[66].

  The function also checks whether `private_key` and `nonce` are valid values:
    • 0 < `private_key` < the order of the curve
    • 0 < `nonce` < the order of the curve
*/
bool
Hacl_P521_ecdsa_sign_p521_without_hash(
    uint8_t *signature,
    uint32_t msg_len,
    uint8_t *msg,
    uint8_t *private_key,
    uint8_t *nonce)
{
    uint64_t m_q[9U] = { 0U };
    uint8_t mHash[66U] = { 0U };
    memcpy(mHash, msg, 66U * sizeof(uint8_t));
    KRML_MAYBE_UNUSED_VAR(msg_len);
    bn_from_bytes_be(m_q, mHash);
    qmod_short(m_q, m_q);
    bool res = ecdsa_sign_msg_as_qelem(signature, m_q, private_key, nonce);
    return res;
}

/**********************/
/* ECDSA verification */
/**********************/

/**
Verify an ECDSA signature WITHOUT hashing first.

  This function is intended to receive a hash of the input.
  For convenience, we recommend using one of the hash-and-verify combined functions above.

  The argument `msg` MUST be at least 66 bytes (i.e. `msg_len >= 66`).

  The function returns `true` if the signature is valid and `false` otherwise.

  The argument `msg` points to `msg_len` bytes of valid memory, i.e., uint8_t[msg_len].
  The argument `public_key` (x || y) points to 132 bytes of valid memory, i.e., uint8_t[132].
  The arguments `signature_r` and `signature_s` point to 66 bytes of valid memory, i.e., uint8_t[66].

  The function also checks whether `public_key` is valid
*/
bool
Hacl_P521_ecdsa_verif_without_hash(
    uint32_t msg_len,
    uint8_t *msg,
    uint8_t *public_key,
    uint8_t *signature_r,
    uint8_t *signature_s)
{
    uint64_t m_q[9U] = { 0U };
    uint8_t mHash[66U] = { 0U };
    memcpy(mHash, msg, 66U * sizeof(uint8_t));
    KRML_MAYBE_UNUSED_VAR(msg_len);
    bn_from_bytes_be(m_q, mHash);
    qmod_short(m_q, m_q);
    bool res = ecdsa_verify_msg_as_qelem(m_q, public_key, signature_r, signature_s);
    return res;
}

/******************/
/* Key validation */
/******************/

/**
Public key validation.

  The function returns `true` if a public key is valid and `false` otherwise.

  The argument `public_key` points to 132 bytes of valid memory, i.e., uint8_t[132].

  The public key (x || y) is valid (with respect to SP 800-56A):
    • the public key is not the “point at infinity”, represented as O.
    • the affine x and y coordinates of the point represented by the public key are
      in the range [0, p – 1] where p is the prime defining the finite field.
    • y^2 = x^3 + ax + b where a and b are the coefficients of the curve equation.
  The last extract is taken from: https://neilmadden.blog/2017/05/17/so-how-do-you-validate-nist-ecdh-public-keys/
*/
bool
Hacl_P521_validate_public_key(uint8_t *public_key)
{
    uint64_t point_jac[27U] = { 0U };
    uint64_t p_aff[18U] = { 0U };
    uint8_t *p_x = public_key;
    uint8_t *p_y = public_key + 66U;
    uint64_t *bn_p_x = p_aff;
    uint64_t *bn_p_y = p_aff + 9U;
    bn_from_bytes_be(bn_p_x, p_x);
    bn_from_bytes_be(bn_p_y, p_y);
    uint64_t *px0 = p_aff;
    uint64_t *py0 = p_aff + 9U;
    uint64_t lessX = bn_is_lt_prime_mask(px0);
    uint64_t lessY = bn_is_lt_prime_mask(py0);
    uint64_t res0 = lessX & lessY;
    bool is_xy_valid = res0 == 0xFFFFFFFFFFFFFFFFULL;
    bool res;
    if (!is_xy_valid) {
        res = false;
    } else {
        uint64_t rp[9U] = { 0U };
        uint64_t tx[9U] = { 0U };
        uint64_t ty[9U] = { 0U };
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        to_mont(tx, px);
        to_mont(ty, py);
        uint64_t tmp[9U] = { 0U };
        fsqr0(rp, tx);
        fmul0(rp, rp, tx);
        p521_make_a_coeff(tmp);
        fmul0(tmp, tmp, tx);
        fadd0(rp, tmp, rp);
        p521_make_b_coeff(tmp);
        fadd0(rp, tmp, rp);
        fsqr0(ty, ty);
        uint64_t r = bn_is_eq_mask(ty, rp);
        uint64_t r0 = r;
        bool r1 = r0 == 0xFFFFFFFFFFFFFFFFULL;
        res = r1;
    }
    if (res) {
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        uint64_t *rx = point_jac;
        uint64_t *ry = point_jac + 9U;
        uint64_t *rz = point_jac + 18U;
        to_mont(rx, px);
        to_mont(ry, py);
        p521_make_fone(rz);
    }
    bool res1 = res;
    return res1;
}

/**
Private key validation.

  The function returns `true` if a private key is valid and `false` otherwise.

  The argument `private_key` points to 66 bytes of valid memory, i.e., uint8_t[66].

  The private key is valid:
    • 0 < `private_key` < the order of the curve
*/
bool
Hacl_P521_validate_private_key(uint8_t *private_key)
{
    uint64_t bn_sk[9U] = { 0U };
    bn_from_bytes_be(bn_sk, private_key);
    uint64_t tmp[9U] = { 0U };
    p521_make_order(tmp);
    uint64_t c = bn_sub(tmp, bn_sk, tmp);
    uint64_t is_lt_order = FStar_UInt64_gte_mask(c, 0ULL) & ~FStar_UInt64_eq_mask(c, 0ULL);
    uint64_t bn_zero[9U] = { 0U };
    uint64_t res = bn_is_eq_mask(bn_sk, bn_zero);
    uint64_t is_eq_zero = res;
    uint64_t res0 = is_lt_order & ~is_eq_zero;
    return res0 == 0xFFFFFFFFFFFFFFFFULL;
}

/*******************************************************************************
  Parsing and Serializing public keys.

  A public key is a point (x, y) on the P-521 NIST curve.

  The point can be represented in the following three ways.
    • raw          = [ x || y ], 132 bytes
    • uncompressed = [ 0x04 || x || y ], 133 bytes
    • compressed   = [ (0x02 for even `y` and 0x03 for odd `y`) || x ], 33 bytes

*******************************************************************************/

/**
Convert a public key from uncompressed to its raw form.

  The function returns `true` for successful conversion of a public key and `false` otherwise.

  The outparam `pk_raw` points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `pk` points to 133 bytes of valid memory, i.e., uint8_t[133].

  The function DOESN'T check whether (x, y) is a valid point.
*/
bool
Hacl_P521_uncompressed_to_raw(uint8_t *pk, uint8_t *pk_raw)
{
    uint8_t pk0 = pk[0U];
    if (pk0 != 0x04U) {
        return false;
    }
    memcpy(pk_raw, pk + 1U, 132U * sizeof(uint8_t));
    return true;
}

/**
Convert a public key from compressed to its raw form.

  The function returns `true` for successful conversion of a public key and `false` otherwise.

  The outparam `pk_raw` points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `pk` points to 33 bytes of valid memory, i.e., uint8_t[33].

  The function also checks whether (x, y) is a valid point.
*/
bool
Hacl_P521_compressed_to_raw(uint8_t *pk, uint8_t *pk_raw)
{
    uint64_t xa[9U] = { 0U };
    uint64_t ya[9U] = { 0U };
    uint8_t *pk_xb = pk + 1U;
    uint8_t s0 = pk[0U];
    uint8_t s01 = s0;
    bool b;
    if (!(s01 == 0x02U || s01 == 0x03U)) {
        b = false;
    } else {
        uint8_t *xb = pk + 1U;
        bn_from_bytes_be(xa, xb);
        uint64_t is_x_valid = bn_is_lt_prime_mask(xa);
        bool is_x_valid1 = is_x_valid == 0xFFFFFFFFFFFFFFFFULL;
        bool is_y_odd = s01 == 0x03U;
        if (!is_x_valid1) {
            b = false;
        } else {
            uint64_t y2M[9U] = { 0U };
            uint64_t xM[9U] = { 0U };
            uint64_t yM[9U] = { 0U };
            to_mont(xM, xa);
            uint64_t tmp[9U] = { 0U };
            fsqr0(y2M, xM);
            fmul0(y2M, y2M, xM);
            p521_make_a_coeff(tmp);
            fmul0(tmp, tmp, xM);
            fadd0(y2M, tmp, y2M);
            p521_make_b_coeff(tmp);
            fadd0(y2M, tmp, y2M);
            p521_fsqrt(yM, y2M);
            from_mont(ya, yM);
            fsqr0(yM, yM);
            uint64_t r = bn_is_eq_mask(yM, y2M);
            uint64_t r0 = r;
            bool is_y_valid = r0 == 0xFFFFFFFFFFFFFFFFULL;
            bool is_y_valid0 = is_y_valid;
            if (!is_y_valid0) {
                b = false;
            } else {
                uint64_t is_y_odd1 = ya[0U] & 1ULL;
                bool is_y_odd2 = is_y_odd1 == 1ULL;
                uint64_t zero[9U] = { 0U };
                if (is_y_odd2 != is_y_odd) {
                    fsub0(ya, zero, ya);
                }
                b = true;
            }
        }
    }
    if (b) {
        memcpy(pk_raw, pk_xb, 66U * sizeof(uint8_t));
        bn_to_bytes_be(pk_raw + 66U, ya);
    }
    return b;
}

/**
Convert a public key from raw to its uncompressed form.

  The outparam `pk` points to 133 bytes of valid memory, i.e., uint8_t[133].
  The argument `pk_raw` points to 132 bytes of valid memory, i.e., uint8_t[132].

  The function DOESN'T check whether (x, y) is a valid point.
*/
void
Hacl_P521_raw_to_uncompressed(uint8_t *pk_raw, uint8_t *pk)
{
    pk[0U] = 0x04U;
    memcpy(pk + 1U, pk_raw, 132U * sizeof(uint8_t));
}

/**
Convert a public key from raw to its compressed form.

  The outparam `pk` points to 33 bytes of valid memory, i.e., uint8_t[33].
  The argument `pk_raw` points to 132 bytes of valid memory, i.e., uint8_t[132].

  The function DOESN'T check whether (x, y) is a valid point.
*/
void
Hacl_P521_raw_to_compressed(uint8_t *pk_raw, uint8_t *pk)
{
    uint8_t *pk_x = pk_raw;
    uint8_t *pk_y = pk_raw + 66U;
    uint64_t bn_f[9U] = { 0U };
    bn_from_bytes_be(bn_f, pk_y);
    uint64_t is_odd_f = bn_f[0U] & 1ULL;
    pk[0U] = (uint32_t)(uint8_t)is_odd_f + 0x02U;
    memcpy(pk + 1U, pk_x, 66U * sizeof(uint8_t));
}

/******************/
/* ECDH agreement */
/******************/

/**
Compute the public key from the private key.

  The function returns `true` if a private key is valid and `false` otherwise.

  The outparam `public_key`  points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `private_key` points to 66 bytes of valid memory, i.e., uint8_t[66].

  The private key is valid:
    • 0 < `private_key` < the order of the curve.
*/
bool
Hacl_P521_dh_initiator(uint8_t *public_key, uint8_t *private_key)
{
    uint64_t tmp[36U] = { 0U };
    uint64_t *sk = tmp;
    uint64_t *pk = tmp + 9U;
    uint64_t is_sk_valid = load_qelem_conditional(sk, private_key);
    point_mul_g(pk, sk);
    uint64_t aff_p[18U] = { 0U };
    uint64_t zinv[9U] = { 0U };
    uint64_t *px = pk;
    uint64_t *py0 = pk + 9U;
    uint64_t *pz = pk + 18U;
    uint64_t *x = aff_p;
    uint64_t *y = aff_p + 9U;
    p521_finv(zinv, pz);
    fmul0(x, px, zinv);
    fmul0(y, py0, zinv);
    from_mont(x, x);
    from_mont(y, y);
    uint64_t *px0 = aff_p;
    uint64_t *py = aff_p + 9U;
    bn_to_bytes_be(public_key, px0);
    bn_to_bytes_be(public_key + 66U, py);
    return is_sk_valid == 0xFFFFFFFFFFFFFFFFULL;
}

/**
Execute the diffie-hellmann key exchange.

  The function returns `true` for successful creation of an ECDH shared secret and
  `false` otherwise.

  The outparam `shared_secret` points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `their_pubkey` points to 132 bytes of valid memory, i.e., uint8_t[132].
  The argument `private_key` points to 66 bytes of valid memory, i.e., uint8_t[66].

  The function also checks whether `private_key` and `their_pubkey` are valid.
*/
bool
Hacl_P521_dh_responder(uint8_t *shared_secret, uint8_t *their_pubkey, uint8_t *private_key)
{
    uint64_t tmp[264U] = { 0U };
    uint64_t *sk = tmp;
    uint64_t *pk = tmp + 9U;
    uint64_t p_aff[18U] = { 0U };
    uint8_t *p_x = their_pubkey;
    uint8_t *p_y = their_pubkey + 66U;
    uint64_t *bn_p_x = p_aff;
    uint64_t *bn_p_y = p_aff + 9U;
    bn_from_bytes_be(bn_p_x, p_x);
    bn_from_bytes_be(bn_p_y, p_y);
    uint64_t *px0 = p_aff;
    uint64_t *py0 = p_aff + 9U;
    uint64_t lessX = bn_is_lt_prime_mask(px0);
    uint64_t lessY = bn_is_lt_prime_mask(py0);
    uint64_t res0 = lessX & lessY;
    bool is_xy_valid = res0 == 0xFFFFFFFFFFFFFFFFULL;
    bool res;
    if (!is_xy_valid) {
        res = false;
    } else {
        uint64_t rp[9U] = { 0U };
        uint64_t tx[9U] = { 0U };
        uint64_t ty[9U] = { 0U };
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        to_mont(tx, px);
        to_mont(ty, py);
        uint64_t tmp1[9U] = { 0U };
        fsqr0(rp, tx);
        fmul0(rp, rp, tx);
        p521_make_a_coeff(tmp1);
        fmul0(tmp1, tmp1, tx);
        fadd0(rp, tmp1, rp);
        p521_make_b_coeff(tmp1);
        fadd0(rp, tmp1, rp);
        fsqr0(ty, ty);
        uint64_t r = bn_is_eq_mask(ty, rp);
        uint64_t r0 = r;
        bool r1 = r0 == 0xFFFFFFFFFFFFFFFFULL;
        res = r1;
    }
    if (res) {
        uint64_t *px = p_aff;
        uint64_t *py = p_aff + 9U;
        uint64_t *rx = pk;
        uint64_t *ry = pk + 9U;
        uint64_t *rz = pk + 18U;
        to_mont(rx, px);
        to_mont(ry, py);
        p521_make_fone(rz);
    }
    bool is_pk_valid = res;
    uint64_t is_sk_valid = load_qelem_conditional(sk, private_key);
    uint64_t ss_proj[27U] = { 0U };
    if (is_pk_valid) {
        point_mul(ss_proj, sk, pk);
        uint64_t aff_p[18U] = { 0U };
        uint64_t zinv[9U] = { 0U };
        uint64_t *px = ss_proj;
        uint64_t *py1 = ss_proj + 9U;
        uint64_t *pz = ss_proj + 18U;
        uint64_t *x = aff_p;
        uint64_t *y = aff_p + 9U;
        p521_finv(zinv, pz);
        fmul0(x, px, zinv);
        fmul0(y, py1, zinv);
        from_mont(x, x);
        from_mont(y, y);
        uint64_t *px1 = aff_p;
        uint64_t *py = aff_p + 9U;
        bn_to_bytes_be(shared_secret, px1);
        bn_to_bytes_be(shared_secret + 66U, py);
    }
    return is_sk_valid == 0xFFFFFFFFFFFFFFFFULL && is_pk_valid;
}
