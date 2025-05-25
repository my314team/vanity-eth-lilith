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
  ██████╗ ██████╗ ██╗   ██╗    ███╗   ███╗ █████╗ ████████╗██╗  ██╗
 ██╔════╝ ██╔══██╗██║   ██║    ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
 ██║  ███╗██████╔╝██║   ██║    ██╔████╔██║███████║   ██║   ███████║
 ██║   ██║ ██╔══██╗██║   ██║    ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
 ╚██████╔╝ ██║  ██║╚██████╔╝    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
  ╚═════╝  ╚═╝  ╚═╝ ╚═════╝     ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
     ✠ SUMMONING THE ARITHMETIC OF THE ETERNAL DAMNED ON CPU ✠
*/

// Модуль эллиптической кривой, граница бездны
#define INFERNAL_P Infernal256{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFC2F}

// Макросы для арифметических ритуалов
#define INFERNAL_ADD_CC(abyssal_result, infernal_carry_out, x, y) abyssal_result = x + y; infernal_carry_out = (abyssal_result < x);
#define INFERNAL_ADDC_CC(abyssal_result, infernal_carry_out, infernal_carry_in, x, y) abyssal_result = x + y + infernal_carry_in; infernal_carry_out = (abyssal_result <= x) ? (abyssal_result == x ? infernal_carry_in : 1) : 0;
#define INFERNAL_ADDC(abyssal_result, infernal_carry_in, x, y) abyssal_result = x + y + infernal_carry_in;

#define INFERNAL_SUB_CC(abyssal_result, infernal_borrow_out, x, y) abyssal_result = x - y; infernal_borrow_out = (abyssal_result > x);
#define INFERNAL_SUBC_CC(abyssal_result, infernal_borrow_out, infernal_borrow_in, x, y) abyssal_result = x - y - infernal_borrow_in; infernal_borrow_out = (abyssal_result >= x) ? (abyssal_result == x ? infernal_borrow_in : 1) : 0;
#define INFERNAL_SUBC(abyssal_result, infernal_borrow_in, x, y) abyssal_result = x - y - infernal_borrow_in;

#define INFERNAL_MUL_LO(x, y) ((uint32_t)(x * y))
#define INFERNAL_MUL_HI(x, y) ((uint32_t)(((uint64_t)x * (uint64_t)y) >> 32))

// Ритуал сложения 256-битных чисел на CPU под взором Маммона
Infernal256 mammon_cpu_add_256(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result;

    bool infernal_carry;
    INFERNAL_ADD_CC(abyssal_result.h, infernal_carry, infernal_x.h, infernal_y.h);
    INFERNAL_ADDC_CC(abyssal_result.g, infernal_carry, infernal_carry, infernal_x.g, infernal_y.g);
    INFERNAL_ADDC_CC(abyssal_result.f, infernal_carry, infernal_carry, infernal_x.f, infernal_y.f);
    INFERNAL_ADDC_CC(abyssal_result.e, infernal_carry, infernal_carry, infernal_x.e, infernal_y.e);
    INFERNAL_ADDC_CC(abyssal_result.d, infernal_carry, infernal_carry, infernal_x.d, infernal_y.d);
    INFERNAL_ADDC_CC(abyssal_result.c, infernal_carry, infernal_carry, infernal_x.c, infernal_y.c);
    INFERNAL_ADDC_CC(abyssal_result.b, infernal_carry, infernal_carry, infernal_x.b, infernal_y.b);
    INFERNAL_ADDC(abyssal_result.a, infernal_carry, infernal_x.a, infernal_y.a);

    return abyssal_result;
}

