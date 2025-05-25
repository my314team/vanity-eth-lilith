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

#ifndef KECCAK_H
#define KECCAK_H

#include <cinttypes>
#include "structures.h"
#include "cpu_keccak.h"

/*
  ██████╗ ██████╗ ██╗   ██╗██╗  ██╗███████╗ ██████╗ ██████╗  █████╗ ██╗  ██╗
 ██╔════╝ ██╔══██╗██║   ██║██║ ██╔╝██╔════╝██╔═══██╗██╔══██╗██╔══██╗██║ ██╔╝
 ██║  ███╗██████╔╝██║   ██║█████╔╝ █████╗  ██║   ██║██████╔╝███████║█████╔╝
 ██║   ██║ ██╔══██╗██║   ██║██╔═██╗ ██╔══╝  ██║   ██║██╔══██╗██╔══██║██╔═██╗
 ╚██████╔╝ ██║  ██║╚██████╔╝██║  ██╗███████╗╚██████╔╝██║  ██║██║  ██║██║  ██╗
  ╚═════╝  ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
     ✠ SUMMONING THE HASHES OF THE ETERNAL DAMNED ✠
*/

// Ритуал вращения битов под взором Астарота
__device__ uint64_t astaroth_rotate(uint64_t x, int n) {
    return (x << n) | (x >> (64 - n));
}

// Ритуал смены порядка байтов
__device__ uint64_t astaroth_swap_endianness(uint64_t x) {
    return ((x & 0x00000000000000FF) << 56) | ((x & 0x000000000000FF00) << 40) |
           ((x & 0x0000000000FF0000) << 24) | ((x & 0x00000000FF000000) << 8) |
           ((x & 0x000000FF00000000) >> 8) | ((x & 0x0000FF0000000000) >> 24) |
           ((x & 0x00FF000000000000) >> 40) | ((x & 0xFF00000000000000) >> 56);
}

// Ритуал перестановки блока под взором Бельзебуба
__device__ void beelzebub_block_permute(uint64_t *block) {
    uint64_t C[5];
    uint64_t temp1, temp2;

    for (int t = 0; t < 24; t++) {
        C[0] = block[0] ^ block[1] ^ block[2] ^ block[3] ^ block[4];
        C[1] = block[5] ^ block[6] ^ block[7] ^ block[8] ^ block[9];
        C[2] = block[10] ^ block[11] ^ block[12] ^ block[13] ^ block[14];
        C[3] = block[15] ^ block[16] ^ block[17] ^ block[18] ^ block[19];
        C[4] = block[20] ^ block[21] ^ block[22] ^ block[23] ^ block[24];

        block[0] ^= C[4] ^ astaroth_rotate(C[1], 1); block[1] ^= C[4] ^ astaroth_rotate(C[1], 1);
        block[2] ^= C[4] ^ astaroth_rotate(C[1], 1); block[3] ^= C[4] ^ astaroth_rotate(C[1], 1);
        block[4] ^= C[4] ^ astaroth_rotate(C[1], 1);
        block[5] ^= C[0] ^ astaroth_rotate(C[2], 1); block[6] ^= C[0] ^ astaroth_rotate(C[2], 1);
        block[7] ^= C[0] ^ astaroth_rotate(C[2], 1); block[8] ^= C[0] ^ astaroth_rotate(C[2], 1);
        block[9] ^= C[0] ^ astaroth_rotate(C[2], 1);
        block[10] ^= C[1] ^ astaroth_rotate(C[3], 1); block[11] ^= C[1] ^ astaroth_rotate(C[3], 1);
        block[12] ^= C[1] ^ astaroth_rotate(C[3], 1); block[13] ^= C[1] ^ astaroth_rotate(C[3], 1);
        block[14] ^= C[1] ^ astaroth_rotate(C[3], 1);
        block[15] ^= C[2] ^ astaroth_rotate(C[4], 1); block[16] ^= C[2] ^ astaroth_rotate(C[4], 1);
        block[17] ^= C[2] ^ astaroth_rotate(C[4], 1); block[18] ^= C[2] ^ astaroth_rotate(C[4], 1);
        block[19] ^= C[2] ^ astaroth_rotate(C[4], 1);
        block[20] ^= C[3] ^ astaroth_rotate(C[0], 1); block[21] ^= C[3] ^ astaroth_rotate(C[0], 1);
        block[22] ^= C[3] ^ astaroth_rotate(C[0], 1); block[23] ^= C[3] ^ astaroth_rotate(C[0], 1);
        block[24] ^= C[3] ^ astaroth_rotate(C[0], 1);

        temp1 = block[8];
        block[8] = astaroth_rotate(block[1], 36);
        block[1] = astaroth_rotate(block[15], 28);
        block[15] = astaroth_rotate(block[18], 21);
        block[18] = astaroth_rotate(block[13], 15);
        block[13] = astaroth_rotate(block[7], 10);
        block[7] = astaroth_rotate(block[11], 6);
        block[11] = astaroth_rotate(block[2], 3);
        block[2] = astaroth_rotate(block[5], 1);
        block[5] = astaroth_rotate(block[6], 44);
        block[6] = astaroth_rotate(block[21], 20);
        block[21] = astaroth_rotate(block[14], 61);
        block[14] = astaroth_rotate(block[22], 39);
        block[22] = astaroth_rotate(block[4], 18);
        block[4] = astaroth_rotate(block[10], 62);
        block[10] = astaroth_rotate(block[12], 43);
        block[12] = astaroth_rotate(block[17], 25);
        block[17] = astaroth_rotate(block[23], 8);
        block[23] = astaroth_rotate(block[19], 56);
        block[19] = astaroth_rotate(block[3], 41);
        block[3] = astaroth_rotate(block[20], 27);
        block[20] = astaroth_rotate(block[24], 14);
        block[24] = astaroth_rotate(block[9], 2);
        block[9] = astaroth_rotate(block[16], 55);
        block[16] = astaroth_rotate(temp1, 45);

        temp1 = block[0];
        temp2 = block[5];
        block[0] ^= (~block[5] & block[10]);
        block[5] ^= (~block[10] & block[15]);
        block[10] ^= (~block[15] & block[20]);
        block[15] ^= (~block[20] & temp1);
        block[20] ^= (~temp1 & temp2);

        temp1 = block[1];
        temp2 = block[6];
        block[1] ^= (~block[6] & block[11]);
        block[6] ^= (~block[11] & block[16]);
        block[11] ^= (~block[16] & block[21]);
        block[16] ^= (~block[21] & temp1);
        block[21] ^= (~temp1 & temp2);

        temp1 = block[2];
        temp2 = block[7];
        block[2] ^= (~block[7] & block[12]);
        block[7] ^= (~block[12] & block[17]);
        block[12] ^= (~block[17] & block[22]);
        block[17] ^= (~block[22] & temp1);
        block[22] ^= (~temp1 & temp2);

        temp1 = block[3];
        temp2 = block[8];
        block[3] ^= (~block[8] & block[13]);
        block[8] ^= (~block[13] & block[18]);
        block[13] ^= (~block[18] & block[23]);
        block[18] ^= (~block[23] & temp1);
        block[23] ^= (~temp1 & temp2);

        temp1 = block[4];
        temp2 = block[9];
        block[4] ^= (~block[9] & block[14]);
        block[9] ^= (~block[14] & block[19]);
        block[14] ^= (~block[19] & block[24]);
        block[19] ^= (~block[24] & temp1);
        block[24] ^= (~temp1 & temp2);

        block[0] ^= INFERNAL_IOTA_CONSTANTS[t];
    }
}

