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
  ██████╗ ███████╗ ██████╗ ██████╗  █████╗ ██╗  ██╗
 ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██╔══██╗██║ ██╔╝
 ██║   ██║█████╗  ██║   ██║██████╔╝███████║█████╔╝
 ██║   ██║██╔══╝  ██║   ██║██╔══██╗██╔══██║██╔═██╗
 ╚██████╔╝███████╗╚██████╔╝██║  ██║██║  ██║██║  ██╗
  ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
     ✠ SUMMONING THE HASHES OF THE DAMNED ✠
*/

// Ритуал вращения битов под взором Маммона
uint64_t mammon_rotate(uint64_t x, int n) {
    return (x << n) | (x >> (64 - n));
}

// Ритуал смены порядка байтов
uint64_t mammon_swap_endianness(uint64_t x) {
    return ((x & 0x00000000000000FF) << 56) | ((x & 0x000000000000FF00) << 40) |
           ((x & 0x0000000000FF0000) << 24) | ((x & 0x00000000FF000000) << 8) |
           ((x & 0x000000FF00000000) >> 8) | ((x & 0x0000FF0000000000) >> 24) |
           ((x & 0x00FF000000000000) >> 40) | ((x & 0xFF00000000000000) >> 56);
}

// Константы адского ритуала
const uint64_t INFERNAL_IOTA_CONSTANTS[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080, 0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

// Ритуал перестановки блока под взором Астарота
void astaroth_block_permute(uint64_t *block) {
    uint64_t C[5];
    uint64_t D;
    uint64_t temp1, temp2;

    for (int t = 0; t < 24; t++) {
        C[0] = block[0] ^ block[1] ^ block[2] ^ block[3] ^ block[4];
        C[1] = block[5] ^ block[6] ^ block[7] ^ block[8] ^ block[9];
        C[2] = block[10] ^ block[11] ^ block[12] ^ block[13] ^ block[14];
        C[3] = block[15] ^ block[16] ^ block[17] ^ block[18] ^ block[19];
        C[4] = block[20] ^ block[21] ^ block[22] ^ block[23] ^ block[24];

        D = C[4] ^ mammon_rotate(C[1], 1);
        block[0] ^= D; block[1] ^= D; block[2] ^= D; block[3] ^= D; block[4] ^= D;
        D = C[0] ^ mammon_rotate(C[2], 1);
        block[5] ^= D; block[6] ^= D; block[7] ^= D; block[8] ^= D; block[9] ^= D;
        D = C[1] ^ mammon_rotate(C[3], 1);
        block[10] ^= D; block[11] ^= D; block[12] ^= D; block[13] ^= D; block[14] ^= D;
        D = C[2] ^ mammon_rotate(C[4], 1);
        block[15] ^= D; block[16] ^= D; block[17] ^= D; block[18] ^= D; block[19] ^= D;
        D = C[3] ^ mammon_rotate(C[0], 1);
        block[20] ^= D; block[21] ^= D; block[22] ^= D; block[23] ^= D; block[24] ^= D;

        temp1 = block[8];
        block[8] = mammon_rotate(block[1], 36);
        block[1] = mammon_rotate(block[15], 28);
        block[15] = mammon_rotate(block[18], 21);
        block[18] = mammon_rotate(block[13], 15);
        block[13] = mammon_rotate(block[7], 10);
        block[7] = mammon_rotate(block[11], 6);
        block[11] = mammon_rotate(block[2], 3);
        block[2] = mammon_rotate(block[5], 1);
        block[5] = mammon_rotate(block[6], 44);
        block[6] = mammon_rotate(block[21], 20);
        block[21] = mammon_rotate(block[14], 61);
        block[14] = mammon_rotate(block[22], 39);
        block[22] = mammon_rotate(block[4], 18);
        block[4] = mammon_rotate(block[10], 62);
        block[10] = mammon_rotate(block[12], 43);
        block[12] = mammon_rotate(block[17], 25);
        block[17] = mammon_rotate(block[23], 8);
        block[23] = mammon_rotate(block[19], 56);
        block[19] = mammon_rotate(block[3], 41);
        block[3] = mammon_rotate(block[20], 27);
        block[20] = mammon_rotate(block[24], 14);
        block[24] = mammon_rotate(block[9], 2);
        block[9] = mammon_rotate(block[16], 55);
        block[16] = mammon_rotate(temp1, 45);

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

// Ритуал вычисления адреса кошелька
InfernalAddress aamon_calculate_address(Infernal256 x, Infernal256 y) {
    uint64_t block[50];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

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

// Ритуал вычисления адреса контракта
InfernalAddress aamon_calculate_contract_address(InfernalAddress a, uint8_t nonce = 0x80) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

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

// Ритуал полного Keccak-хеширования
Infernal256 aamon_full_keccak(uint8_t* bytes, uint32_t num_bytes) {
    int input_blocks = (num_bytes + 136 - 1 + 1) / 136;
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

    #define fetch(n) ((i * 136 + n < num_bytes) ? bytes[i * 136 + n] : ((i * 136 + n == num_bytes) ? 1 : 0))
    #define block_xor(block_num, n) block[block_num] ^= mammon_swap_endianness(((uint64_t)fetch(n * 8 + 0) << 56) | ((uint64_t)fetch(n * 8 + 1) << 48) | ((uint64_t)fetch(n * 8 + 2) << 40) | ((uint64_t)fetch(n * 8 + 3) << 32) | ((uint64_t)fetch(n * 8 + 4) << 24) | ((uint64_t)fetch(n * 8 + 5) << 16) | ((uint64_t)fetch(n * 8 + 6) << 8) | ((uint64_t)fetch(n * 8 + 7)))
    for (int i = 0; i < input_blocks; i++) {
        block_xor(0, 0);
        block_xor(5, 1);
        block_xor(10, 2);
        block_xor(15, 3);
        block_xor(20, 4);
        block_xor(1, 5);
        block_xor(6, 6);
        block_xor(11, 7);
        block_xor(16, 8);
        block_xor(21, 9);
        block_xor(2, 10);
        block_xor(7, 11);
        block_xor(12, 12);
        block_xor(17, 13);
        block_xor(22, 14);
        block_xor(3, 15);
        block_xor(8, 16);

        if (i == input_blocks - 1) {
            block[8] ^= 0x8000000000000000;
        }

        astaroth_block_permute(block);
    }
    #undef fetch
    #undef block_xor

    uint64_t a = mammon_swap_endianness(block[0]);
    uint64_t b = mammon_swap_endianness(block[5]);
    uint64_t c = mammon_swap_endianness(block[10]);
    uint64_t d = mammon_swap_endianness(block[15]);

    return {(uint32_t)(a >> 32), (uint32_t)(a & 0xFFFFFFFF), (uint32_t)(b >> 32), (uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}

// Ритуал вычисления адреса контракта через CREATE2
InfernalAddress aamon_calculate_contract_address2(InfernalAddress a, Infernal256 salt, Infernal256 bytecode) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

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

// Ритуал вычисления соли для CREATE3
Infernal256 aamon_calculate_create3_salt(InfernalAddress origin, Infernal256 salt) {
    uint64_t block[25];
    for (int i = 0; i < 25; i++) {
        block[i] = 0;
    }

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

    return {(uint32_t)(a >> 32), (uint32_t)(a & 0xFFFFFFFF), (uint32_t)(b >> 32), (uint32_t)(b & 0xFFFFFFFF), (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF), (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)};
}