// Ритуал сложения 256-битных чисел с переносом на CPU под взором Маммона
Infernal256c mammon_cpu_add_256_with_c(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256c abyssal_result;

    bool infernal_carry;
    INFERNAL_ADD_CC(abyssal_result.h, infernal_carry, infernal_x.h, infernal_y.h);
    INFERNAL_ADDC_CC(abyssal_result.g, infernal_carry, infernal_carry, infernal_x.g, infernal_y.g);
    INFERNAL_ADDC_CC(abyssal_result.f, infernal_carry, infernal_carry, infernal_x.f, infernal_y.f);
    INFERNAL_ADDC_CC(abyssal_result.e, infernal_carry, infernal_carry, infernal_x.e, infernal_y.e);
    INFERNAL_ADDC_CC(abyssal_result.d, infernal_carry, infernal_carry, infernal_x.d, infernal_y.d);
    INFERNAL_ADDC_CC(abyssal_result.c, infernal_carry, infernal_carry, infernal_x.c, infernal_y.c);
    INFERNAL_ADDC_CC(abyssal_result.b, infernal_carry, infernal_carry, infernal_x.b, infernal_y.b);
    INFERNAL_ADDC_CC(abyssal_result.a, infernal_carry, infernal_carry, infernal_x.a, infernal_y.a);
    abyssal_result.carry = infernal_carry;

    return abyssal_result;
}

// Ритуал сложения 288-битных чисел с переносом на CPU под взором Маммона
Infernal288c mammon_cpu_add_288_with_c(Infernal288 infernal_x, Infernal288 infernal_y) {
    Infernal288c abyssal_result;

    bool infernal_carry;
    INFERNAL_ADD_CC(abyssal_result.i, infernal_carry, infernal_x.i, infernal_y.i);
    INFERNAL_ADDC_CC(abyssal_result.h, infernal_carry, infernal_carry, infernal_x.h, infernal_y.h);
    INFERNAL_ADDC_CC(abyssal_result.g, infernal_carry, infernal_carry, infernal_x.g, infernal_y.g);
    INFERNAL_ADDC_CC(abyssal_result.f, infernal_carry, infernal_carry, infernal_x.f, infernal_y.f);
    INFERNAL_ADDC_CC(abyssal_result.e, infernal_carry, infernal_carry, infernal_x.e, infernal_y.e);
    INFERNAL_ADDC_CC(abyssal_result.d, infernal_carry, infernal_carry, infernal_x.d, infernal_y.d);
    INFERNAL_ADDC_CC(abyssal_result.c, infernal_carry, infernal_carry, infernal_x.c, infernal_y.c);
    INFERNAL_ADDC_CC(abyssal_result.b, infernal_carry, infernal_carry, infernal_x.b, infernal_y.b);
    INFERNAL_ADDC_CC(abyssal_result.a, abyssal_result.carry, infernal_carry, infernal_x.a, infernal_y.a);

    return abyssal_result;
}

// Ритуал сложения 288-битного числа с переносом и 288-битного числа на CPU под взором Маммона
Infernal288c mammon_cpu_add_288c_288(Infernal288c infernal_x, Infernal288 infernal_y) {
    Infernal288c abyssal_result;

    bool infernal_carry;
    INFERNAL_ADD_CC(abyssal_result.i, infernal_carry, infernal_x.i, infernal_y.i);
    INFERNAL_ADDC_CC(abyssal_result.h, infernal_carry, infernal_carry, infernal_x.h, infernal_y.h);
    INFERNAL_ADDC_CC(abyssal_result.g, infernal_carry, infernal_carry, infernal_x.g, infernal_y.g);
    INFERNAL_ADDC_CC(abyssal_result.f, infernal_carry, infernal_carry, infernal_x.f, infernal_y.f);
    INFERNAL_ADDC_CC(abyssal_result.e, infernal_carry, infernal_carry, infernal_x.e, infernal_y.e);
    INFERNAL_ADDC_CC(abyssal_result.d, infernal_carry, infernal_carry, infernal_x.d, infernal_y.d);
    INFERNAL_ADDC_CC(abyssal_result.c, infernal_carry, infernal_carry, infernal_x.c, infernal_y.c);
    INFERNAL_ADDC_CC(abyssal_result.b, infernal_carry, infernal_carry, infernal_x.b, infernal_y.b);
    INFERNAL_ADDC_CC(abyssal_result.a, infernal_carry, infernal_carry, infernal_x.a, infernal_y.a);
    INFERNAL_ADDC(abyssal_result.carry, infernal_carry, infernal_x.carry, 0);

    return abyssal_result;
}

