/*! \file */
/* ************************************************************************
 * Copyright (c) 2018-2021 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ************************************************************************ */

#pragma once
#ifndef COMMON_H
#define COMMON_H

#include "rocsparse.h"

#include <hip/hip_runtime.h>

// clang-format off

// BSR indexing macros
#define BSR_IND(j, bi, bj, dir) ((dir == rocsparse_direction_row) ? BSR_IND_R(j, bi, bj) : BSR_IND_C(j, bi, bj))
#define BSR_IND_R(j, bi, bj) (bsr_dim * bsr_dim * (j) + (bi) * bsr_dim + (bj))
#define BSR_IND_C(j, bi, bj) (bsr_dim * bsr_dim * (j) + (bi) + (bj) * bsr_dim)

#define GEBSR_IND(j, bi, bj, dir) ((dir == rocsparse_direction_row) ? GEBSR_IND_R(j, bi, bj) : GEBSR_IND_C(j, bi, bj))
#define GEBSR_IND_R(j, bi, bj) (row_bsr_dim * col_bsr_dim * (j) + (bi) * col_bsr_dim + (bj))
#define GEBSR_IND_C(j, bi, bj) (row_bsr_dim * col_bsr_dim * (j) + (bi) + (bj) * row_bsr_dim)

// find next power of 2
__attribute__((unused)) static unsigned int fnp2(unsigned int x)
{
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x++;

    return x;
}

__device__ __forceinline__ float rocsparse_ldg(const float* ptr) { return __ldg(ptr); }
__device__ __forceinline__ double rocsparse_ldg(const double* ptr) { return __ldg(ptr); }
__device__ __forceinline__ rocsparse_float_complex rocsparse_ldg(const rocsparse_float_complex* ptr) { return rocsparse_float_complex(__ldg((const float*)ptr), __ldg((const float*)ptr + 1)); }
__device__ __forceinline__ rocsparse_double_complex rocsparse_ldg(const rocsparse_double_complex* ptr) { return rocsparse_double_complex(__ldg((const double*)ptr), __ldg((const double*)ptr + 1)); }
__device__ __forceinline__ int32_t rocsparse_ldg(const int32_t* ptr) { return __ldg(ptr); }
__device__ __forceinline__ int64_t rocsparse_ldg(const int64_t* ptr) { return __ldg(ptr); }

__device__ __forceinline__ float rocsparse_fma(float p, float q, float r) { return fma(p, q, r); }
__device__ __forceinline__ double rocsparse_fma(double p, double q, double r) { return fma(p, q, r); }
__device__ __forceinline__ rocsparse_float_complex rocsparse_fma(rocsparse_float_complex p, rocsparse_float_complex q, rocsparse_float_complex r) { return std::fma(p, q, r); }
__device__ __forceinline__ rocsparse_double_complex rocsparse_fma(rocsparse_double_complex p, rocsparse_double_complex q, rocsparse_double_complex r) { return std::fma(p, q, r); }

__device__ __forceinline__ float rocsparse_abs(float x) { return x < 0.0f ? -x : x; }
__device__ __forceinline__ double rocsparse_abs(double x) { return x < 0.0 ? -x : x; }
__device__ __forceinline__ float rocsparse_abs(rocsparse_float_complex x) { return std::abs(x); }
__device__ __forceinline__ double rocsparse_abs(rocsparse_double_complex x) { return std::abs(x); }

__device__ __forceinline__ float rocsparse_conj(const float& x) { return x; }
__device__ __forceinline__ double rocsparse_conj(const double& x) { return x; }
__device__ __forceinline__ rocsparse_float_complex rocsparse_conj(const rocsparse_float_complex& x) { return std::conj(x); }
__device__ __forceinline__ rocsparse_double_complex rocsparse_conj(const rocsparse_double_complex& x) { return std::conj(x); }

