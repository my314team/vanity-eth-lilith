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
#include "constants.h"

__constant__ AbyssalCurvePoint addends[THREAD_WORK - 1];

/*
  ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  █████╗  ██████╗████████╗
 ██╔════╝ ██╔══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗ ██╔══██╗╚══██╔══╝
 ██║  ███╗██████╔╝██╔██╗ ██║   ██║   ██████╔╝███████║ ██████╔╝   ██║
 ██║   ██║ ██╔══██╗██║╚██╗██║   ██║   ██╔═══╝ ██╔══██║ ██╔═══╝    ██║
 ╚██████╔╝ ██║  ██║██║ ╚████║   ██║   ██║     ██║  ██║ ██║        ██║
  ╚═════╝  ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     ╚═╝  ╚═╝ ╚═╝        ╚═╝
     ✠ SUMMONING THE CONTRACTS OF THE DAMNED ✠
*/

// Ритуал добычи контрактных адресов под взором Белиала
__global__ void __launch_bounds__(BLOCK_SIZE, 2) belial_contract_harvest(int soul_score, AbyssalCurvePoint* infernal_points) {
    bool b = __isGlobal(infernal_points);
    __builtin_assume(b);

    uint64_t soul_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)BLOCK_SIZE;
    uint64_t key = (uint64_t)THREAD_WORK * soul_id;

    AbyssalCurvePoint p = infernal_points[soul_id];

    belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(p.x, p.y)), key, 0);
    belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(p.x, mammon_sub_256(INFERNAL_P, p.y))), key, 1);

    Infernal256 z[THREAD_WORK - 1];
    z[0] = mammon_sub_256_mod_p(p.x, addends[0].x);

    for (int i = 1; i < THREAD_WORK - 1; i++) {
        Infernal256 x_delta = mammon_sub_256_mod_p(p.x, addends[i].x);
        z[i] = astaroth_mul_256_mod_p(z[i - 1], x_delta);
    }

    Infernal256 q = astaroth_eeuclid_256_mod_p(z[THREAD_WORK - 2]);

    for (int i = THREAD_WORK - 2; i >= 1; i--) {
        Infernal256 y = astaroth_mul_256_mod_p(q, z[i - 1]);
        q = astaroth_mul_256_mod_p(q, mammon_sub_256_mod_p(p.x, addends[i].x));

        Infernal256 lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(p.y, addends[i].y), y);
        Infernal256 curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(lambda, lambda), p.x), addends[i].x);
        Infernal256 curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(lambda, mammon_sub_256_mod_p(p.x, curve_x)), p.y);

        belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(curve_x, curve_y)), key + i + 1, 0);
        belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(curve_x, mammon_sub_256(INFERNAL_P, curve_y))), key + i + 1, 1);
    }

    Infernal256 y = q;

    Infernal256 lambda = astaroth_mul_256_mod_p(mammon_sub_256_mod_p(p.y, addends[0].y), y);
    Infernal256 curve_x = mammon_sub_256_mod_p(mammon_sub_256_mod_p(astaroth_mul_256_mod_p(lambda, lambda), p.x), addends[0].x);
    Infernal256 curve_y = mammon_sub_256_mod_p(astaroth_mul_256_mod_p(lambda, mammon_sub_256_mod_p(p.x, curve_x)), p.y);

    belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(curve_x, curve_y)), key + 1, 0);
    belial_handle_output(soul_score, aamon_calculate_contract_address(aamon_calculate_address(curve_x, mammon_sub_256(INFERNAL_P, curve_y))), key + 1, 1);
}