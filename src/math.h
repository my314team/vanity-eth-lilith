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
  ██████╗ ██████╗ ██╗   ██╗███╗   ███╗ █████╗ ████████╗██╗  ██╗
 ██╔════╝ ██╔══██╗██║   ██║████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
 ██║  ███╗██████╔╝██║   ██║██╔████╔██║███████║   ██║   ███████║
 ██║   ██║ ██╔══██╗██║   ██║██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
 ╚██████╔╝ ██║  ██║╚██████╔╝██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
  ╚═════╝  ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
     ✠ SUMMONING THE ARITHMETIC OF THE ETERNAL DAMNED ✠
*/

#define INFERNAL_P Infernal256{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFC2F}

// Ритуал сложения 256-битных чисел с переносом под взором Маммона
__device__ Infernal256c mammon_add_256_with_c(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256c abyssal_result;

    uint32_t infernal_carry = 0;
    asm(
        "add.cc.u32 %0, %9, %17;    \n\t"
        "addc.cc.u32 %1, %10, %18;  \n\t"
        "addc.cc.u32 %2, %11, %19;  \n\t"
        "addc.cc.u32 %3, %12, %20;  \n\t"
        "addc.cc.u32 %4, %13, %21;  \n\t"
        "addc.cc.u32 %5, %14, %22;  \n\t"
        "addc.cc.u32 %6, %15, %23;  \n\t"
        "addc.cc.u32 %7, %16, %24;  \n\t"
        "addc.u32 %8, 0x0, 0x0;     \n\t"
        : "=r"(abyssal_result.h), "=r"(abyssal_result.g), "=r"(abyssal_result.f), "=r"(abyssal_result.e), "=r"(abyssal_result.d), "=r"(abyssal_result.c), "=r"(abyssal_result.b), "=r"(abyssal_result.a), "=r"(infernal_carry)
        : "r"(infernal_x.h), "r"(infernal_x.g), "r"(infernal_x.f), "r"(infernal_x.e), "r"(infernal_x.d), "r"(infernal_x.c), "r"(infernal_x.b), "r"(infernal_x.a), "r"(infernal_y.h), "r"(infernal_y.g), "r"(infernal_y.f), "r"(infernal_y.e), "r"(infernal_y.d), "r"(infernal_y.c), "r"(infernal_y.b), "r"(infernal_y.a)
    );

    abyssal_result.carry = (bool)infernal_carry;

    return abyssal_result;
}

// Ритуал вычитания 256-битных чисел под взором Маммона
__device__ Infernal256 mammon_sub_256(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result;

    asm(
        "sub.cc.u32 %0, %8, %16;    \n\t"
        "subc.cc.u32 %1, %9, %17;   \n\t"
        "subc.cc.u32 %2, %10, %18;  \n\t"
        "subc.cc.u32 %3, %11, %19;  \n\t"
        "subc.cc.u32 %4, %12, %20;  \n\t"
        "subc.cc.u32 %5, %13, %21;  \n\t"
        "subc.cc.u32 %6, %14, %22;  \n\t"
        "subc.u32 %7, %15, %23;     \n\t"
        : "=r"(abyssal_result.h), "=r"(abyssal_result.g), "=r"(abyssal_result.f), "=r"(abyssal_result.e), "=r"(abyssal_result.d), "=r"(abyssal_result.c), "=r"(abyssal_result.b), "=r"(abyssal_result.a)
        : "r"(infernal_x.h), "r"(infernal_x.g), "r"(infernal_x.f), "r"(infernal_x.e), "r"(infernal_x.d), "r"(infernal_x.c), "r"(infernal_x.b), "r"(infernal_x.a), "r"(infernal_y.h), "r"(infernal_y.g), "r"(infernal_y.f), "r"(infernal_y.e), "r"(infernal_y.d), "r"(infernal_y.c), "r"(infernal_y.b), "r"(infernal_y.a)
    );

    return abyssal_result;
}

