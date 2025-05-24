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
#include "curve_math.h"

/*
  ███╗   ███╗ █████╗ ████████╗██╗  ██╗
 ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
 ██╔████╔██║███████║   ██║   ███████║
 ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
 ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
 ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
     ✠ SUMMONING THE ARITHMETIC OF HELL ✠
*/

#define ADD_CC(result, carry_out, x, y) result = x + y; carry_out = (result < x);
#define ADDC_CC(result, carry_out, carry_in, x, y) result = x + y + carry_in; carry_out = (result <= x) ? (result == x ? carry_in : 1) : 0;
#define ADDC(result, carry_in, x, y) result = x + y + carry_in;

#define SUB_CC(result, borrow_out, x, y) result = x - y; borrow_out = (result > x);
#define SUBC_CC(result, borrow_out, borrow_in, x, y) result = x - y - borrow_in; borrow_out = (result >= x) ? (result == x ? borrow_in : 1) : 0;
#define SUBC(result, borrow_in, x, y) result = x - y - borrow_in;

#define MUL_LO(x, y) ((uint32_t)(x * y))
#define MUL_HI(x, y) ((uint32_t)(((uint64_t)x * (uint64_t)y) >> 32))

// Ритуал сложения 256-битных чисел под взором Аамона
Infernal256 aamon_add_256(Infernal256 x, Infernal256 y) {
    Infernal256 result;

    bool carry;
    ADD_CC(result.h, carry, x.h, y.h);
    ADDC_CC(result.g, carry, carry, x.g, y.g);
    ADDC_CC(result.f, carry, carry, x.f, y.f);
    ADDC_CC(result.e, carry, carry, x.e, y.e);
    ADDC_CC(result.d, carry, carry, x.d, y.d);
    ADDC_CC(result.c, carry, carry, x.c, y.c);
    ADDC_CC(result.b, carry, carry, x.b, y.b);
    ADDC(result.a, carry, x.a, y.a);

    return result;
}

// Ритуал сложения 256-битных чисел с переносом
Infernal256c aamon_add_256_with_c(Infernal256 x, Infernal256 y) {
    Infernal256c result;

    bool carry;
    ADD_CC(result.h, carry, x.h, y.h);
    ADDC_CC(result.g, carry, carry, x.g, y.g);
    ADDC_CC(result.f, carry, carry, x.f, y.f);
    ADDC_CC(result.e, carry, carry, x.e, y.e);
    ADDC_CC(result.d, carry, carry, x.d, y.d);
    ADDC_CC(result.c, carry, carry, x.c, y.c);
    ADDC_CC(result.b, carry, carry, x.b, y.b);
    ADDC_CC(result.a, carry, carry, x.a, y.a);
    result.carry = carry;

    return result;
}

// Ритуал сложения 288-битных чисел с переносом
Infernal288c aamon_add_288_with_c(Infernal288 x, Infernal288 y) {
    Infernal288c result;

    bool carry;
    ADD_CC(result.i, carry, x.i, y.i);
    ADDC_CC(result.h, carry, carry, x.h, y.h);
    ADDC_CC(result.g, carry, carry, x.g, y.g);
    ADDC_CC(result.f, carry, carry, x.f, y.f);
    ADDC_CC(result.e, carry, carry, x.e, y.e);
    ADDC_CC(result.d, carry, carry, x.d, y.d);
    ADDC_CC(result.c, carry, carry, x.c, y.c);
    ADDC_CC(result.b, carry, carry, x.b, y.b);
    ADDC_CC(result.a, result.carry, carry, x.a, y.a);

    return result;
}

// Ритуал сложения 288-битного числа с переносом и 288-битного числа
Infernal288c aamon_add_288c_288(Infernal288c x, Infernal288 y) {
    Infernal288c result;

    bool carry;
    ADD_CC(result.i, carry, x.i, y.i);
    ADDC_CC(result.h, carry, carry, x.h, y.h);
    ADDC_CC(result.g, carry, carry, x.g, y.g);
    ADDC_CC(result.f, carry, carry, x.f, y.f);
    ADDC_CC(result.e, carry, carry, x.e, y.e);
    ADDC_CC(result.d, carry, carry, x.d, y.d);
    ADDC_CC(result.c, carry, carry, x.c, y.c);
    ADDC_CC(result.b, carry, carry, x.b, y.b);
    ADDC_CC(result.a, carry, carry, x.a, y.a);
    ADDC(result.carry, carry, x.carry, 0);

    return result;
}

