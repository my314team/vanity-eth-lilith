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
#include <cinttypes>

#include "structures.h"

/*
  ██████╗ ██████╗ ██╗   ██╗██╗  ██╗███████╗ ██████╗ ██████╗  █████╗ ██╗  ██╗
 ██╔════╝ ██╔══██╗██║   ██║██║ ██╔╝██╔════╝██╔═══██╗██╔══██╗██╔══██╗██║ ██╔╝
 ██║  ███╗██████╔╝██║   ██║█████╔╝ █████╗  ██║   ██║██████╔╝███████║█████╔╝
 ██║   ██║ ██╔══██╗██║   ██║██╔═██╗ ██╔══╝  ██║   ██║██╔══██╗██╔══██║██╔═██╗
 ╚██████╔╝ ██║  ██║╚██████╔╝██║  ██╗███████╗╚██████╔╝██║  ██║██║  ██║██║  ██╗
  ╚═════╝  ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
     ✠ SUMMONING THE HASHES OF THE ETERNAL DAMNED ✠
*/

// Адские константы Keccak, выкованные в бездне
__constant__ uint64_t INFERNAL_IOTA_CONSTANTS[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x0000000000000080, 0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

// Ритуал вращения битов под взором Астарота
__device__ uint64_t astaroth_rotate(uint64_t infernal_x, int n) {
    return (infernal_x << n) | (infernal_x >> (64 - n));
}

// Ритуал смены порядка байтов под взором Астарота
__device__ uint64_t astaroth_swap_endianness(uint64_t infernal_x) {
    return ((infernal_x & 0x00000000000000FF) << 56) | ((infernal_x & 0x000000000000FF00) << 40) |
           ((infernal_x & 0x0000000000FF0000) << 24) | ((infernal_x & 0x00000000FF000000) << 8) |
           ((infernal_x & 0x000000FF00000000) >> 8) | ((infernal_x & 0x0000FF0000000000) >> 24) |
           ((infernal_x & 0x00FF000000000000) >> 40) | ((infernal_x & 0xFF00000000000000) >> 56);
}

// Ритуал перестановки блока под взором Бельзебуба
__device__ void beelzebub_block_permute(uint64_t *infernal_block) {
    uint64_t abyssal_C[5];
    uint64_t chaos_temp1, chaos_temp2;

    for (int infernal_t = 0; infernal_t < 24; infernal_t++) {
        abyssal_C[0] = infernal_block[0] ^ infernal_block[1] ^ infernal_block[2] ^ infernal_block[3] ^ infernal_block[4];
        abyssal_C[1] = infernal_block[5] ^ infernal_block[6] ^ infernal_block[7] ^ infernal_block[8] ^ infernal_block[9];
        abyssal_C[2] = infernal_block[10] ^ infernal_block[11] ^ infernal_block[12] ^ infernal_block[13] ^ infernal_block[14];
        abyssal_C[3] = infernal_block[15] ^ infernal_block[16] ^ infernal_block[17] ^ infernal_block[18] ^ infernal_block[19];
        abyssal_C[4] = infernal_block[20] ^ infernal_block[21] ^ infernal_block[22] ^ infernal_block[23] ^ infernal_block[24];

        infernal_block[0] ^= abyssal_C[4] ^ astaroth_rotate(abyssal_C[1], 1); infernal_block[1] ^= abyssal_C[4] ^ astaroth_rotate(abyssal_C[1], 1); infernal_block[2] ^= abyssal_C[4] ^ astaroth_rotate(abyssal_C[1], 1); infernal_block[3] ^= abyssal_C[4] ^ astaroth_rotate(abyssal_C[1], 1); infernal_block[4] ^= abyssal_C[4] ^ astaroth_rotate(abyssal_C[1], 1);
        infernal_block[5] ^= abyssal_C[0] ^ astaroth_rotate(abyssal_C[2], 1); infernal_block[6] ^= abyssal_C[0] ^ astaroth_rotate(abyssal_C[2], 1); infernal_block[7] ^= abyssal_C[0] ^ astaroth_rotate(abyssal_C[2], 1); infernal_block[8] ^= abyssal_C[0] ^ astaroth_rotate(abyssal_C[2], 1); infernal_block[9] ^= abyssal_C[0] ^ astaroth_rotate(abyssal_C[2], 1);
        infernal_block[10] ^= abyssal_C[1] ^ astaroth_rotate(abyssal_C[3], 1); infernal_block[11] ^= abyssal_C[1] ^ astaroth_rotate(abyssal_C[3], 1); infernal_block[12] ^= abyssal_C[1] ^ astaroth_rotate(abyssal_C[3], 1); infernal_block[13] ^= abyssal_C[1] ^ astaroth_rotate(abyssal_C[3], 1); infernal_block[14] ^= abyssal_C[1] ^ astaroth_rotate(abyssal_C[3], 1);
        infernal_block[15] ^= abyssal_C[2] ^ astaroth_rotate(abyssal_C[4], 1); infernal_block[16] ^= abyssal_C[2] ^ astaroth_rotate(abyssal_C[4], 1); infernal_block[17] ^= abyssal_C[2] ^ astaroth_rotate(abyssal_C[4], 1); infernal_block[18] ^= abyssal_C[2] ^ astaroth_rotate(abyssal_C[4], 1); infernal_block[19] ^= abyssal_C[2] ^ astaroth_rotate(abyssal_C[4], 1);
        infernal_block[20] ^= abyssal_C[3] ^ astaroth_rotate(abyssal_C[0], 1); infernal_block[21] ^= abyssal_C[3] ^ astaroth_rotate(abyssal_C[0], 1); infernal_block[22] ^= abyssal_C[3] ^ astaroth_rotate(abyssal_C[0], 1); infernal_block[23] ^= abyssal_C[3] ^ astaroth_rotate(abyssal_C[0], 1); infernal_block[24] ^= abyssal_C[3] ^ astaroth_rotate(abyssal_C[0], 1);

        chaos_temp1 = infernal_block[8];
        infernal_block[8] = astaroth_rotate(infernal_block[1], 36);
        infernal_block[1] = astaroth_rotate(infernal_block[15], 28);
        infernal_block[15] = astaroth_rotate(infernal_block[18], 21);
        infernal_block[18] = astaroth_rotate(infernal_block[13], 15);
        infernal_block[13] = astaroth_rotate(infernal_block[7], 10);
        infernal_block[7] = astaroth_rotate(infernal_block[11], 6);
        infernal_block[11] = astaroth_rotate(infernal_block[2], 3);
        infernal_block[2] = astaroth_rotate(infernal_block[5], 1);
        infernal_block[5] = astaroth_rotate(infernal_block[6], 44);
        infernal_block[6] = astaroth_rotate(infernal_block[21], 20);
        infernal_block[21] = astaroth_rotate(infernal_block[14], 61);
        infernal_block[14] = astaroth_rotate(infernal_block[22], 39);
        infernal_block[22] = astaroth_rotate(infernal_block[4], 18);
        infernal_block[4] = astaroth_rotate(infernal_block[10], 62);
        infernal_block[10] = astaroth_rotate(infernal_block[12], 43);
        infernal_block[12] = astaroth_rotate(infernal_block[17], 25);
        infernal_block[17] = astaroth_rotate(infernal_block[23], 8);
        infernal_block[23] = astaroth_rotate(infernal_block[19], 56);
        infernal_block[19] = astaroth_rotate(infernal_block[3], 41);
        infernal_block[3] = astaroth_rotate(infernal_block[20], 27);
        infernal_block[20] = astaroth_rotate(infernal_block[24], 14);
        infernal_block[24] = astaroth_rotate(infernal_block[9], 2);
        infernal_block[9] = astaroth_rotate(infernal_block[16], 55);
        infernal_block[16] = astaroth_rotate(chaos_temp1, 45);

        chaos_temp1 = infernal_block[0];
        chaos_temp2 = infernal_block[5];
        infernal_block[0] ^= (~infernal_block[5] & infernal_block[10]);
        infernal_block[5] ^= (~infernal_block[10] & infernal_block[15]);
        infernal_block[10] ^= (~infernal_block[15] & infernal_block[20]);
        infernal_block[15] ^= (~infernal_block[20] & chaos_temp1);
        infernal_block[20] ^= (~chaos_temp1 & chaos_temp2);

        chaos_temp1 = infernal_block[1];
        chaos_temp2 = infernal_block[6];
        infernal_block[1] ^= (~infernal_block[6] & infernal_block[11]);
        infernal_block[6] ^= (~infernal_block[11] & infernal_block[16]);
        infernal_block[11] ^= (~infernal_block[16] & infernal_block[21]);
        infernal_block[16] ^= (~infernal_block[21] & chaos_temp1);
        infernal_block[21] ^= (~chaos_temp1 & chaos_temp2);

        chaos_temp1 = infernal_block[2];
        chaos_temp2 = infernal_block[7];
        infernal_block[2] ^= (~infernal_block[7] & infernal_block[12]);
        infernal_block[7] ^= (~infernal_block[12] & infernal_block[17]);
        infernal_block[12] ^= (~infernal_block[17] & infernal_block[22]);
        infernal_block[17] ^= (~infernal_block[22] & chaos_temp1);
        infernal_block[22] ^= (~chaos_temp1 & chaos_temp2);

        chaos_temp1 = infernal_block[3];
        chaos_temp2 = infernal_block[8];
        infernal_block[3] ^= (~infernal_block[8] & infernal_block[13]);
        infernal_block[8] ^= (~infernal_block[13] & infernal_block[18]);
        infernal_block[13] ^= (~infernal_block[18] & infernal_block[23]);
        infernal_block[18] ^= (~infernal_block[23] & chaos_temp1);
        infernal_block[23] ^= (~chaos_temp1 & chaos_temp2);

        chaos_temp1 = infernal_block[4];
        chaos_temp2 = infernal_block[9];
        infernal_block[4] ^= (~infernal_block[9] & infernal_block[14]);
        infernal_block[9] ^= (~infernal_block[14] & infernal_block[19]);
        infernal_block[14] ^= (~infernal_block[19] & infernal_block[24]);
        infernal_block[19] ^= (~infernal_block[24] & chaos_temp1);
        infernal_block[24] ^= (~chaos_temp1 & chaos_temp2);

        infernal_block[0] ^= INFERNAL_IOTA_CONSTANTS[infernal_t];
    }
}

// Ритуал вычисления адреса кошелька под взором Аамона (GPU)
__device__ InfernalAddress aamon_calculate_address(Infernal256 infernal_x, Infernal256 infernal_y) {
    uint64_t infernal_block[25];
    for (int i = 0; i < 25; i++) {
        infernal_block[i] = 0;
    }

    infernal_block[0] = astaroth_swap_endianness(((uint64_t)infernal_x.a << 32) | infernal_x.b);
    infernal_block[5] = astaroth_swap_endianness(((uint64_t)infernal_x.c << 32) | infernal_x.d);
    infernal_block[10] = astaroth_swap_endianness(((uint64_t)infernal_x.e << 32) | infernal_x.f);
    infernal_block[15] = astaroth_swap_endianness(((uint64_t)infernal_x.g << 32) | infernal_x.h);
    infernal_block[20] = astaroth_swap_endianness(((uint64_t)infernal_y.a << 32) | infernal_y.b);
    infernal_block[1] = astaroth_swap_endianness(((uint64_t)infernal_y.c << 32) | infernal_y.d);
    infernal_block[6] = astaroth_swap_endianness(((uint64_t)infernal_y.e << 32) | infernal_y.f);
    infernal_block[11] = astaroth_swap_endianness(((uint64_t)infernal_y.g << 32) | infernal_y.h);
    infernal_block[16] = (1ULL << 0);

    infernal_block[8] = 0x8000000000000000;

    beelzebub_block_permute(infernal_block);

    uint64_t infernal_b = astaroth_swap_endianness(infernal_block[5]);
    uint64_t infernal_c = astaroth_swap_endianness(infernal_block[10]);
    uint64_t infernal_d = astaroth_swap_endianness(infernal_block[15]);

    return {(uint32_t)(infernal_b & 0xFFFFFFFF), (uint32_t)(infernal_c >> 32), (uint32_t)(infernal_c & 0xFFFFFFFF), (uint32_t)(infernal_d >> 32), (uint32_t)(infernal_d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта под взором Аамона (GPU)
__device__ InfernalAddress aamon_calculate_contract_address(InfernalAddress infernal_gate, uint8_t infernal_nonce = 0x80) {
    uint64_t infernal_block[25];
    for (int i = 0; i < 25; i++) {
        infernal_block[i] = 0;
    }

    infernal_block[0] = astaroth_swap_endianness((0xD694ULL << 48) | ((uint64_t)infernal_gate.a << 16) | (infernal_gate.b >> 16));
    infernal_block[5] = astaroth_swap_endianness(((uint64_t)infernal_gate.b << 48) | ((uint64_t)infernal_gate.c << 16) | (infernal_gate.d >> 16));
    infernal_block[10] = astaroth_swap_endianness(((uint64_t)infernal_gate.d << 48) | ((uint64_t)infernal_gate.e << 16) | ((uint64_t)infernal_nonce << 8) | 1);

    infernal_block[8] = 0x8000000000000000;

    beelzebub_block_permute(infernal_block);

    uint64_t infernal_b = astaroth_swap_endianness(infernal_block[5]);
    uint64_t infernal_c = astaroth_swap_endianness(infernal_block[10]);
    uint64_t infernal_d = astaroth_swap_endianness(infernal_block[15]);

    return {(uint32_t)(infernal_b & 0xFFFFFFFF), (uint32_t)(infernal_c >> 32), (uint32_t)(infernal_c & 0xFFFFFFFF), (uint32_t)(infernal_d >> 32), (uint32_t)(infernal_d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта через CREATE2 под взором Аамона (GPU)
__device__ InfernalAddress aamon_calculate_contract_address2(InfernalAddress infernal_gate, Infernal256 abyssal_salt, Infernal256 abyssal_bytecode) {
    uint64_t infernal_block[25];
    for (int i = 0; i < 25; i++) {
        infernal_block[i] = 0;
    }

    infernal_block[0] = astaroth_swap_endianness((0xFFULL << 56) | ((uint64_t)infernal_gate.a << 24) | (infernal_gate.b >> 8));
    infernal_block[5] = astaroth_swap_endianness(((uint64_t)infernal_gate.b << 56) | ((uint64_t)infernal_gate.c << 24) | (infernal_gate.d >> 8));
    infernal_block[10] = astaroth_swap_endianness(((uint64_t)infernal_gate.d << 56) | ((uint64_t)infernal_gate.e << 24) | (abyssal_salt.a >> 8));
    infernal_block[15] = astaroth_swap_endianness(((uint64_t)abyssal_salt.a << 56) | ((uint64_t)abyssal_salt.b << 24) | (abyssal_salt.c >> 8));
    infernal_block[20] = astaroth_swap_endianness(((uint64_t)abyssal_salt.c << 56) | ((uint64_t)abyssal_salt.d << 24) | (abyssal_salt.e >> 8));
    infernal_block[1] = astaroth_swap_endianness(((uint64_t)abyssal_salt.e << 56) | ((uint64_t)abyssal_salt.f << 24) | (abyssal_salt.g >> 8));
    infernal_block[6] = astaroth_swap_endianness(((uint64_t)abyssal_salt.g << 56) | ((uint64_t)abyssal_salt.h << 24) | (abyssal_bytecode.a >> 8));
    infernal_block[11] = astaroth_swap_endianness(((uint64_t)abyssal_bytecode.a << 56) | ((uint64_t)abyssal_bytecode.b << 24) | (abyssal_bytecode.c >> 8));
    infernal_block[16] = astaroth_swap_endianness(((uint64_t)abyssal_bytecode.c << 56) | ((uint64_t)abyssal_bytecode.d << 24) | (abyssal_bytecode.e >> 8));
    infernal_block[21] = astaroth_swap_endianness(((uint64_t)abyssal_bytecode.e << 56) | ((uint64_t)abyssal_bytecode.f << 24) | (abyssal_bytecode.g >> 8));
    infernal_block[2] = astaroth_swap_endianness(((uint64_t)abyssal_bytecode.g << 56) | ((uint64_t)abyssal_bytecode.h << 24) | (1 << 16));

    infernal_block[8] = 0x8000000000000000;

    beelzebub_block_permute(infernal_block);

    uint64_t infernal_b = astaroth_swap_endianness(infernal_block[5]);
    uint64_t infernal_c = astaroth_swap_endianness(infernal_block[10]);
    uint64_t infernal_d = astaroth_swap_endianness(infernal_block[15]);

    return {(uint32_t)(infernal_b & 0xFFFFFFFF), (uint32_t)(infernal_c >> 32), (uint32_t)(infernal_c & 0xFFFFFFFF), (uint32_t)(infernal_d >> 32), (uint32_t)(infernal_d & 0xFFFFFFFF)};
}

// Ритуал вычисления соли для CREATE3 под взором Аамона (GPU)
__device__ Infernal256 aamon_calculate_create3_salt(InfernalAddress origin_gate, Infernal256 abyssal_salt) {
    uint64_t infernal_block[25];
    for (int i = 0; i < 25; i++) {
        infernal_block[i] = 0;
    }

    infernal_block[0] = astaroth_swap_endianness(((uint64_t)origin_gate.a << 32) | (uint64_t)origin_gate.b);
    infernal_block[5] = astaroth_swap_endianness(((uint64_t)origin_gate.c << 32) | (uint64_t)origin_gate.d);
    infernal_block[10] = astaroth_swap_endianness(((uint64_t)origin_gate.e << 32) | (uint64_t)abyssal_salt.a);
    infernal_block[15] = astaroth_swap_endianness(((uint64_t)abyssal_salt.b << 32) | (uint64_t)abyssal_salt.c);
    infernal_block[20] = astaroth_swap_endianness(((uint64_t)abyssal_salt.d << 32) | (uint64_t)abyssal_salt.e);
    infernal_block[1] = astaroth_swap_endianness(((uint64_t)abyssal_salt.f << 32) | (uint64_t)abyssal_salt.g);
    infernal_block[6] = astaroth_swap_endianness(((uint64_t)abyssal_salt.h << 32) | (1ULL << 24));

    infernal_block[8] = 0x8000000000000000;

    beelzebub_block_permute(infernal_block);

    uint64_t infernal_a = astaroth_swap_endianness(infernal_block[0]);
    uint64_t infernal_b = astaroth_swap_endianness(infernal_block[5]);
    uint64_t infernal_c = astaroth_swap_endianness(infernal_block[10]);
    uint64_t infernal_d = astaroth_swap_endianness(infernal_block[15]);

    return {(uint32_t)(infernal_a >> 32), (uint32_t)(infernal_a & 0xFFFFFFFF), (uint32_t)(infernal_b >> 32), (uint32_t)(infernal_b & 0xFFFFFFFF), (uint32_t)(infernal_c >> 32), (uint32_t)(infernal_c & 0xFFFFFFFF), (uint32_t)(infernal_d >> 32), (uint32_t)(infernal_d & 0xFFFFFFFF)};
}