__device__ __forceinline__ float rocsparse_real(const float& x) { return x; }
__device__ __forceinline__ double rocsparse_real(const double& x) { return x; }
__device__ __forceinline__ float rocsparse_real(const rocsparse_float_complex& x) { return std::real(x); }
__device__ __forceinline__ double rocsparse_real(const rocsparse_double_complex& x) { return std::real(x); }

__device__ __forceinline__ float rocsparse_nontemporal_load(const float* ptr) { return __builtin_nontemporal_load(ptr); }
__device__ __forceinline__ double rocsparse_nontemporal_load(const double* ptr) { return __builtin_nontemporal_load(ptr); }
__device__ __forceinline__ rocsparse_float_complex rocsparse_nontemporal_load(const rocsparse_float_complex* ptr) { return rocsparse_float_complex(__builtin_nontemporal_load((const float*)ptr), __builtin_nontemporal_load((const float*)ptr + 1)); }
__device__ __forceinline__ rocsparse_double_complex rocsparse_nontemporal_load(const rocsparse_double_complex* ptr) { return rocsparse_double_complex(__builtin_nontemporal_load((const double*)ptr), __builtin_nontemporal_load((const double*)ptr + 1)); }
__device__ __forceinline__ int32_t rocsparse_nontemporal_load(const int32_t* ptr) { return __builtin_nontemporal_load(ptr); }
__device__ __forceinline__ int64_t rocsparse_nontemporal_load(const int64_t* ptr) { return __builtin_nontemporal_load(ptr); }

__device__ __forceinline__ void rocsparse_nontemporal_store(float val, float* ptr) { __builtin_nontemporal_store(val, ptr); }
__device__ __forceinline__ void rocsparse_nontemporal_store(double val, double* ptr) { __builtin_nontemporal_store(val, ptr); }
__device__ __forceinline__ void rocsparse_nontemporal_store(rocsparse_float_complex val, rocsparse_float_complex* ptr) { __builtin_nontemporal_store(std::real(val), (float*)ptr); __builtin_nontemporal_store(std::imag(val), (float*)ptr + 1); }
__device__ __forceinline__ void rocsparse_nontemporal_store(rocsparse_double_complex val, rocsparse_double_complex* ptr) { __builtin_nontemporal_store(std::real(val), (double*)ptr); __builtin_nontemporal_store(std::imag(val), (double*)ptr + 1); }
__device__ __forceinline__ void rocsparse_nontemporal_store(int32_t val, int32_t* ptr) { __builtin_nontemporal_store(val, ptr); }
__device__ __forceinline__ void rocsparse_nontemporal_store(int64_t val, int64_t* ptr) { __builtin_nontemporal_store(val, ptr); }

__device__ __forceinline__ float rocsparse_shfl(float var, int src_lane, int width = warpSize) { return __shfl(var, src_lane, width); }
__device__ __forceinline__ double rocsparse_shfl(double var, int src_lane, int width = warpSize) { return __shfl(var, src_lane, width); }
__device__ __forceinline__ rocsparse_float_complex rocsparse_shfl(rocsparse_float_complex var, int src_lane, int width = warpSize) { return rocsparse_float_complex(__shfl(std::real(var), src_lane, width), __shfl(std::imag(var), src_lane, width)); }
__device__ __forceinline__ rocsparse_double_complex rocsparse_shfl(rocsparse_double_complex var, int src_lane, int width = warpSize) { return rocsparse_double_complex(__shfl(std::real(var), src_lane, width), __shfl(std::imag(var), src_lane, width)); }

__device__ __forceinline__ int32_t rocsparse_mul24(int32_t x, int32_t y) { return ((x << 8) >> 8) * ((y << 8) >> 8); }
__device__ __forceinline__ int64_t rocsparse_mul24(int64_t x, int64_t y) { return ((x << 40) >> 40) * ((y << 40) >> 40); }

__device__ __forceinline__ int32_t rocsparse_mad24(int32_t x, int32_t y, int32_t z) { return rocsparse_mul24(x, y) + z; }
__device__ __forceinline__ int64_t rocsparse_mad24(int64_t x, int64_t y, int64_t z) { return rocsparse_mul24(x, y) + z; }

