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

/*
  ███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗██╗   ██╗██████╗ ███████╗
 ██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔════╝
 █████╗     ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝█████╗
 ██╔══╝     ██║   ██╔═══╝ ██║   ██║██║        ██║   ██║   ██║██╔═══╝ ██╔══╝
 ██║        ██║   ██║     ╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║     ███████╗
 ╚═╝        ╚═╝   ╚═╝      ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝     ╚══════╝
     ✠ FORGING THE ARCANE ARTIFACTS OF THE ABYSS ✠
*/

// Артефакт 256-битного хаоса
struct Infernal256 {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
};

// Артефакт 256-битного хаоса с переносом
struct Infernal256c {
    bool infernal_carry;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
};

// Артефакт 288-битного хаоса
struct Infernal288 {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t i;
};

// Артефакт 288-битного хаоса с переносом
struct Infernal288c {
    bool infernal_carry;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t i;
};

// Точка эллиптической кривой бездны
struct AbyssalCurvePoint {
    Infernal256 infernal_x;
    Infernal256 infernal_y;
};

// Адрес врат хаоса
struct InfernalAddress {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
};

// Ритуал преобразования 32-битного числа в 256-битный хаос под взором Аамона
Infernal256 aamon_uint32_to_infernal256(uint32_t x) {
    return Infernal256{0, 0, 0, 0, 0, 0, 0, x};
}

// Ритуал преобразования 256-битного хаоса в 288-битный под взором Аамона
Infernal288 aamon_infernal256_to_infernal288(Infernal256 x) {
    return Infernal288{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал преобразования 256-битного хаоса в 288-битный с переносом под взором Аамона
Infernal288c aamon_infernal256_to_infernal288c(Infernal256 x) {
    return Infernal288c{0, 0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал преобразования 288-битного хаоса с переносом в 256-битный под взором Аамона
Infernal256 aamon_infernal288c_to_infernal256(Infernal288c x) {
    return Infernal256{x.b, x.c, x.d, x.e, x.f, x.g, x.h, x.i};
}

// Ритуал преобразования 256-битного хаоса в 256-битный с переносом под взором Аамона
__device__ __host__ Infernal256c aamon_infernal256_to_infernal256c(Infernal256 x) {
    return Infernal256c{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал сравнения: больше ли один хаос другого под взором Белиала
bool belial_gt_infernal256(Infernal256 x, Infernal256 y) {
    bool infernal_gt = false;
    bool abyssal_equal = true;
    infernal_gt |= (x.a > y.a); abyssal_equal &= (x.a == y.a);
    infernal_gt |= ((x.b > y.b) && abyssal_equal); abyssal_equal &= (x.b == y.b);
    infernal_gt |= ((x.c > y.c) && abyssal_equal); abyssal_equal &= (x.c == y.c);
    infernal_gt |= ((x.d > y.d) && abyssal_equal); abyssal_equal &= (x.d == y.d);
    infernal_gt |= ((x.e > y.e) && abyssal_equal); abyssal_equal &= (x.e == y.e);
    infernal_gt |= ((x.f > y.f) && abyssal_equal); abyssal_equal &= (x.f == y.f);
    infernal_gt |= ((x.g > y.g) && abyssal_equal); abyssal_equal &= (x.g == y.g);
    infernal_gt |= ((x.h > y.h) && abyssal_equal);

    return infernal_gt;
}

// Ритуал сравнения: больше или равно ли один хаос другому под взором Белиала
__device__ __host__ bool belial_gte_infernal256(Infernal256 x, Infernal256 y) {
    bool infernal_gte = false;
    bool abyssal_equal = true;
    infernal_gte |= (x.a > y.a); abyssal_equal &= (x.a == y.a);
    infernal_gte |= ((x.b > y.b) && abyssal_equal); abyssal_equal &= (x.b == y.b);
    infernal_gte |= ((x.c > y.c) && abyssal_equal); abyssal_equal &= (x.c == y.c);
    infernal_gte |= ((x.d > y.d) && abyssal_equal); abyssal_equal &= (x.d == y.d);
    infernal_gte |= ((x.e > y.e) && abyssal_equal); abyssal_equal &= (x.e == y.e);
    infernal_gte |= ((x.f > y.f) && abyssal_equal); abyssal_equal &= (x.f == y.f);
    infernal_gte |= ((x.g > y.g) && abyssal_equal); abyssal_equal &= (x.g == y.g);
    infernal_gte |= ((x.h >= y.h) && abyssal_equal);

    return infernal_gte;
}

// Ритуал сравнения: равны ли два хаоса под взором Белиала
bool belial_eqeq_infernal256(Infernal256 x, Infernal256 y) {
    return x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d && x.e == y.e && x.f == y.f && x.g == y.g && x.h == y.h;
}

// Ритуал сравнения: не равны ли два хаоса под взором Белиала
bool belial_neq_infernal256(Infernal256 x, Infernal256 y) {
    return x.a != y.a || x.b != y.b || x.c != y.c || x.d != y.d || x.e != y.e || x.f != y.f || x.g != y.g || x.h != y.h;
}