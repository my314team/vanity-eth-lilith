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


struct _uint256 {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
};

struct _uint256c {
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

struct _uint288 {
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

struct _uint288c {
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

struct CurvePoint {
    _uint256 x;
    _uint256 y;
};

struct Address {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
};


_uint256 uint32_to_uint256(uint32_t x) {
    return _uint256{0, 0, 0, 0, 0, 0, 0, x};
}

_uint288 uint256_to_uint288(_uint256 x) {
    return _uint288{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

_uint288c uint256_to_uint288c(_uint256 x) {
    return _uint288c{0, 0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}

_uint256 uint288c_to_uint256(_uint288c x) {
    return _uint256{x.b, x.c, x.d, x.e, x.f, x.g, x.h, x.i};
}

__device__ __host__ _uint256c uint256_to_uint256c(_uint256 x) {
    return _uint256c{0, x.a, x.b, x.c, x.d, x.e, x.f, x.g, x.h};
}


bool gt_256(_uint256 x, _uint256 y) {
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

__device__ __host__ bool gte_256(_uint256 x, _uint256 y) {
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

bool eqeq_256(_uint256 x, _uint256 y) {
    return x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d && x.e == y.e && x.f == y.f && x.g == y.g && x.h == y.h;
}

bool neq_256(_uint256 x, _uint256 y) {
    return x.a != y.a || x.b != y.b || x.c != y.c || x.d != y.d || x.e != y.e || x.f != y.f || x.g != y.g || x.h != y.h; 
}