__device__ __forceinline__ int64_t atomicMin(int64_t* ptr, int64_t val) { return atomicMin((unsigned long long*)ptr, val); }
__device__ __forceinline__ int64_t atomicMax(int64_t* ptr, int64_t val) { return atomicMax((unsigned long long*)ptr, val); }
__device__ __forceinline__ int64_t atomicAdd(int64_t* ptr, int64_t val) { return atomicAdd((unsigned long long*)ptr, val); }
__device__ __forceinline__ int64_t atomicCAS(int64_t* ptr, int64_t cmp, int64_t val) { return atomicCAS((unsigned long long*)ptr, cmp, val); }

__device__ __forceinline__ rocsparse_float_complex atomicAdd(rocsparse_float_complex* ptr, rocsparse_float_complex val)
{
    return rocsparse_float_complex(atomicAdd((float*)ptr, std::real(val)),
                                   atomicAdd((float*)ptr + 1, std::imag(val)));
}
__device__ __forceinline__ rocsparse_double_complex atomicAdd(rocsparse_double_complex* ptr, rocsparse_double_complex val)
{
    return rocsparse_double_complex(atomicAdd((double*)ptr, std::real(val)),
                                    atomicAdd((double*)ptr + 1, std::imag(val)));
}

// Block reduce kernel computing block sum
template <unsigned int BLOCKSIZE, typename T>
__device__ __forceinline__ void rocsparse_blockreduce_sum(int i, T* data)
{
    if(BLOCKSIZE > 512) { if(i < 512 && i + 512 < BLOCKSIZE) { data[i] = data[i] + data[i + 512]; } __syncthreads(); }
    if(BLOCKSIZE > 256) { if(i < 256 && i + 256 < BLOCKSIZE) { data[i] = data[i] + data[i + 256]; } __syncthreads(); }
    if(BLOCKSIZE > 128) { if(i < 128 && i + 128 < BLOCKSIZE) { data[i] = data[i] + data[i + 128]; } __syncthreads(); }
    if(BLOCKSIZE >  64) { if(i <  64 && i +  64 < BLOCKSIZE) { data[i] = data[i] + data[i +  64]; } __syncthreads(); }
    if(BLOCKSIZE >  32) { if(i <  32 && i +  32 < BLOCKSIZE) { data[i] = data[i] + data[i +  32]; } __syncthreads(); }
    if(BLOCKSIZE >  16) { if(i <  16 && i +  16 < BLOCKSIZE) { data[i] = data[i] + data[i +  16]; } __syncthreads(); }
    if(BLOCKSIZE >   8) { if(i <   8 && i +   8 < BLOCKSIZE) { data[i] = data[i] + data[i +   8]; } __syncthreads(); }
    if(BLOCKSIZE >   4) { if(i <   4 && i +   4 < BLOCKSIZE) { data[i] = data[i] + data[i +   4]; } __syncthreads(); }
    if(BLOCKSIZE >   2) { if(i <   2 && i +   2 < BLOCKSIZE) { data[i] = data[i] + data[i +   2]; } __syncthreads(); }
    if(BLOCKSIZE >   1) { if(i <   1 && i +   1 < BLOCKSIZE) { data[i] = data[i] + data[i +   1]; } __syncthreads(); }
}

