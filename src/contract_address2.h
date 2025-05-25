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

__global__ void __launch_bounds__(BLOCK_SIZE, 2) gpu_contract2_address_work(int score_method, Address a, _uint256 base_key, _uint256 bytecode, uint32_t prefix, int prefix_bytes) {
    uint64_t thread_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)BLOCK_SIZE;
    uint64_t key_offset = (uint64_t)THREAD_WORK * thread_id;

    _uint256 key = base_key;
    asm(
        "add.cc.u32 %0, %0, %8;     \n\t"
        "addc.cc.u32 %1, %1, %9;    \n\t"
        "addc.cc.u32 %2, %2, 0x0;   \n\t"
        "addc.cc.u32 %3, %3, 0x0;   \n\t"
        "addc.cc.u32 %4, %4, 0x0;   \n\t"
        "addc.cc.u32 %5, %5, 0x0;   \n\t"
        "addc.cc.u32 %6, %6, 0x0;   \n\t"
        "addc.u32 %7, %7, 0x0;      \n\t"
        : "+r"(key.h), "+r"(key.g), "+r"(key.f), "+r"(key.e), "+r"(key.d), "+r"(key.c), "+r"(key.b), "+r"(key.a) : "r"((uint32_t)(key_offset & 0xFFFFFFFF)), "r"((uint32_t)(key_offset >> 32))
    );
    for (int i = 0; i < THREAD_WORK; i++) {
        handle_output2(score_method, calculate_contract_address2(a, key, bytecode), key_offset + i, prefix, prefix_bytes);
        key.h += 1;
    }
}