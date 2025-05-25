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

#ifndef CPU_KECCAK_H
#define CPU_KECCAK_H

#include <cinttypes>
#include <cstring>
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

// Константы адского ритуала
#ifndef INFERNAL_IOTA_CONSTANTS_DEFINED
#define INFERNAL_IOTA_CONSTANTS_DEFINED
__constant__ uint64_t INFERNAL_IOTA_CONSTANTS[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x0000000000000080, 0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};
#endif

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

// Ритуал полного Keccak-хэширования
Infernal256 aamon_full_keccak(uint8_t* data, size_t len) {
    uint64_t block[25] = {0};
    size_t rate = 136; // 1088 бит / 8 = 136 байт
    size_t pos = 0;

    // Абсорбция
    while (pos + rate <= len) {
        for (size_t i = 0; i < rate / 8; i++) {
            block[i] ^= mammon_swap_endianness(*(uint64_t*)(data + pos + i * 8));
        }
        astaroth_block_permute(block);
        pos += rate;
    }

    // Последний блок
    size_t remaining = len - pos;
    uint8_t padded[136] = {0};
    memcpy(padded, data + pos, remaining);
    padded[remaining] = 0x06; // Паддинг для Keccak-256
    padded[rate - 1] |= 0x80;

    for (size_t i = 0; i < rate / 8; i++) {
        block[i] ^= mammon_swap_endianness(*(uint64_t*)(padded + i * 8));
    }
    astaroth_block_permute(block);

    // Извлечение результата
    uint64_t a = mammon_swap_endianness(block[0]);
    uint64_t b = mammon_swap_endianness(block[1]);
    uint64_t c = mammon_swap_endianness(block[2]);
    uint64_t d = mammon_swap_endianness(block[3]);

    return {
        (uint32_t)(a >> 32), (uint32_t)(a & 0xFFFFFFFF),
        (uint32_t)(b >> 32), (uint32_t)(b & 0xFFFFFFFF),
        (uint32_t)(c >> 32), (uint32_t)(c & 0xFFFFFFFF),
        (uint32_t)(d >> 32), (uint32_t)(d & 0xFFFFFFFF)
    };
}

#endif // CPU_KECCAK_H