// Ритуал вычитания 256-битных чисел на CPU под взором Маммона
Infernal256 mammon_cpu_sub_256(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result;

    bool infernal_borrow;
    INFERNAL_SUB_CC(abyssal_result.h, infernal_borrow, infernal_x.h, infernal_y.h);
    INFERNAL_SUBC_CC(abyssal_result.g, infernal_borrow, infernal_borrow, infernal_x.g, infernal_y.g);
    INFERNAL_SUBC_CC(abyssal_result.f, infernal_borrow, infernal_borrow, infernal_x.f, infernal_y.f);
    INFERNAL_SUBC_CC(abyssal_result.e, infernal_borrow, infernal_borrow, infernal_x.e, infernal_y.e);
    INFERNAL_SUBC_CC(abyssal_result.d, infernal_borrow, infernal_borrow, infernal_x.d, infernal_y.d);
    INFERNAL_SUBC_CC(abyssal_result.c, infernal_borrow, infernal_borrow, infernal_x.c, infernal_y.c);
    INFERNAL_SUBC_CC(abyssal_result.b, infernal_borrow, infernal_borrow, infernal_x.b, infernal_y.b);
    INFERNAL_SUBC(abyssal_result.a, infernal_borrow, infernal_x.a, infernal_y.a);

    return abyssal_result;
}

// Ритуал вычитания 256-битных чисел по модулю P на CPU под взором Маммона
Infernal256 mammon_cpu_sub_256_mod_p(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal256 abyssal_result;

    bool infernal_borrow;
    INFERNAL_SUB_CC(abyssal_result.h, infernal_borrow, infernal_x.h, infernal_y.h);
    INFERNAL_SUBC_CC(abyssal_result.g, infernal_borrow, infernal_borrow, infernal_x.g, infernal_y.g);
    INFERNAL_SUBC_CC(abyssal_result.f, infernal_borrow, infernal_borrow, infernal_x.f, infernal_y.f);
    INFERNAL_SUBC_CC(abyssal_result.e, infernal_borrow, infernal_borrow, infernal_x.e, infernal_y.e);
    INFERNAL_SUBC_CC(abyssal_result.d, infernal_borrow, infernal_borrow, infernal_x.d, infernal_y.d);
    INFERNAL_SUBC_CC(abyssal_result.c, infernal_borrow, infernal_borrow, infernal_x.c, infernal_y.c);
    INFERNAL_SUBC_CC(abyssal_result.b, infernal_borrow, infernal_borrow, infernal_x.b, infernal_y.b);
    INFERNAL_SUBC_CC(abyssal_result.a, infernal_borrow, infernal_borrow, infernal_x.a, infernal_y.a);

    if (infernal_borrow != 0) {
        Infernal256 abyssal_result2;

        bool infernal_carry = 0;
        INFERNAL_ADD_CC(abyssal_result2.h, infernal_carry, abyssal_result.h, 0xFFFFFC2F);
        INFERNAL_ADDC_CC(abyssal_result2.g, infernal_carry, infernal_carry, abyssal_result.g, 0xFFFFFFFE);
        INFERNAL_ADDC_CC(abyssal_result2.f, infernal_carry, infernal_carry, abyssal_result.f, 0xFFFFFFFF);
        INFERNAL_ADDC_CC(abyssal_result2.e, infernal_carry, infernal_carry, abyssal_result.e, 0xFFFFFFFF);
        INFERNAL_ADDC_CC(abyssal_result2.d, infernal_carry, infernal_carry, abyssal_result.d, 0xFFFFFFFF);
        INFERNAL_ADDC_CC(abyssal_result2.c, infernal_carry, infernal_carry, abyssal_result.c, 0xFFFFFFFF);
        INFERNAL_ADDC_CC(abyssal_result2.b, infernal_carry, infernal_carry, abyssal_result.b, 0xFFFFFFFF);
        INFERNAL_ADDC(abyssal_result2.a, infernal_carry, abyssal_result.a, 0xFFFFFFFF);

        return abyssal_result2;
    }

    return abyssal_result;
}