// Block reduce kernel computing blockwide maximum entry
template <unsigned int BLOCKSIZE, typename T>
__device__ __forceinline__ void rocsparse_blockreduce_max(int i, T* data)
{
    if(BLOCKSIZE > 512) { if(i < 512 && i + 512 < BLOCKSIZE) { data[i] = max(data[i], data[i + 512]); } __syncthreads(); }
    if(BLOCKSIZE > 256) { if(i < 256 && i + 256 < BLOCKSIZE) { data[i] = max(data[i], data[i + 256]); } __syncthreads(); }
    if(BLOCKSIZE > 128) { if(i < 128 && i + 128 < BLOCKSIZE) { data[i] = max(data[i], data[i + 128]); } __syncthreads(); }
    if(BLOCKSIZE >  64) { if(i <  64 && i +  64 < BLOCKSIZE) { data[i] = max(data[i], data[i +  64]); } __syncthreads(); }
    if(BLOCKSIZE >  32) { if(i <  32 && i +  32 < BLOCKSIZE) { data[i] = max(data[i], data[i +  32]); } __syncthreads(); }
    if(BLOCKSIZE >  16) { if(i <  16 && i +  16 < BLOCKSIZE) { data[i] = max(data[i], data[i +  16]); } __syncthreads(); }
    if(BLOCKSIZE >   8) { if(i <   8 && i +   8 < BLOCKSIZE) { data[i] = max(data[i], data[i +   8]); } __syncthreads(); }
    if(BLOCKSIZE >   4) { if(i <   4 && i +   4 < BLOCKSIZE) { data[i] = max(data[i], data[i +   4]); } __syncthreads(); }
    if(BLOCKSIZE >   2) { if(i <   2 && i +   2 < BLOCKSIZE) { data[i] = max(data[i], data[i +   2]); } __syncthreads(); }
    if(BLOCKSIZE >   1) { if(i <   1 && i +   1 < BLOCKSIZE) { data[i] = max(data[i], data[i +   1]); } __syncthreads(); }
}

// Block reduce kernel computing blockwide minimum entry
template <unsigned int BLOCKSIZE, typename T>
__device__ __forceinline__ void rocsparse_blockreduce_min(int i, T* data)
{
    if(BLOCKSIZE > 512) { if(i < 512 && i + 512 < BLOCKSIZE) { data[i] = min(data[i], data[i + 512]); } __syncthreads(); }
    if(BLOCKSIZE > 256) { if(i < 256 && i + 256 < BLOCKSIZE) { data[i] = min(data[i], data[i + 256]); } __syncthreads(); }
    if(BLOCKSIZE > 128) { if(i < 128 && i + 128 < BLOCKSIZE) { data[i] = min(data[i], data[i + 128]); } __syncthreads(); }
    if(BLOCKSIZE >  64) { if(i <  64 && i +  64 < BLOCKSIZE) { data[i] = min(data[i], data[i +  64]); } __syncthreads(); }
    if(BLOCKSIZE >  32) { if(i <  32 && i +  32 < BLOCKSIZE) { data[i] = min(data[i], data[i +  32]); } __syncthreads(); }
    if(BLOCKSIZE >  16) { if(i <  16 && i +  16 < BLOCKSIZE) { data[i] = min(data[i], data[i +  16]); } __syncthreads(); }
    if(BLOCKSIZE >   8) { if(i <   8 && i +   8 < BLOCKSIZE) { data[i] = min(data[i], data[i +   8]); } __syncthreads(); }
    if(BLOCKSIZE >   4) { if(i <   4 && i +   4 < BLOCKSIZE) { data[i] = min(data[i], data[i +   4]); } __syncthreads(); }
    if(BLOCKSIZE >   2) { if(i <   2 && i +   2 < BLOCKSIZE) { data[i] = min(data[i], data[i +   2]); } __syncthreads(); }
    if(BLOCKSIZE >   1) { if(i <   1 && i +   1 < BLOCKSIZE) { data[i] = min(data[i], data[i +   1]); } __syncthreads(); }
}

#ifndef __gfx1030__
// DPP-based wavefront reduction maximum
template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_max(int* maximum)
{
    if(WFSIZE >  1) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x111, 0xf, 0xf, 0));
    if(WFSIZE >  2) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x112, 0xf, 0xf, 0));
    if(WFSIZE >  4) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x114, 0xf, 0xe, 0));
    if(WFSIZE >  8) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x118, 0xf, 0xc, 0));
    if(WFSIZE > 16) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x142, 0xa, 0xf, 0));
    if(WFSIZE > 32) *maximum = max(*maximum, __hip_move_dpp(*maximum, 0x143, 0xc, 0xf, 0));
}