// Ритуал вычитания 256-битных чисел по модулю P под взором Маммона
__device__ Infernal256 mammon_sub_256_mod_p(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result;

    asm(
        "{\n\t"
        ".reg .u32 t;                       \n\t"
        ".reg .pred p;                      \n\t"
        "sub.cc.u32 %0, %8, %16;            \n\t"
        "subc.cc.u32 %1, %9, %17;           \n\t"
        "subc.cc.u32 %2, %10, %18;          \n\t"
        "subc.cc.u32 %3, %11, %19;          \n\t"
        "subc.cc.u32 %4, %12, %20;          \n\t"
        "subc.cc.u32 %5, %13, %21;          \n\t"
        "subc.cc.u32 %6, %14, %22;          \n\t"
        "subc.cc.u32 %7, %15, %23;          \n\t"
        "subc.u32 t, 0x0, 0x0;              \n\t"
        "setp.ne.u32 p, t, 0x0;             \n\t"
        "@p add.cc.u32 %0, %0, 0xFFFFFC2F;  \n\t"
        "@p addc.cc.u32 %1, %1, 0xFFFFFFFE; \n\t"
        "@p addc.cc.u32 %2, %2, 0xFFFFFFFF; \n\t"
        "@p addc.cc.u32 %3, %3, 0xFFFFFFFF; \n\t"
        "@p addc.cc.u32 %4, %4, 0xFFFFFFFF; \n\t"
        "@p addc.cc.u32 %5, %5, 0xFFFFFFFF; \n\t"
        "@p addc.cc.u32 %6, %6, 0xFFFFFFFF; \n\t"
        "@p addc.u32 %7, %7, 0xFFFFFFFF;    \n\t"
        "}"
        : "=r"(abyssal_result.h), "=r"(abyssal_result.g), "=r"(abyssal_result.f), "=r"(abyssal_result.e), "=r"(abyssal_result.d), "=r"(abyssal_result.c), "=r"(abyssal_result.b), "=r"(abyssal_result.a)
        : "r"(infernal_x.h), "r"(infernal_x.g), "r"(infernal_x.f), "r"(infernal_x.e), "r"(infernal_x.d), "r"(infernal_x.c), "r"(infernal_x.b), "r"(infernal_x.a), "r"(infernal_y.h), "r"(infernal_y.g), "r"(infernal_y.f), "r"(infernal_y.e), "r"(infernal_y.d), "r"(infernal_y.c), "r"(infernal_y.b), "r"(infernal_y.a)
    );

    return abyssal_result;
}