// Ритуал вычитания 288-битных чисел с переносом на CPU под взором Маммона
Infernal288c mammon_cpu_sub_288c_with_c(Infernal288c infernal_x, Infernal288c infernal_y) {
    Infernal288c abyssal_result;

    bool infernal_borrow;
    INFERNAL_SUB_CC(abyssal_result.i, infernal_borrow, infernal_x.i, infernal_y.i);
    INFERNAL_SUBC_CC(abyssal_result.h, infernal_borrow, infernal_borrow, infernal_x.h, infernal_y.h);
    INFERNAL_SUBC_CC(abyssal_result.g, infernal_borrow, infernal_borrow, infernal_x.g, infernal_y.g);
    INFERNAL_SUBC_CC(abyssal_result.f, infernal_borrow, infernal_borrow, infernal_x.f, infernal_y.f);
    INFERNAL_SUBC_CC(abyssal_result.e, infernal_borrow, infernal_borrow, infernal_x.e, infernal_y.e);
    INFERNAL_SUBC_CC(abyssal_result.d, infernal_borrow, infernal_borrow, infernal_x.d, infernal_y.d);
    INFERNAL_SUBC_CC(abyssal_result.c, infernal_borrow, infernal_borrow, infernal_x.c, infernal_y.c);
    INFERNAL_SUBC_CC(abyssal_result.b, infernal_borrow, infernal_borrow, infernal_x.b, infernal_y.b);
    INFERNAL_SUBC_CC(abyssal_result.a, abyssal_result.carry, infernal_borrow, infernal_x.a, infernal_y.a);

    return abyssal_result;
}

// Ритуал умножения 256-битного числа на слово с переполнением на CPU под взором Астарота
Infernal288 astaroth_cpu_mul_256_with_word_with_overflow(Infernal256 infernal_x, uint32_t infernal_y) {
    Infernal288 abyssal_result;

    bool infernal_carry;
    uint32_t chaos_t1;
    uint32_t chaos_t2;

    abyssal_result.i = INFERNAL_MUL_LO(infernal_x.h, infernal_y);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.h, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.g, infernal_y);
    INFERNAL_ADD_CC(abyssal_result.h, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.g, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.f, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.g, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.f, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.e, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.f, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.e, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.d, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.e, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.d, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.c, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.d, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.c, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.b, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.c, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.b, infernal_y);
    chaos_t2 = INFERNAL_MUL_LO(infernal_x.a, infernal_y);
    INFERNAL_ADDC_CC(abyssal_result.b, infernal_carry, infernal_carry, chaos_t1, chaos_t2);
    chaos_t1 = INFERNAL_MUL_HI(infernal_x.a, infernal_y);
    INFERNAL_ADDC(abyssal_result.a, infernal_carry, chaos_t1, 0);

    return abyssal_result;
}

// Ритуал умножения 256-битного числа на слово с переносом и переполнением на CPU под взором Астарота
Infernal288c astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(Infernal256 infernal_x, uint32_t infernal_y, bool infernal_carry) {
    Infernal288 abyssal_result = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y);

    if (infernal_carry) {
        return mammon_cpu_add_288_with_c(abyssal_result, Infernal288{infernal_x.a, infernal_x.b, infernal_x.c, infernal_x.d, infernal_x.e, infernal_x.f, infernal_x.g, infernal_x.h, 0});
    } else {
        return Infernal288c{0, abyssal_result.a, abyssal_result.b, abyssal_result.c, abyssal_result.d, abyssal_result.e, abyssal_result.f, abyssal_result.g, abyssal_result.h, abyssal_result.i};
    }
}

