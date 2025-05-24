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
     ✠ SUMMONING THE DATA FORMS OF THE DAMNED ✠
*/

// Абиссальная структура для 256-битного числа
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

// Абиссальная структура для 256-битного числа с переносом
struct Infernal256c {
    bool carry;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
};

// Абиссальная структура для 288-битного числа
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

// Абиссальная структура для 288-битного числа с переносом
struct Infernal288c {
    bool carry;
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

// Точка на эллиптической кривой ада
struct AbyssalCurvePoint {
    Infernal256 x;
    Infernal256 y;
};

// Адрес кошелька или контракта в бездне
struct InfernalAddress {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
};

// Ритуал преобразования 32-битного числа в 256-битное
__host__ Infernal256 aamon_uint32_to_infernal256(uint32_t x) {
    return Infernal256{0, 0, 0, 0, 0, 0, 0, x};
}

// Ритуал преобразования 256-битного числа в 288-битное
__host__ Infernal288 aamon_infernal256_to_infernal288(Infernal256 x) {
    return Infernal288{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал преобразования 256-битного числа в 288-битное с переносом
__host__ Infernal288c aamon_infernal256_to_infernal288c(Infernal256 x) {
    return Infernal288c{0, 0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал преобразования 288-битного числа с переносом в 256-битное
__host__ Infernal256 aamon_infernal288c_to_infernal256(Infernal288c x) {
    return Infernal256{x.b, x.c, x.d, x.e, x.f, x.g, x.h, x.i};
}

// Ритуал преобразования 256-битного числа в 256-битное с переносом
__host__ __device__ Infernal256c aamon_infernal256_to_infernal256c(Infernal256 x) {
    return Infernal256c{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

// Ритуал сравнения: больше ли одно 256-битное число другого
__host__ __device__ bool belial_gt_infernal256(Infernal256 x, Infernal256 y) {
    bool gt = false;
    bool equal = true;
    gt |= (x.a > y.a); equal &= (x.a == y.a);
    gt |= ((x.b > y.b) && equal); equal &= (x.b == y.b);
    gt |= ((x.c > y.c) && equal); equal &= (x.c == y.c);
    gt |= ((x.d > y.d) && equal); equal &= (x.d == y.d);
    gt |= ((x.e > y.e) && equal); equal &= (x.e == y.e);
    gt |= ((x.f > y.f) && equal); equal &= (x.f == y.f);
    gt |= ((x.g > y.g) && equal); equal &= (x.g == y.g);
    gt |= ((x.h > y.h) && equal);

    return gt;
}

// Ритуал сравнения: больше или равно ли одно 256-битное число другому
__host__ __device__ bool belial_gte_infernal256(Infernal256 x, Infernal256 y) {
    bool gte = false;
    bool equal = true;
    gte |= (x.a > y.a); equal &= (x.a == y.a);
    gte |= ((x.b > y.b) && equal); equal &= (x.b == y.b);
    gte |= ((x.c > y.c) && equal); equal &= (x.c == y.c);
    gte |= ((x.d > y.d) && equal); equal &= (x.d == y.d);
    gte |= ((x.e > y.e) && equal); equal &= (x.e == y.e);
    gte |= ((x.f > y.f) && equal); equal &= (x.f == y.f);
    gte |= ((x.g > y.g) && equal); equal &= (x.g == y.g);
    gte |= ((x.h >= y.h) && equal);

    return gte;
}

// Ритуал проверки равенства двух 256-битных чисел
__host__ __device__ bool belial_eqeq_infernal256(Infernal256 x, Infernal256 y) {
    return x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d && x.e == y.e && x.f == y.f && x.g == y.g && x.h == y.h;
}

// Ритуал проверки неравенства двух 256-битных чисел
__host__ __device__ bool belial_neq_infernal256(Infernal256 x, Infernal256 y) {
    return x.a != y.a || x.b != y.b || x.c != y.c || x.d != y.d || x.e != y.e || x.f != y.f || x.g != y.g || x.h != y.h;
}