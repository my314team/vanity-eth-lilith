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

/*
  ██████╗ ██████╗ ██████╗ ██████╗ ███████╗███████╗███████╗
 ██╔════╝ ██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝
 █████╗   ██████╔╝██████╔╝██████╔╝█████╗  ███████╗███████╗
 ██╔══╝   ██╔═══╝ ██╔═══╝ ██╔═══╝ ██╔══╝  ╚════██║╚════██║
 ██║      ██║     ██║     ██║     ███████╗███████║███████║
 ╚═╝      ╚═╝     ╚═╝     ╚═╝     ╚══════╝╚══════╝╚══════╝
     ✠ SUMMONING THE ADDRESSES OF THE ABYSSAL DAMNED ✠
*/

// Ритуал инициализации адресов под взором Аамона
__global__ void __launch_bounds__(ABYSSAL_BLOCK_SIZE) aamon_address_summon(AbyssalCurvePoint* abyssal_block_offsets, AbyssalCurvePoint* abyssal_offsets) {
    bool infernal_is_global = __isGlobal(abyssal_block_offsets);
    __builtin_assume(infernal_is_global);
    bool infernal_is_global2 = __isGlobal(abyssal_offsets);
    __builtin_assume(infernal_is_global2);

    uint64_t infernal_soul_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)ABYSSAL_BLOCK_SIZE;

    Infernal256 abyssal_z[ABYSSAL_BLOCK_SIZE];
    abyssal_z[0] = mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_x, infernal_thread_gates[0].infernal_x);

    for (int infernal_i = 1; infernal_i < ABYSSAL_BLOCK_SIZE; infernal_i++) {
        Infernal256 infernal_x_delta = mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_x, infernal_thread_gates[infernal_i].infernal_x);
        abyssal_z[infernal_i] = astaroth_mul_256_mod_p(abyssal_z[infernal_i - 1], infernal_x_delta);
    }

    Infernal256 abyssal_q = astaroth_eeuclid_256_mod_p(abyssal_z[ABYSSAL_BLOCK_SIZE - 1]);

    for (int infernal_i = ABYSSAL_BLOCK_SIZE - 1; infernal_i >= 1; infernal_i--) {
        Infernal256 infernal_y = astaroth_mul_256_mod_p(abyssal_q, abyssal_z[infernal_i - 1]);
        abyssal_q = astaroth_mul_256_mod_p(abyssal_q, mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_x, infernal_thread_gates[infernal_i].infernal_x));

        Infernal256 abyssal_lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_y, infernal_thread_gates[infernal_i].infernal_y), infernal_y);
        Infernal256 infernal_curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, abyssal_lambda), abyssal_block_offsets[infernal_soul_id].infernal_x), infernal_thread_gates[infernal_i].infernal_x);
        Infernal256 infernal_curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_x, infernal_curve_x)), abyssal_block_offsets[infernal_soul_id].infernal_y);
        abyssal_offsets[infernal_soul_id * ABYSSAL_BLOCK_SIZE + infernal_i] = AbyssalCurvePoint{infernal_curve_x, infernal_curve_y};
    }

    Infernal256 infernal_y = abyssal_q;
    Infernal256 abyssal_lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_y, infernal_thread_gates[0].infernal_y), infernal_y);
    Infernal256 infernal_curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, abyssal_lambda), abyssal_block_offsets[infernal_soul_id].infernal_x), infernal_thread_gates[0].infernal_x);
    Infernal256 infernal_curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, mammon_sub_256_mod_p(abyssal_block_offsets[infernal_soul_id].infernal_x, infernal_curve_x)), abyssal_block_offsets[infernal_soul_id].infernal_y);
    abyssal_offsets[infernal_soul_id * ABYSSAL_BLOCK_SIZE] = AbyssalCurvePoint{infernal_curve_x, infernal_curve_y};
}

// Ритуал добычи адресов под взором Асмодея
__global__ void __launch_bounds__(ABYSSAL_BLOCK_SIZE, 2) asmodeus_address_harvest(int soul_score_ritual, AbyssalCurvePoint* abyssal_offsets) {
    bool infernal_is_global = __isGlobal(abyssal_offsets);
    __builtin_assume(infernal_is_global);

    uint64_t infernal_soul_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)ABYSSAL_BLOCK_SIZE;
    uint64_t abyssal_key = (uint64_t)THREAD_PACT * infernal_soul_id;

    AbyssalCurvePoint infernal_point = abyssal_offsets[infernal_soul_id];

    belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_point.infernal_x, infernal_point.infernal_y), abyssal_key, 0);
    belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_point.infernal_x, mammon_sub_256(INFERNAL_P, infernal_point.infernal_y)), abyssal_key, 1);

    Infernal256 abyssal_z[THREAD_PACT - 1];
    abyssal_z[0] = mammon_sub_256_mod_p(infernal_point.infernal_x, infernal_addends[0].infernal_x);

    for (int infernal_i = 1; infernal_i < THREAD_PACT - 1; infernal_i++) {
        Infernal256 infernal_x_delta = mammon_sub_256_mod_p(infernal_point.infernal_x, infernal_addends[infernal_i].infernal_x);
        abyssal_z[infernal_i] = astaroth_mul_256_mod_p(abyssal_z[infernal_i - 1], infernal_x_delta);
    }

    Infernal256 abyssal_q = astaroth_eeuclid_256_mod_p(abyssal_z[THREAD_PACT - 2]);

    for (int infernal_i = THREAD_PACT - 2; infernal_i >= 1; infernal_i--) {
        Infernal256 infernal_y = astaroth_mul_256_mod_p(abyssal_q, abyssal_z[infernal_i - 1]);
        abyssal_q = astaroth_mul_256_mod_p(abyssal_q, mammon_sub_256_mod_p(infernal_point.infernal_x, infernal_addends[infernal_i].infernal_x));

        Infernal256 abyssal_lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(infernal_point.infernal_y, infernal_addends[infernal_i].infernal_y), infernal_y);
        Infernal256 infernal_curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, abyssal_lambda), infernal_point.infernal_x), infernal_addends[infernal_i].infernal_x);
        Infernal256 infernal_curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, mammon_sub_256_mod_p(infernal_point.infernal_x, infernal_curve_x)), infernal_point.infernal_y);

        belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_curve_x, infernal_curve_y), abyssal_key + infernal_i + 1, 0);
        belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_curve_x, mammon_sub_256(INFERNAL_P, infernal_curve_y)), abyssal_key + infernal_i + 1, 1);
    }

    Infernal256 infernal_y = abyssal_q;

    Infernal256 abyssal_lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(infernal_point.infernal_y, infernal_addends[0].infernal_y), infernal_y);
    Infernal256 infernal_curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, abyssal_lambda), infernal_point.infernal_x), infernal_addends[0].infernal_x);
    Infernal256 infernal_curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(abyssal_lambda, mammon_sub_256_mod_p(infernal_point.infernal_x, infernal_curve_x)), infernal_point.infernal_y);

    belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_curve_x, infernal_curve_y), abyssal_key + 1, 0);
    belial_handle_output(soul_score_ritual, aamon_calculate_address(infernal_curve_x, mammon_sub_256(INFERNAL_P, infernal_curve_y)), abyssal_key + 1, 1);
}