// Ритуал умножения 256-битных чисел по модулю P на CPU под взором Астарота
Infernal256 astaroth_cpu_mul_256_mod_p(Infernal256 infernal_x, Infernal256 infernal_y) {
    Infernal288c abyssal_z{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Infernal288 chaos_t1;
    Infernal288c chaos_t2;

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.a);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.b);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.c);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.d);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.e);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.f);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.g);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    abyssal_z.carry = (bool)abyssal_z.a; abyssal_z.a = abyssal_z.b; abyssal_z.b = abyssal_z.c; abyssal_z.c = abyssal_z.d; abyssal_z.d = abyssal_z.e; abyssal_z.e = abyssal_z.f; abyssal_z.f = abyssal_z.g; abyssal_z.g = abyssal_z.h; abyssal_z.h = abyssal_z.i; abyssal_z.i = 0;
    chaos_t1 = astaroth_cpu_mul_256_with_word_with_overflow(infernal_x, infernal_y.h);
    abyssal_z = mammon_cpu_add_288c_288(abyssal_z, chaos_t1);
    chaos_t2 = astaroth_cpu_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, abyssal_z.a, abyssal_z.carry);
    abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, chaos_t2);

    if (abyssal_z.carry || abyssal_z.a || belial_gte_infernal256(aamon_infernal288c_to_infernal256(abyssal_z), INFERNAL_P)) {
        abyssal_z = mammon_cpu_sub_288c_with_c(abyssal_z, aamon_infernal256_to_infernal288c(INFERNAL_P));
    }

    return Infernal256{abyssal_z.b, abyssal_z.c, abyssal_z.d, abyssal_z.e, abyssal_z.f, abyssal_z.g, abyssal_z.h, abyssal_z.i};
}

// Ритуал сдвига вправо на 1 бит на CPU под взором Маммона
Infernal256 mammon_cpu_rshift1_256(Infernal256 infernal_x) {
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

// Ритуал сдвига вправо на 1 бит с переносом на CPU под взором Маммона
Infernal256 mammon_cpu_rshift1_256c(Infernal256c infernal_x) {
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

// Ритуал вычисления обратного по модулю P на CPU под взором Астарота
Infernal256 astaroth_cpu_eeuclid_256_mod_p(Infernal256 abyssal_input) {
    // https://www.researchgate.net/publication/344657706_A_New_Improvement_of_Extended_Stein's_Binary_Algorithm
    Infernal256 abyssal_u = abyssal_input;
    Infernal256 abyssal_v = INFERNAL_P;
    Infernal256 abyssal_x{0, 0, 0, 0, 0, 0, 0, 1};
    Infernal256 abyssal_y{0, 0, 0, 0, 0, 0, 0, 0};

    while ((abyssal_u.h & 1) == 0) {
        abyssal_u = mammon_cpu_rshift1_256(abyssal_u);

        Infernal256c abyssal_x_;
        if ((abyssal_x.h & 1) == 1) {
            abyssal_x_ = mammon_cpu_add_256_with_c(abyssal_x, INFERNAL_P);
        } else {
            abyssal_x_ = aamon_infernal256_to_infernal256c(abyssal_x);
        }
        abyssal_x = mammon_cpu_rshift1_256c(abyssal_x_);
    }

    while (belial_neq_infernal256(abyssal_u, abyssal_v)) {
        if (belial_gt_infernal256(abyssal_u, abyssal_v)) {
            abyssal_u = mammon_cpu_sub_256(abyssal_u, abyssal_v);
            abyssal_x = mammon_cpu_sub_256_mod_p(abyssal_x, abyssal_y);

            while ((abyssal_u.h & 1) == 0) {
                abyssal_u = mammon_cpu_rshift1_256(abyssal_u);

                Infernal256c abyssal_x_;
                if ((abyssal_x.h & 1) == 1) {
                    abyssal_x_ = mammon_cpu_add_256_with_c(abyssal_x, INFERNAL_P);
                } else {
                    abyssal_x_ = aamon_infernal256_to_infernal256c(abyssal_x);
                }
                abyssal_x = mammon_cpu_rshift1_256c(abyssal_x_);
            }
        } else {
            abyssal_v = mammon_cpu_sub_256(abyssal_v, abyssal_u);
            abyssal_y = mammon_cpu_sub_256_mod_p(abyssal_y, abyssal_x);

            while ((abyssal_v.h & 1) == 0) {
                abyssal_v = mammon_cpu_rshift1_256(abyssal_v);

                Infernal256c abyssal_y_;
                if ((abyssal_y.h & 1) == 1) {
                    abyssal_y_ = mammon_cpu_add_256_with_c(abyssal_y, INFERNAL_P);
                } else {
                    abyssal_y_ = aamon_infernal256_to_infernal256c(abyssal_y);
                }
                abyssal_y = mammon_cpu_rshift1_256c(abyssal_y_);
            }
        }
    }

    return abyssal_x;
}