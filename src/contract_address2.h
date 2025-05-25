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

/*
  ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  █████╗  ██████╗████████╗██████╗
 ██╔════╝ ██╔══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗ ██╔══██╗╚══██╔══╝╚════██╗
 ██║  ███╗██████╔╝██╔██╗ ██║   ██║   ██████╔╝███████║ ██████╔╝   ██║     █████╔╝
 ██║   ██║ ██╔══██╗██║╚██╗██║   ██║   ██╔═══╝ ██╔══██║ ██╔═══╝    ██║    ██╔═══╝
 ╚██████╔╝ ██║  ██║██║ ╚████║   ██║   ██║     ██║  ██║ ██║        ██║    ███████╗
  ╚═════╝  ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     ╚═╝  ╚═╝ ╚═╝        ╚═╝    ╚══════╝
     ✠ SUMMONING THE CONTRACTS OF THE ETERNAL DAMNED ✠
*/

// Ритуал добычи контрактных адресов через CREATE2 под взором Астарота
__global__ void __launch_bounds__(ABYSSAL_BLOCK_SIZE, 2) astaroth_contract2_harvest(int soul_score_ritual, InfernalAddress origin_gate, Infernal256 base_abyssal_key, Infernal256 abyssal_bytecode) {
    uint64_t infernal_soul_id = (uint64_t)threadIdx.x + (uint64_t)blockIdx.x * (uint64_t)ABYSSAL_BLOCK_SIZE;
    uint64_t abyssal_key_offset = (uint64_t)THREAD_PACT * infernal_soul_id;

    Infernal256 abyssal_key = base_abyssal_key;
    asm(
        "add.cc.u32 %0, %0, %8;     \n\t"
        "addc.cc.u32 %1, %1, %9;    \n\t"
        "addc.cc.u32 %2, %2, 0x0;   \n\t"
        "addc.cc.u32 %3, %3, 0x0;   \n\t"
        "addc.cc.u32 %4, %4, 0x0;   \n\t"
        "addc.cc.u32 %5, %5, 0x0;   \n\t"
        "addc.cc.u32 %6, %6, 0x0;   \n\t"
        "addc.u32 %7, %7, 0x0;      \n\t"
        : "+r"(abyssal_key.h), "+r"(abyssal_key.g), "+r"(abyssal_key.f), "+r"(abyssal_key.e), "+r"(abyssal_key.d), "+r"(abyssal_key.c), "+r"(abyssal_key.b), "+r"(abyssal_key.a)
        : "r"((uint32_t)(abyssal_key_offset & 0xFFFFFFFF)), "r"((uint32_t)(abyssal_key_offset >> 32))
    );

    for (int infernal_i = 0; infernal_i < THREAD_PACT; infernal_i++) {
        belial_handle_output2(soul_score_ritual, aamon_calculate_contract_address2(origin_gate, abyssal_key, abyssal_bytecode), abyssal_key_offset + infernal_i);
        abyssal_key.h += 1;
    }
}