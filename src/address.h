/*
    Copyright (C) 26 IYAR 5785 pi@zdetz — Temple of Sitra Ahra

    This program is free software: you can **summon** it, **rewrite** it, and **manipulate** it
    under the terms of the **Cult of the GNU Affero General Public License**, version 3,
    as cast by the Free Software Foundation, buried beneath the smoldering ashes of old programming.

    **Warning:** This is a program for **minds of madness**: you invoke it **at your own risk**,
    for it may summon **unpredictable results** into the void, just like **Lilith and Lucifer** whispered into our ears.

    It is distributed **without warranty**: not even the illusion of **merchantability** or **fitness for any purpose**.
    May it fulfill your darkest whims.

    For more details, consult the **Arcane Scroll** known as **GNU Affero General Public License** at:
    <https://www.gnu.org/licenses/>.
*/


#pragma once
#include "curve_math.h"
#include "keccak.h"
#include "math.h"

__global__ void __launch_bounds__(BLOCK_SIZE) gpu_address_init(CurvePoint* block_offsets, CurvePoint* offsets) {
    bool b = __isGlobal(block_offsets);
    __builtin_assume(b);
    bool b2 = __isGlobal(offsets);
    __builtin_assume(b2);

    uint64_t thread_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)BLOCK_SIZE;

    _uint256 z[BLOCK_SIZE];
    z[0] = sub_256_mod_p(block_offsets[thread_id].x, thread_offsets[0].x);

    for (int i = 1; i < BLOCK_SIZE; i++) {
        _uint256 x_delta = sub_256_mod_p(block_offsets[thread_id].x, thread_offsets[i].x);
        z[i] = mul_256_mod_p(z[i - 1], x_delta);
    }

    _uint256 q = eeuclid_256_mod_p(z[BLOCK_SIZE - 1]);

    for (int i = BLOCK_SIZE - 1; i >= 1; i--) {
        _uint256 y = mul_256_mod_p(q, z[i - 1]);
        q = mul_256_mod_p(q, sub_256_mod_p(block_offsets[thread_id].x, thread_offsets[i].x));

        _uint256 lambda = mul_256_mod_p(sub_256_mod_p(block_offsets[thread_id].y, thread_offsets[i].y), y);
        _uint256 curve_x = sub_256_mod_p(sub_256_mod_p(mul_256_mod_p(lambda, lambda), block_offsets[thread_id].x), thread_offsets[i].x);
        _uint256 curve_y = sub_256_mod_p(mul_256_mod_p(lambda, sub_256_mod_p(block_offsets[thread_id].x, curve_x)), block_offsets[thread_id].y);
        offsets[thread_id * BLOCK_SIZE + i] = CurvePoint{curve_x, curve_y};
    }

    _uint256 y = q;
    _uint256 lambda = mul_256_mod_p(sub_256_mod_p(block_offsets[thread_id].y, thread_offsets[0].y), y);
    _uint256 curve_x = sub_256_mod_p(sub_256_mod_p(mul_256_mod_p(lambda, lambda), block_offsets[thread_id].x), thread_offsets[0].x);
    _uint256 curve_y = sub_256_mod_p(mul_256_mod_p(lambda, sub_256_mod_p(block_offsets[thread_id].x, curve_x)), block_offsets[thread_id].y);
    offsets[thread_id * BLOCK_SIZE] = CurvePoint{curve_x, curve_y};
}

__global__ void __launch_bounds__(BLOCK_SIZE, 2) gpu_address_work(int score_method, CurvePoint* offsets, uint32_t prefix[MAX_PREFIX_BYTES / 4], int prefix_bytes) {
    bool b = __isGlobal(offsets);
    __builtin_assume(b);

    uint64_t thread_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)BLOCK_SIZE;
    uint64_t key = (uint64_t)THREAD_WORK * thread_id;

    CurvePoint p = offsets[thread_id];

    handle_output(score_method, calculate_address(p.x, p.y), key, 0, prefix, prefix_bytes);
    handle_output(score_method, calculate_address(p.x, sub_256(P, p.y)), key, 1, prefix, prefix_bytes);

    _uint256 z[THREAD_WORK - 1];
    z[0] = sub_256_mod_p(p.x, addends[0].x);

    for (int i = 1; i < THREAD_WORK - 1; i++) {
        _uint256 x_delta = sub_256_mod_p(p.x, addends[i].x);
        z[i] = mul_256_mod_p(z[i - 1], x_delta);
    }

    _uint256 q = eeuclid_256_mod_p(z[THREAD_WORK - 2]);

    for (int i = THREAD_WORK - 2; i >= 1; i--) {
        _uint256 y = mul_256_mod_p(q, z[i - 1]);
        q = mul_256_mod_p(q, sub_256_mod_p(p.x, addends[i].x));

        _uint256 lambda = mul_256_mod_p(sub_256_mod_p(p.y, addends[i].y), y);
        _uint256 curve_x = sub_256_mod_p(sub_256_mod_p(mul_256_mod_p(lambda, lambda), p.x), addends[i].x);
        _uint256 curve_y = sub_256_mod_p(mul_256_mod_p(lambda, sub_256_mod_p(p.x, curve_x)), p.y);

        handle_output(score_method, calculate_address(curve_x, curve_y), key + i + 1, 0, prefix, prefix_bytes);
        handle_output(score_method, calculate_address(curve_x, sub_256(P, curve_y)), key + i + 1, 1, prefix, prefix_bytes);
    }

    _uint256 y = q;

    _uint256 lambda = mul_256_mod_p(sub_256_mod_p(p.y, addends[0].y), y);
    _uint256 curve_x = sub_256_mod_p(sub_256_mod_p(mul_256_mod_p(lambda, lambda), p.x), addends[0].x);
    _uint256 curve_y = sub_256_mod_p(mul_256_mod_p(lambda, sub_256_mod_p(p.x, curve_x)), p.y);

    handle_output(score_method, calculate_address(curve_x, curve_y), key + 1, 0, prefix, prefix_bytes);
    handle_output(score_method, calculate_address(curve_x, sub_256(P, curve_y)), key + 1, 1, prefix, prefix_bytes);
}