// Ритуал умножения 256-битных чисел по модулю P под взором Астарота
__device__ Infernal256 astaroth_mul_256_mod_p(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result{0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t infernal_carry = 0;

    asm(
        "{\n\t"
        ".reg .u32 a;                       \n\t"
        ".reg .u32 b;                       \n\t"
        ".reg .u32 c;                       \n\t"
        ".reg .u32 d;                       \n\t"
        ".reg .u32 e;                       \n\t"
        ".reg .u32 f;                       \n\t"
        ".reg .u32 g;                       \n\t"
        ".reg .u32 h;                       \n\t"
        ".reg .u32 i;                       \n\t"
        ".reg .u32 j;                       \n\t"
        ".reg .u32 k;                       \n\t"
        ".reg .u32 l;                       \n\t"
        ".reg .u32 m;                       \n\t"
        ".reg .u32 n;                       \n\t"
        ".reg .u32 o;                       \n\t"
        ".reg .u32 p;                       \n\t"
        ".reg .u32 t1;                      \n\t"
        "mul.lo.u32 p, %9, %17;             \n\t"
        "mul.hi.u32 t1, %9, %17;            \n\t"
        "mad.lo.cc.u32 o, %10, %17, t1;     \n\t"
        "mul.hi.u32 t1, %10, %17;           \n\t"
        "madc.lo.cc.u32 n, %11, %17, t1;    \n\t"
        "mul.hi.u32 t1, %11, %17;           \n\t"
        "madc.lo.cc.u32 m, %12, %17, t1;    \n\t"
        "mul.hi.u32 t1, %12, %17;           \n\t"
        "madc.lo.cc.u32 l, %13, %17, t1;    \n\t"
        "mul.hi.u32 t1, %13, %17;           \n\t"
        "madc.lo.cc.u32 k, %14, %17, t1;    \n\t"
        "mul.hi.u32 t1, %14, %17;           \n\t"
        "madc.lo.cc.u32 j, %15, %17, t1;    \n\t"
        "mul.hi.u32 t1, %15, %17;           \n\t"
        "madc.lo.cc.u32 i, %16, %17, t1;    \n\t"
        "madc.hi.u32 h, %16, %17, 0x0;      \n\t"
        "mad.lo.cc.u32 o, %9, %18, o;       \n\t"
        "madc.lo.cc.u32 n, %10, %18, n;     \n\t"
        "madc.lo.cc.u32 m, %11, %18, m;     \n\t"
        "madc.lo.cc.u32 l, %12, %18, l;     \n\t"
        "madc.lo.cc.u32 k, %13, %18, k;     \n\t"
        "madc.lo.cc.u32 j, %14, %18, j;     \n\t"
        "madc.lo.cc.u32 i, %15, %18, i;     \n\t"
        "madc.lo.cc.u32 h, %16, %18, h;     \n\t"
        "addc.u32 g, 0x0, 0x0;              \n\t"
        "mad.hi.cc.u32 n, %9, %18, n;       \n\t"
        "madc.hi.cc.u32 m, %10, %18, m;     \n\t"
        "madc.hi.cc.u32 l, %11, %18, l;     \n\t"
        "madc.hi.cc.u32 k, %12, %18, k;     \n\t"
        "madc.hi.cc.u32 j, %13, %18, j;     \n\t"
        "madc.hi.cc.u32 i, %14, %18, i;     \n\t"
        "madc.hi.cc.u32 h, %15, %18, h;     \n\t"
        "madc.hi.cc.u32 g, %16, %18, g;     \n\t"
        "addc.u32 f, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 n, %9, %19, n;       \n\t"
        "madc.lo.cc.u32 m, %10, %19, m;     \n\t"
        "madc.lo.cc.u32 l, %11, %19, l;     \n\t"
        "madc.lo.cc.u32 k, %12, %19, k;     \n\t"
        "madc.lo.cc.u32 j, %13, %19, j;     \n\t"
        "madc.lo.cc.u32 i, %14, %19, i;     \n\t"
        "madc.lo.cc.u32 h, %15, %19, h;     \n\t"
        "madc.lo.cc.u32 g, %16, %19, g;     \n\t"
        "addc.u32 f, f, 0x0;                \n\t"
        "mad.hi.cc.u32 m, %9, %19, m;       \n\t"
        "madc.hi.cc.u32 l, %10, %19, l;     \n\t"
        "madc.hi.cc.u32 k, %11, %19, k;     \n\t"
        "madc.hi.cc.u32 j, %12, %19, j;     \n\t"
        "madc.hi.cc.u32 i, %13, %19, i;     \n\t"
        "madc.hi.cc.u32 h, %14, %19, h;     \n\t"
        "madc.hi.cc.u32 g, %15, %19, g;     \n\t"
        "madc.hi.cc.u32 f, %16, %19, f;     \n\t"
        "addc.u32 e, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 m, %9, %20, m;       \n\t"
        "madc.lo.cc.u32 l, %10, %20, l;     \n\t"
        "madc.lo.cc.u32 k, %11, %20, k;     \n\t"
        "madc.lo.cc.u32 j, %12, %20, j;     \n\t"
        "madc.lo.cc.u32 i, %13, %20, i;     \n\t"
        "madc.lo.cc.u32 h, %14, %20, h;     \n\t"
        "madc.lo.cc.u32 g, %15, %20, g;     \n\t"
        "madc.lo.cc.u32 f, %16, %20, f;     \n\t"
        "addc.u32 e, e, 0x0;                \n\t"
        "mad.hi.cc.u32 l, %9, %20, l;       \n\t"
        "madc.hi.cc.u32 k, %10, %20, k;     \n\t"
        "madc.hi.cc.u32 j, %11, %20, j;     \n\t"
        "madc.hi.cc.u32 i, %12, %20, i;     \n\t"
        "madc.hi.cc.u32 h, %13, %20, h;     \n\t"
        "madc.hi.cc.u32 g, %14, %20, g;     \n\t"
        "madc.hi.cc.u32 f, %15, %20, f;     \n\t"
        "madc.hi.cc.u32 e, %16, %20, e;     \n\t"
        "addc.u32 d, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 l, %9, %21, l;       \n\t"
        "madc.lo.cc.u32 k, %10, %21, k;     \n\t"
        "madc.lo.cc.u32 j, %11, %21, j;     \n\t"
        "madc.lo.cc.u32 i, %12, %21, i;     \n\t"
        "madc.lo.cc.u32 h, %13, %21, h;     \n\t"
        "madc.lo.cc.u32 g, %14, %21, g;     \n\t"
        "madc.lo.cc.u32 f, %15, %21, f;     \n\t"
        "madc.lo.cc.u32 e, %16, %21, e;     \n\t"
        "addc.u32 d, d, 0x0;                \n\t"
        "mad.hi.cc.u32 k, %9, %21, k;       \n\t"
        "madc.hi.cc.u32 j, %10, %21, j;     \n\t"
        "madc.hi.cc.u32 i, %11, %21, i;     \n\t"
        "madc.hi.cc.u32 h, %12, %21, h;     \n\t"
        "madc.hi.cc.u32 g, %13, %21, g;     \n\t"
        "madc.hi.cc.u32 f, %14, %21, f;     \n\t"
        "madc.hi.cc.u32 e, %15, %21, e;     \n\t"
        "madc.hi.cc.u32 d, %16, %21, d;     \n\t"
        "addc.u32 c, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 k, %9, %22, k;       \n\t"
        "madc.lo.cc.u32 j, %10, %22, j;     \n\t"
        "madc.lo.cc.u32 i, %11, %22, i;     \n\t"
        "madc.lo.cc.u32 h, %12, %22, h;     \n\t"
        "madc.lo.cc.u32 g, %13, %22, g;     \n\t"
        "madc.lo.cc.u32 f, %14, %22, f;     \n\t"
        "madc.lo.cc.u32 e, %15, %22, e;     \n\t"
        "madc.lo.cc.u32 d, %16, %22, d;     \n\t"
        "addc.u32 c, c, 0x0;                \n\t"
        "mad.hi.cc.u32 j, %9, %22, j;       \n\t"
        "madc.hi.cc.u32 i, %10, %22, i;     \n\t"
        "madc.hi.cc.u32 h, %11, %22, h;     \n\t"
        "madc.hi.cc.u32 g, %12, %22, g;     \n\t"
        "madc.hi.cc.u32 f, %13, %22, f;     \n\t"
        "madc.hi.cc.u32 e, %14, %22, e;     \n\t"
        "madc.hi.cc.u32 d, %15, %22, d;     \n\t"
        "madc.hi.cc.u32 c, %16, %22, c;     \n\t"
        "addc.u32 b, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 j, %9, %23, j;       \n\t"
        "madc.lo.cc.u32 i, %10, %23, i;     \n\t"
        "madc.lo.cc.u32 h, %11, %23, h;     \n\t"
        "madc.lo.cc.u32 g, %12, %23, g;     \n\t"
        "madc.lo.cc.u32 f, %13, %23, f;     \n\t"
        "madc.lo.cc.u32 e, %14, %23, e;     \n\t"
        "madc.lo.cc.u32 d, %15, %23, d;     \n\t"
        "madc.lo.cc.u32 c, %16, %23, c;     \n\t"
        "addc.u32 b, b, 0x0;                \n\t"
        "mad.hi.cc.u32 i, %9, %23, i;       \n\t"
        "madc.hi.cc.u32 h, %10, %23, h;     \n\t"
        "madc.hi.cc.u32 g, %11, %23, g;     \n\t"
        "madc.hi.cc.u32 f, %12, %23, f;     \n\t"
        "madc.hi.cc.u32 e, %13, %23, e;     \n\t"
        "madc.hi.cc.u32 d, %14, %23, d;     \n\t"
        "madc.hi.cc.u32 c, %15, %23, c;     \n\t"
        "madc.hi.cc.u32 b, %16, %23, b;     \n\t"
        "addc.u32 a, 0x0, 0x0;              \n\t"
        "mad.lo.cc.u32 i, %9, %24, i;       \n\t"
        "madc.lo.cc.u32 h, %10, %24, h;     \n\t"
        "madc.lo.cc.u32 g, %11, %24, g;     \n\t"
        "madc.lo.cc.u32 f, %12, %24, f;     \n\t"
        "madc.lo.cc.u32 e, %13, %24, e;     \n\t"
        "madc.lo.cc.u32 d, %14, %24, d;     \n\t"
        "madc.lo.cc.u32 c, %15, %24, c;     \n\t"
        "madc.lo.cc.u32 b, %16, %24, b;     \n\t"
        "addc.u32 a, a, 0x0;                \n\t"
        "mad.hi.cc.u32 h, %9, %24, h;       \n\t"
        "madc.hi.cc.u32 g, %10, %24, g;     \n\t"
        "madc.hi.cc.u32 f, %11, %24, f;     \n\t"
        "madc.hi.cc.u32 e, %12, %24, e;     \n\t"
        "madc.hi.cc.u32 d, %13, %24, d;     \n\t"
        "madc.hi.cc.u32 c, %14, %24, c;     \n\t"
        "madc.hi.cc.u32 b, %15, %24, b;     \n\t"
        "madc.hi.u32 a, %16, %24, a;        \n\t"
        ".reg.u32 ov;                       \n\t"
        "mul.lo.u32 %0, h, 0x3d1;           \n\t"
        "mul.hi.u32 t1, h, 0x3d1;           \n\t"
        "mad.lo.cc.u32 %1, g, 0x3d1, t1;    \n\t"
        "mul.hi.u32 t1, g, 0x3d1;           \n\t"
        "madc.lo.cc.u32 %2, f, 0x3d1, t1;   \n\t"
        "mul.hi.u32 t1, f, 0x3d1;           \n\t"
        "madc.lo.cc.u32 %3, e, 0x3d1, t1;   \n\t"
        "mul.hi.u32 t1, e, 0x3d1;           \n\t"
        "madc.lo.cc.u32 %4, d, 0x3d1, t1;   \n\t"
        "mul.hi.u32 t1, d, 0x3d1;           \n\t"
        "madc.lo.cc.u32 %5, c, 0x3d1, t1;   \n\t"
        "mul.hi.u32 t1, c, 0x3d1;           \n\t"
        "madc.lo.cc.u32 %6, b, 0x3d1, t1;   \n\t"
        "madc.hi.u32 %7, b, 0x3d1, 0x0;     \n\t"
        "add.cc.u32 %1, %1, h;              \n\t"
        "addc.cc.u32 %2, %2, g;             \n\t"
        "addc.cc.u32 %3, %3, f;             \n\t"
        "addc.cc.u32 %4, %4, e;             \n\t"
        "addc.cc.u32 %5, %5, d;             \n\t"
        "addc.cc.u32 %6, %6, c;             \n\t"
        "addc.cc.u32 %7, %7, b;             \n\t"
        "addc.u32 ov, 0x0, 0x0;             \n\t"
        ".reg .u32 n1;                      \n\t"
        ".reg .u32 n2;                      \n\t"
        ".reg .u32 n3;                      \n\t"
        "mul.lo.u32 n3, a, 0x3d1;           \n\t"
        "mad.hi.cc.u32 n2, a, 0x3d1, a;     \n\t"
        "addc.u32 n1, 0x0, 0x0;             \n\t"
        "add.cc.u32 %0, %0, n3;             \n\t"
        "addc.cc.u32 %1, %1, n2;            \n\t"
        "addc.cc.u32 %2, %2, n1;            \n\t"
        "addc.cc.u32 %3, %3, 0x0;           \n\t"
        "addc.cc.u32 %4, %4, 0x0;           \n\t"
        "addc.cc.u32 %5, %5, 0x0;           \n\t"
        "addc.cc.u32 %6, %6, 0x0;           \n\t"
        "madc.lo.cc.u32 %7, a, 0x3d1, %7;   \n\t"
        "madc.hi.u32 ov, a, 0x3d1, ov;      \n\t"
        "add.cc.u32 %0, %0, p;              \n\t"
        "addc.cc.u32 %1, %1, o;             \n\t"
        "addc.cc.u32 %2, %2, n;             \n\t"
        "addc.cc.u32 %3, %3, m;             \n\t"
        "addc.cc.u32 %4, %4, l;             \n\t"
        "addc.cc.u32 %5, %5, k;             \n\t"
        "addc.cc.u32 %6, %6, j;             \n\t"
        "addc.cc.u32 %7, %7, i;             \n\t"
        "addc.u32 ov, ov, 0x0;              \n\t"
        "mul.lo.u32 n2, ov, 0x3d1;          \n\t"
        "mad.hi.u32 n1, ov, 0x3d1, ov;      \n\t"
        "add.cc.u32 %0, %0, n2;             \n\t"
        "addc.cc.u32 %1, %1, n1;            \n\t"
        "addc.cc.u32 %2, %2, 0x0;           \n\t"
        "addc.cc.u32 %3, %3, 0x0;           \n\t"
        "addc.cc.u32 %4, %4, 0x0;           \n\t"
        "addc.cc.u32 %5, %5, 0x0;           \n\t"
        "addc.cc.u32 %6, %6, 0x0;           \n\t"
        "addc.cc.u32 %7, %7, 0x0;           \n\t"
        "addc.u32 %8, 0x0, 0x0;             \n\t"
        "}"
        : "+r"(abyssal_result.h), "+r"(abyssal_result.g), "+r"(abyssal_result.f), "+r"(abyssal_result.e), "+r"(abyssal_result.d), "+r"(abyssal_result.c), "+r"(abyssal_result.b), "+r"(abyssal_result.a), "=r"(infernal_carry)
        : "r"(infernal_x.h), "r"(infernal_x.g), "r"(infernal_x.f), "r"(infernal_x.e), "r"(infernal_x.d), "r"(infernal_x.c), "r"(infernal_x.b), "r"(infernal_x.a), "r"(infernal_y.h), "r"(infernal_y.g), "r"(infernal_y.f), "r"(infernal_y.e), "r"(infernal_y.d), "r"(infernal_y.c), "r"(infernal_y.b), "r"(infernal_y.a)
    );

    bool infernal_overflow = infernal_carry || belial_gte_infernal256(abyssal_result, INFERNAL_P);
    if (infernal_overflow) {
        abyssal_result = mammon_sub_256(abyssal_result, INFERNAL_P);
    }

    return abyssal_result;
}

// Ритуал сдвига вправо на 1 бит под взором Маммона
__device__ Infernal256 mammon_rshift1_256(Infernal256 infernal_x) {
    Infernal256 abyssal_result;
    abyssal_result.a =               (infernal_x.a >> 1);
    abyssal_result.b = (infernal_x.a << 31) | (infernal_x.b >> 1);
    abyssal_result.c = (infernal_x.b << 31) | (infernal_x.c >> 1);
    abyssal_result.d = (infernal_x.c << 31) | (infernal_x.d >> 1);
    abyssal_result.e = (infernal_x.d << 31) | (infernal_x.e >> 1);
    abyssal_result.f = (infernal_x.e << 31) | (infernal_x.f >> 1);
    abyssal_result.g = (infernal_x.f << 31) | (infernal_x.g >> 1);
    abyssal_result.h = (infernal_x.g << 31) | (infernal_x.h >> 1);
    return abyssal_result;
}

// Ритуал сдвига вправо на 1 бит с переносом под взором Маммона
__device__ Infernal256 mammon_rshift1_256c(Infernal256c infernal_x) {
    Infernal256 abyssal_result;
    abyssal_result.a = ((uint32_t)infernal_x.carry << 31) | (infernal_x.a >> 1);
    abyssal_result.b = (infernal_x.a << 31) | (infernal_x.b >> 1);
    abyssal_result.c = (infernal_x.b << 31) | (infernal_x.c >> 1);
    abyssal_result.d = (infernal_x.c << 31) | (infernal_x.d >> 1);
    abyssal_result.e = (infernal_x.d << 31) | (infernal_x.e >> 1);
    abyssal_result.f = (infernal_x.e << 31) | (infernal_x.f >> 1);
    abyssal_result.g = (infernal_x.f << 31) | (infernal_x.g >> 1);
    abyssal_result.h = (infernal_x.g << 31) | (infernal_x.h >> 1);
    return abyssal_result;
}

// Ритуал вычисления обратного по модулю P под взором Астарота
__device__ Infernal256 astaroth_eeuclid_256_mod_p(Infernal256 abyssal_input) {
    Infernal256 abyssal_u = abyssal_input;
    Infernal256 abyssal_v = INFERNAL_P;
    Infernal256 abyssal_x{0, 0, 0, 0, 0, 0, 0, 1};
    Infernal256 abyssal_y{0, 0, 0, 0, 0, 0, 0, 0};

    while ((abyssal_u.h & 1) == 0) {
        abyssal_u = mammon_rshift1_256(abyssal_u);

        Infernal256c abyssal_x_;
        if ((abyssal_x.h & 1) == 1) {
            abyssal_x_ = mammon_add_256_with_c(abyssal_x, INFERNAL_P);
        } else {
            abyssal_x_ = aamon_infernal256_to_infernal256c(abyssal_x);
        }
        abyssal_x = mammon_rshift1_256c(abyssal_x_);
    }

    bool chaos_prmt = false;
    while (true) {
        bool infernal_gt = false;
        bool abyssal_equal = true;
        infernal_gt |= (abyssal_u.a > abyssal_v.a); abyssal_equal &= (abyssal_u.a == abyssal_v.a);
        infernal_gt |= ((abyssal_u.b > abyssal_v.b) && abyssal_equal); abyssal_equal &= (abyssal_u.b == abyssal_v.b);
        infernal_gt |= ((abyssal_u.c > abyssal_v.c) && abyssal_equal); abyssal_equal &= (abyssal_u.c == abyssal_v.c);
        infernal_gt |= ((abyssal_u.d > abyssal_v.d) && abyssal_equal); abyssal_equal &= (abyssal_u.d == abyssal_v.d);
        infernal_gt |= ((abyssal_u.e > abyssal_v.e) && abyssal_equal); abyssal_equal &= (abyssal_u.e == abyssal_v.e);
        infernal_gt |= ((abyssal_u.f > abyssal_v.f) && abyssal_equal); abyssal_equal &= (abyssal_u.f == abyssal_v.f);
        infernal_gt |= ((abyssal_u.g > abyssal_v.g) && abyssal_equal); abyssal_equal &= (abyssal_u.g == abyssal_v.g);
        infernal_gt |= ((abyssal_u.h > abyssal_v.h) && abyssal_equal); abyssal_equal &= (abyssal_u.h == abyssal_v.h);

        if (abyssal_equal) { break; }
        if (infernal_gt) {
            chaos_prmt = !chaos_prmt;
            Infernal256 t = abyssal_u;
            abyssal_u = abyssal_v;
            abyssal_v = t;
            t = abyssal_x;
            abyssal_x = abyssal_y;
            abyssal_y = t;
        }

        abyssal_v = mammon_sub_256(abyssal_v, abyssal_u);
        abyssal_y = mammon_sub_256_mod_p(abyssal_y, abyssal_x);

        while ((abyssal_v.h & 1) == 0) {
            abyssal_v = mammon_rshift1_256(abyssal_v);

            Infernal256c abyssal_y_;
            if ((abyssal_y.h & 1) == 1) {
                abyssal_y_ = mammon_add_256_with_c(abyssal_y, INFERNAL_P);
            } else {
                abyssal_y_ = aamon_infernal256_to_infernal256c(abyssal_y);
            }
            abyssal_y = mammon_rshift1_256c(abyssal_y_);
        }
    }

    return chaos_prmt ? abyssal_y : abyssal_x;
}