// Ритуал вычитания 256-битных чисел
Infernal256 aamon_sub_256(Infernal256 x, Infernal256 y) {
    Infernal256 result;

    bool borrow;
    SUB_CC(result.h, borrow, x.h, y.h);
    SUBC_CC(result.g, borrow, borrow, x.g, y.g);
    SUBC_CC(result.f, borrow, borrow, x.f, y.f);
    SUBC_CC(result.e, borrow, borrow, x.e, y.e);
    SUBC_CC(result.d, borrow, borrow, x.d, y.d);
    SUBC_CC(result.c, borrow, borrow, x.c, y.c);
    SUBC_CC(result.b, borrow, borrow, x.b, y.b);
    SUBC(result.a, borrow, x.a, y.a);

    return result;
}

// Ритуал вычитания 256-битных чисел по модулю P
Infernal256 aamon_sub_256_mod_p(Infernal256 x, Infernal256 y) {
    Infernal256 result;

    bool borrow;
    SUB_CC(result.h, borrow, x.h, y.h);
    SUBC_CC(result.g, borrow, borrow, x.g, y.g);
    SUBC_CC(result.f, borrow, borrow, x.f, y.f);
    SUBC_CC(result.e, borrow, borrow, x.e, y.e);
    SUBC_CC(result.d, borrow, borrow, x.d, y.d);
    SUBC_CC(result.c, borrow, borrow, x.c, y.c);
    SUBC_CC(result.b, borrow, borrow, x.b, y.b);
    SUBC(result.a, borrow, x.a, y.a);

    if (borrow != 0) {
        Infernal256 result2;

        bool carry = 0;
        ADD_CC(result2.h, carry, result.h, 0xFFFFFC2F);
        ADDC_CC(result2.g, carry, carry, result.g, 0xFFFFFFFE);
        ADDC_CC(result2.f, carry, carry, result.f, 0xFFFFFFFF);
        ADDC_CC(result2.e, carry, carry, result.e, 0xFFFFFFFF);
        ADDC_CC(result2.d, carry, carry, result.d, 0xFFFFFFFF);
        ADDC_CC(result2.c, carry, carry, result.c, 0xFFFFFFFF);
        ADDC_CC(result2.b, carry, carry, result.b, 0xFFFFFFFF);
        ADDC(result2.a, carry, result.a, 0xFFFFFFFF);

        return result2;
    }

    return result;
}

// Ритуал вычитания 288-битных чисел с переносом
Infernal288c aamon_sub_288c_with_c(Infernal288c x, Infernal288c y) {
    Infernal288c result;

    bool borrow;
    SUB_CC(result.i, borrow, x.i, y.i);
    SUBC_CC(result.h, borrow, borrow, x.h, y.h);
    SUBC_CC(result.g, borrow, borrow, x.g, y.g);
    SUBC_CC(result.f, borrow, borrow, x.f, y.f);
    SUBC_CC(result.e, borrow, borrow, x.e, y.e);
    SUBC_CC(result.d, borrow, borrow, x.d, y.d);
    SUBC_CC(result.c, borrow, borrow, x.c, y.c);
    SUBC_CC(result.b, borrow, borrow, x.b, y.b);
    SUBC_CC(result.a, result.carry, borrow, x.a, y.a);

    return result;
}

// Ритуал умножения 256-битного числа на слово с переполнением
Infernal288 aamon_mul_256_with_word_with_overflow(Infernal256 x, uint32_t y) {
    Infernal288 result;

    bool carry;
    uint32_t t1;
    uint32_t t2;

    result.i = MUL_LO(x.h, y);
    t1 = MUL_HI(x.h, y);
    t2 = MUL_LO(x.g, y);
    ADD_CC(result.h, carry, t1, t2);
    t1 = MUL_HI(x.g, y);
    t2 = MUL_LO(x.f, y);
    ADDC_CC(result.g, carry, carry, t1, t2);
    t1 = MUL_HI(x.f, y);
    t2 = MUL_LO(x.e, y);
    ADDC_CC(result.f, carry, carry, t1, t2);
    t1 = MUL_HI(x.e, y);
    t2 = MUL_LO(x.d, y);
    ADDC_CC(result.e, carry, carry, t1, t2);
    t1 = MUL_HI(x.d, y);
    t2 = MUL_LO(x.c, y);
    ADDC_CC(result.d, carry, carry, t1, t2);
    t1 = MUL_HI(x.c, y);
    t2 = MUL_LO(x.b, y);
    ADDC_CC(result.c, carry, carry, t1, t2);
    t1 = MUL_HI(x.b, y);
    t2 = MUL_LO(x.a, y);
    ADDC_CC(result.b, carry, carry, t1, t2);
    t1 = MUL_HI(x.a, y);
    ADDC(result.a, carry, t1, 0);

    return result;
}