// DPP-based wavefront reduction minimum
template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_min(int* minimum)
{
    if(WFSIZE >  1) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x111, 0xf, 0xf, 0));
    if(WFSIZE >  2) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x112, 0xf, 0xf, 0));
    if(WFSIZE >  4) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x114, 0xf, 0xe, 0));
    if(WFSIZE >  8) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x118, 0xf, 0xc, 0));
    if(WFSIZE > 16) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x142, 0xa, 0xf, 0));
    if(WFSIZE > 32) *minimum = min(*minimum, __hip_move_dpp(*minimum, 0x143, 0xc, 0xf, 0));
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_min(int64_t* minimum)
{
    typedef union i64_b32
    {
        int64_t i64;
        uint32_t b32[2];
    } i64_b32_t;

    i64_b32_t upper_min;
    i64_b32_t temp_min;
    temp_min.i64 = *minimum;

    if(WFSIZE > 1)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x111, 0xf, 0xf, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x111, 0xf, 0xf, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    if(WFSIZE > 2)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x112, 0xf, 0xf, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x112, 0xf, 0xf, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    if(WFSIZE > 4)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x114, 0xf, 0xe, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x114, 0xf, 0xe, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    if(WFSIZE > 8)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x118, 0xf, 0xc, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x118, 0xf, 0xc, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    if(WFSIZE > 16)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x142, 0xa, 0xf, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x142, 0xa, 0xf, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    if(WFSIZE > 32)
    {
        upper_min.b32[0] = __hip_move_dpp(temp_min.b32[0], 0x143, 0xc, 0xf, false);
        upper_min.b32[1] = __hip_move_dpp(temp_min.b32[1], 0x143, 0xc, 0xf, false);
        temp_min.i64 = min(temp_min.i64, upper_min.i64);
    }

    *minimum = temp_min.i64;
}

// DPP-based wavefront reduction sum
template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_sum(int* sum)
{
    if(WFSIZE >  1) *sum += __hip_move_dpp(*sum, 0x111, 0xf, 0xf, 0);
    if(WFSIZE >  2) *sum += __hip_move_dpp(*sum, 0x112, 0xf, 0xf, 0);
    if(WFSIZE >  4) *sum += __hip_move_dpp(*sum, 0x114, 0xf, 0xe, 0);
    if(WFSIZE >  8) *sum += __hip_move_dpp(*sum, 0x118, 0xf, 0xc, 0);
    if(WFSIZE > 16) *sum += __hip_move_dpp(*sum, 0x142, 0xa, 0xf, 0);
    if(WFSIZE > 32) *sum += __hip_move_dpp(*sum, 0x143, 0xc, 0xf, 0);
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_sum(int64_t* sum)
{
    typedef union i64_b32
    {
        int64_t i64;
        uint32_t b32[2];
    } i64_b32_t;

    i64_b32_t upper_sum;
    i64_b32_t temp_sum;
    temp_sum.i64 = *sum;

    if(WFSIZE > 1)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x111, 0xf, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x111, 0xf, 0xf, false);
        temp_sum.i64 += upper_sum.i64;
    }

    if(WFSIZE > 2)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x112, 0xf, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x112, 0xf, 0xf, false);
        temp_sum.i64 += upper_sum.i64;
    }

    if(WFSIZE > 4)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x114, 0xf, 0xe, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x114, 0xf, 0xe, false);
        temp_sum.i64 += upper_sum.i64;
    }

    if(WFSIZE > 8)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x118, 0xf, 0xc, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x118, 0xf, 0xc, false);
        temp_sum.i64 += upper_sum.i64;
    }

    if(WFSIZE > 16)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x142, 0xa, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x142, 0xa, 0xf, false);
        temp_sum.i64 += upper_sum.i64;
    }

    if(WFSIZE > 32)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x143, 0xc, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x143, 0xc, 0xf, false);
        temp_sum.i64 += upper_sum.i64;
    }

    *sum = temp_sum.i64;
}