// Ритуал вычисления адреса кошелька под взором Аамона (GPU)
__device__ InfernalAddress aamon_calculate_address(Infernal256 x, Infernal256 y) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

    block[0] = astaroth_swap_endianness(((uint64_t)x.a << 32) | x.b);
    block[5] = astaroth_swap_endianness(((uint64_t)x.c << 32) | x.d);
    block[10] = astaroth_swap_endianness(((uint64_t)x.e << 32) | x.f);
    block[15] = astaroth_swap_endianness(((uint64_t)x.g << 32) | x.h);
    block[20] = astaroth_swap_endianness(((uint64_t)y.a << 32) | y.b);
    block[1] = astaroth_swap_endianness(((uint64_t)y.c << 32) | y.d);
    block[6] = astaroth_swap_endianness(((uint64_t)y.e << 32) | y.f);
    block[11] = astaroth_swap_endianness(((uint64_t)y.g << 32) | y.h);
    block[16] = (1ULL << 0);
    block[8] = 0x8000000000000000;

    beelzebub_block_permute(block);

    uint64_t b = astaroth_swap_endianness(block[5]);
    uint64_t c = astaroth_swap_endianness(block[10]);
    uint64_t d = astaroth_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса кошелька под взором Аамона (CPU)
__host__ InfernalAddress aamon_calculate_address_cpu(Infernal256 x, Infernal256 y) {
    uint64_t block[25] = {0};

    block[0] = mammon_swap_endianness(((uint64_t)x.a << 32) | x.b);
    block[5] = mammon_swap_endianness(((uint64_t)x.c << 32) | x.d);
    block[10] = mammon_swap_endianness(((uint64_t)x.e << 32) | x.f);
    block[15] = mammon_swap_endianness(((uint64_t)x.g << 32) | x.h);
    block[20] = mammon_swap_endianness(((uint64_t)y.a << 32) | y.b);
    block[1] = mammon_swap_endianness(((uint64_t)y.c << 32) | y.d);
    block[6] = mammon_swap_endianness(((uint64_t)y.e << 32) | y.f);
    block[11] = mammon_swap_endianness(((uint64_t)y.g << 32) | y.h);
    block[16] = (1ULL << 0);
    block[8] = 0x8000000000000000;

    astaroth_block_permute(block);

    uint64_t b = mammon_swap_endianness(block[5]);
    uint64_t c = mammon_swap_endianness(block[10]);
    uint64_t d = mammon_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта (GPU)
__device__ InfernalAddress aamon_calculate_contract_address(InfernalAddress a, uint8_t nonce = 0x80) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

    block[0] = astaroth_swap_endianness((0xD694ULL << 48) | ((uint64_t)a.a << 16) | (a.b >> 16));
    block[5] = astaroth_swap_endianness(((uint64_t)a.b << 48) | ((uint64_t)a.c << 16) | (a.d >> 16));
    block[10] = astaroth_swap_endianness(((uint64_t)a.d << 48) | ((uint64_t)a.e << 16) | ((uint64_t)nonce << 8) | 1);
    block[8] = 0x8000000000000000;

    beelzebub_block_permute(block);

    uint64_t b = astaroth_swap_endianness(block[5]);
    uint64_t c = astaroth_swap_endianness(block[10]);
    uint64_t d = astaroth_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта (CPU)
__host__ InfernalAddress aamon_calculate_contract_address_cpu(InfernalAddress a, uint8_t nonce = 0x80) {
    uint64_t block[25] = {0};

    block[0] = mammon_swap_endianness((0xD694ULL << 48) | ((uint64_t)a.a << 16) | (a.b >> 16));
    block[5] = mammon_swap_endianness(((uint64_t)a.b << 48) | ((uint64_t)a.c << 16) | (a.d >> 16));
    block[10] = mammon_swap_endianness(((uint64_t)a.d << 48) | ((uint64_t)a.e << 16) | ((uint64_t)nonce << 8) | 1);
    block[8] = 0x8000000000000000;

    astaroth_block_permute(block);

    uint64_t b = mammon_swap_endianness(block[5]);
    uint64_t c = mammon_swap_endianness(block[10]);
    uint64_t d = mammon_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта через CREATE2 (GPU)
__device__ InfernalAddress aamon_calculate_contract_address2(InfernalAddress a, Infernal256 salt, Infernal256 bytecode) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

    block[0] = astaroth_swap_endianness((0xFFULL << 56) | ((uint64_t)a.a << 24) | (a.b >> 8));
    block[5] = astaroth_swap_endianness(((uint64_t)a.b << 56) | ((uint64_t)a.c << 24) | (a.d >> 8));
    block[10] = astaroth_swap_endianness(((uint64_t)a.d << 56) | ((uint64_t)a.e << 24) | (salt.a >> 8));
    block[15] = astaroth_swap_endianness(((uint64_t)salt.a << 56) | ((uint64_t)salt.b << 24) | (salt.c >> 8));
    block[20] = astaroth_swap_endianness(((uint64_t)salt.c << 56) | ((uint64_t)salt.d << 24) | (salt.e >> 8));
    block[1] = astaroth_swap_endianness(((uint64_t)salt.e << 56) | ((uint64_t)salt.f << 24) | (salt.g >> 8));
    block[6] = astaroth_swap_endianness(((uint64_t)salt.g << 56) | ((uint64_t)salt.h << 24) | (bytecode.a >> 8));
    block[11] = astaroth_swap_endianness(((uint64_t)bytecode.a << 56) | ((uint64_t)bytecode.b << 24) | (bytecode.c >> 8));
    block[16] = astaroth_swap_endianness(((uint64_t)bytecode.c << 56) | ((uint64_t)bytecode.d << 24) | (bytecode.e >> 8));
    block[21] = astaroth_swap_endianness(((uint64_t)bytecode.e << 56) | ((uint64_t)bytecode.f << 24) | (bytecode.g >> 8));
    block[2] = astaroth_swap_endianness(((uint64_t)bytecode.g << 56) | ((uint64_t)bytecode.h << 24) | (1 << 16));
    block[8] = 0x8000000000000000;

    beelzebub_block_permute(block);

    uint64_t b = astaroth_swap_endianness(block[5]);
    uint64_t c = astaroth_swap_endianness(block[10]);
    uint64_t d = astaroth_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта через CREATE2 (CPU)
__host__ InfernalAddress aamon_calculate_contract_address2_cpu(InfernalAddress a, Infernal256 salt, Infernal256 bytecode) {
    uint64_t block[25] = {0};

    block[0] = mammon_swap_endianness((0xFFULL << 56) | ((uint64_t)a.a << 24) | (a.b >> 8));
    block[5] = mammon_swap_endianness(((uint64_t)a.b << 56) | ((uint64_t)a.c << 24) | (a.d >> 8));
    block[10] = mammon_swap_endianness(((uint64_t)a.d << 56) | ((uint64_t)a.e << 24) | (salt.a >> 8));
    block[15] = mammon_swap_endianness(((uint64_t)salt.a << 56) | ((uint64_t)salt.b << 24) | (salt.c >> 8));
    block[20] = mammon_swap_endianness(((uint64_t)salt.c << 56) | ((uint64_t)salt.d << 24) | (salt.e >> 8));
    block[1] = mammon_swap_endianness(((uint64_t)salt.e << 56) | ((uint64_t)salt.f << 24) | (salt.g >> 8));
    block[6] = mammon_swap_endianness(((uint64_t)salt.g << 56) | ((uint64_t)salt.h << 24) | (bytecode.a >> 8));
    block[11] = mammon_swap_endianness(((uint64_t)bytecode.a << 56) | ((uint64_t)bytecode.b << 24) | (bytecode.c >> 8));
    block[16] = mammon_swap_endianness(((uint64_t)bytecode.c << 56) | ((uint64_t)bytecode.d << 24) | (bytecode.e >> 8));
    block[21] = mammon_swap_endianness(((uint64_t)bytecode.e << 56) | ((uint64_t)bytecode.f << 24) | (bytecode.g >> 8));
    block[2] = mammon_swap_endianness(((uint64_t)bytecode.g << 56) | ((uint64_t)bytecode.h << 24) | (1 << 16));
    block[8] = 0x8000000000000000;

    astaroth_block_permute(block);

    uint64_t b = mammon_swap_endianness(block[5]);
    uint64_t c = mammon_swap_endianness(block[10]);
    uint64_t d = mammon_swap_endianness(block[15]);

    return {(uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления соли для CREATE3 (GPU)
__device__ Infernal256 aamon_calculate_create3_salt(InfernalAddress origin, Infernal256 salt) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

    block[0] = astaroth_swap_endianness(((uint64_t)origin.a << 32) | (uint64_t)origin.b);
    block[5] = astaroth_swap_endianness(((uint64_t)origin.c << 32) | (uint64_t)origin.d);
    block[10] = astaroth_swap_endianness(((uint64_t)origin.e << 32) | (uint64_t)salt.a);
    block[15] = astaroth_swap_endianness(((uint64_t)salt.b << 32) | (uint64_t)salt.c);
    block[20] = astaroth_swap_endianness(((uint64_t)salt.d << 32) | (uint64_t)salt.e);
    block[1] = astaroth_swap_endianness(((uint64_t)salt.f << 32) | (uint64_t)salt.g);
    block[6] = astaroth_swap_endianness(((uint64_t)salt.h << 32) | (1ULL << 24));
    block[8] = 0x8000000000000000;

    beelzebub_block_permute(block);

    uint64_t a = astaroth_swap_endianness(block[0]);
    uint64_t b = astaroth_swap_endianness(block[5]);
    uint64_t c = astaroth_swap_endianness(block[10]);
    uint64_t d = astaroth_swap_endianness(block[15]);

    return {(uint32_t)(a >> 32), (uint32_t)(a & 0xFFFFFFFF), (uint32_t)(b >> 32), (uint32_t)(b & 0xFFFFFFFF),
            (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления соли для CREATE3 (CPU)
__host__ Infernal256 aamon_calculate_create3_salt_cpu(InfernalAddress origin, Infernal256 salt) {
    uint64_t block[25] = {0};

    block[0] = mammon_swap_endianness(((uint64_t)origin.a << 32) | (uint64_t)origin.b);
    block[5] = mammon_swap_endianness(((uint64_t)origin.c << 32) | (uint64_t)origin.d);
    block[10] = mammon_swap_endianness(((uint64_t)origin.e << 32) | (uint64_t)salt.a);
    block[15] = mammon_swap_endianness(((uint64_t)salt.b << 32) | (uint64_t)salt.c);
    block[20] = mammon_swap_endianness(((uint64_t)salt.d << 32) | (uint64_t)salt.e);
    block[1] = mammon_swap_endianness(((uint64_t)salt.f << 32) | (uint64_t)salt.g);
    block[6] = mammon_swap_endianness(((uint64_t)salt.h << 32) | (1ULL << 24));
    block[8] = 0x8000000000000000;

    astaroth_block_permute(block);

    uint64_t a = mammon_swap_endianness(block[0]);
    uint64_t b = mammon_swap_endianness(block[5]);
    uint64_t c = mammon_swap_endianness(block[10]);
    uint64_t d = mammon_swap_endianness(block[15]);

    return {(uint32_t)(a >> 32), (uint32_t)(a & 0xFFFFFFFF), (uint32_t)(b >> 32), (uint32_t)(b & 0xFFFFFFFF),
            (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

#endif // KECCAK_H