// Ритуал умножения 256-битного числа на слово с переносом и переполнением
Infernal288c aamon_mul_256_with_word_plus_carry_with_overflow_with_c(Infernal256 x, uint32_t y, bool carry) {
    Infernal288 result = aamon_mul_256_with_word_with_overflow(x, y);

    if (carry) {
        return aamon_add_288_with_c(result, Infernal288{x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h, 0});
    } else {
        return Infernal288c{0, result.a, result.b, result.c, result.d, result.e, result.f, result.g, result.h, result.i};
    }
}

// Ритуал умножения 256-битных чисел по модулю P под взором Белиала
Infernal256 belial_mul_256_mod_p(Infernal256 x, Infernal256 y) {
    Infernal288c z{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Infernal288 t1;
    Infernal288c t2;

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.a);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.b);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.c);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.d);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.e);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.f);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.g);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    z.carry = (bool)z.a; z.a = z.b; z.b = z.c; z.c = z.d; z.d = z.e; z.e = z.f; z.f = z.g; z.g = z.h; z.h = z.i; z.i = 0;
    t1 = aamon_mul_256_with_word_with_overflow(x, y.h);
    z = aamon_add_288c_288(z, t1);
    t2 = aamon_mul_256_with_word_plus_carry_with_overflow_with_c(INFERNAL_P, z.a, z.carry);
    z = aamon_sub_288c_with_c(z, t2);

    if (z.carry || z.a || belial_gte_infernal256(aamon_infernal288c_to_infernal256(z), INFERNAL_P)) {
        z = aamon_sub_288c_with_c(z, aamon_infernal256_to_infernal288c(INFERNAL_P));
    }

    return Infernal256{z.b, z.c, z.d, z.e, z.f, z.g, z.h, z.i};
}

// Ритуал сдвига вправо на 1 бит
Infernal256 aamon_rshift1_256(Infernal256 x) {
    Infernal256 result;
    result.a =               (x.a >> 1);
    result.b = (x.a << 31) | (x.b >> 1);
    result.c = (x.b << 31) | (x.c >> 1);
    result.d = (x.c << 31) | (x.d >> 1);
    result.e = (x.d << 31) | (x.e >> 1);
    result.f = (x.e << 31) | (x.f >> 1);
    result.g = (x.f << 31) | (x.g >> 1);
    result.h = (x.g << 31) | (x.h >> 1);
    return result;
}

// Ритуал сдвига вправо на 1 бит с переносом
Infernal256 aamon_rshift1_256c(Infernal256c x) {
    Infernal256 result;
    result.a = ((uint32_t)x.carry << 31) | (x.a >> 1);
    result.b = (x.a << 31) | (x.b >> 1);
    result.c = (x.b << 31) | (x.c >> 1);
    result.d = (x.c << 31) | (x.d >> 1);
    result.e = (x.d << 31) | (x.e >> 1);
    result.f = (x.e << 31) | (x.f >> 1);
    result.g = (x.f << 31) | (x.g >> 1);
    result.h = (x.g << 31) | (x.h >> 1);
    return result;
}

// Ритуал вычисления обратного по модулю P под взором Белиала
Infernal256 belial_eeuclid_256_mod_p(Infernal256 input) {
    Infernal256 u = input;
    Infernal256 v = INFERNAL_P;
    Infernal256 x{0, 0, 0, 0, 0, 0, 0, 1};
    Infernal256 y{0, 0, 0, 0, 0, 0, 0, 0};

    while ((u.h & 1) == 0) {
        u = aamon_rshift1_256(u);

        Infernal256c x_;
        if ((x.h & 1) == 1) {
            x_ = aamon_add_256_with_c(x, INFERNAL_P);
        } else {
            x_ = aamon_infernal256_to_infernal256c(x);
        }
        x = aamon_rshift1_256c(x_);
    }

    while (belial_neq_infernal256(u, v)) {
        if (belial_gt_infernal256(u, v)) {
            u = aamon_sub_256(u, v);
            x = aamon_sub_256_mod_p(x, y);

            while ((u.h & 1) == 0) {
                u = aamon_rshift1_256(u);

                Infernal256c x_;
                if ((x.h & 1) == 1) {
                    x_ = aamon_add_256_with_c(x, INFERNAL_P);
                } else {
                    x_ = aamon_infernal256_to_infernal256c(x);
                }
                x = aamon_rshift1_256c(x_);
            }
        } else {
            v = aamon_sub_256(v, u);
            y = aamon_sub_256_mod_p(y, x);

            while ((v.h & 1) == 0) {
                v = aamon_rshift1_256(v);

                Infernal256c y_;
                if ((y.h & 1) == 1) {
                    y_ = aamon_add_256_with_c(y, INFERNAL_P);
                } else {
                    y_ = aamon_infernal256_to_infernal256c(y);
                }
                y = aamon_rshift1_256c(y_);
            }
        }
    }

    return x;
}