// DPP-based float wavefront reduction sum
template <unsigned int WFSIZE>
__device__ __forceinline__ float rocsparse_wfreduce_sum(float sum)
{
    typedef union flt_b32
    {
        float val;
        uint32_t b32;
    } flt_b32_t;

    flt_b32_t upper_sum;
    flt_b32_t temp_sum;
    temp_sum.val = sum;

    if(WFSIZE > 1)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x111, 0xf, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 2)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x112, 0xf, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 4)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x114, 0xf, 0xe, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 8)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x118, 0xf, 0xc, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 16)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x142, 0xa, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 32)
    {
        upper_sum.b32 = __hip_move_dpp(temp_sum.b32, 0x143, 0xc, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    sum = temp_sum.val;
    return sum;
}

// DPP-based double wavefront reduction
template <unsigned int WFSIZE>
__device__ __forceinline__ double rocsparse_wfreduce_sum(double sum)
{
    typedef union dbl_b32
    {
        double val;
        uint32_t b32[2];
    } dbl_b32_t;

    dbl_b32_t upper_sum;
    dbl_b32_t temp_sum;
    temp_sum.val = sum;

    if(WFSIZE > 1)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x111, 0xf, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x111, 0xf, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 2)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x112, 0xf, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x112, 0xf, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 4)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x114, 0xf, 0xe, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x114, 0xf, 0xe, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 8)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x118, 0xf, 0xc, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x118, 0xf, 0xc, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 16)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x142, 0xa, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x142, 0xa, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    if(WFSIZE > 32)
    {
        upper_sum.b32[0] = __hip_move_dpp(temp_sum.b32[0], 0x143, 0xc, 0xf, false);
        upper_sum.b32[1] = __hip_move_dpp(temp_sum.b32[1], 0x143, 0xc, 0xf, false);
        temp_sum.val += upper_sum.val;
    }

    sum = temp_sum.val;
    return sum;
}
#else
template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_max(int* maximum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        *maximum = max(*maximum, __shfl_xor(*maximum, i));
    }
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_min(int* minimum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        *minimum = min(*minimum, __shfl_xor(*minimum, i));
    }
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_min(int64_t* minimum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        *minimum = min(*minimum, __shfl_xor(*minimum, i));
    }
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_sum(int* sum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        *sum += __shfl_xor(*sum, i);
    }
}

template <unsigned int WFSIZE>
__device__ __forceinline__ void rocsparse_wfreduce_sum(int64_t* sum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        *sum += __shfl_xor(*sum, i);
    }
}

template <unsigned int WFSIZE>
__device__ __forceinline__ float rocsparse_wfreduce_sum(float sum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        sum += __shfl_xor(sum, i);
    }

    return sum;
}

template <unsigned int WFSIZE>
__device__ __forceinline__ double rocsparse_wfreduce_sum(double sum)
{
    for(int i = WFSIZE >> 1; i > 0; i >>= 1)
    {
        sum += __shfl_xor(sum, i);
    }

    return sum;
}
#endif

// DPP-based complex float wavefront reduction sum
template <unsigned int WFSIZE>
__device__ __forceinline__ rocsparse_float_complex rocsparse_wfreduce_sum(rocsparse_float_complex sum)
{
    return rocsparse_float_complex(rocsparse_wfreduce_sum<WFSIZE>(std::real(sum)),
                                   rocsparse_wfreduce_sum<WFSIZE>(std::imag(sum)));
}

// DPP-based complex double wavefront reduction
template <unsigned int WFSIZE>
__device__ __forceinline__ rocsparse_double_complex rocsparse_wfreduce_sum(rocsparse_double_complex sum)
{
    return rocsparse_double_complex(rocsparse_wfreduce_sum<WFSIZE>(std::real(sum)),
                                    rocsparse_wfreduce_sum<WFSIZE>(std::imag(sum)));
}
// clang-format on

#endif // COMMON_H
