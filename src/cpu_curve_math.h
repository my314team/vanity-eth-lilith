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
#include "cpu_math.h"
#include "structures.h"

/*
  ██████╗ ██╗   ██╗██████╗ ██╗   ██╗███████╗
 ██╔═══██╗██║   ██║██╔══██╗██║   ██║██╔════╝
 ██║   ██║██║   ██║██████╔╝██║   ██║█████╗
 ██║   ██║██║   ██║██╔═══╝ ██║   ██║██╔══╝
 ╚██████╔╝╚██████╔╝██║     ╚██████╔╝███████╗
  ╚═════╝  ╚═════╝ ╚═╝      ╚═════╝ ╚══════╝
     ✠ SUMMONING THE POINTS OF THE DAMNED ✠
*/

#define INFERNAL_X _uint256{0x79BE667E, 0xF9DCBBAC, 0x55A06295, 0xCE870B07, 0x029BFCDB, 0x2DCE28D9, 0x59F2815B, 0x16F81798}
#define INFERNAL_Y _uint256{0x483ADA77, 0x26A3C465, 0x5DA4FBFC, 0x0E1108A8, 0xFD17B448, 0xA6855419, 0x9C47D08F, 0xFB10D4B8}
#define INFERNAL_POINT CurvePoint{INFERNAL_X, INFERNAL_Y}

// Ритуал удвоения точки для вызова лямбды
_uint256 belial_point_double_lambda(CurvePoint p) {
    return cpu_mul_256_mod_p(
        cpu_mul_256_mod_p(_uint256{0, 0, 0, 0, 0, 0, 0, 3}, cpu_mul_256_mod_p(p.x, p.x)),
        cpu_eeuclid_256_mod_p(cpu_mul_256_mod_p(_uint256{0, 0, 0, 0, 0, 0, 0, 2}, p.y))
    );
}

// Ритуал сложения точек для вызова лямбды
_uint256 belial_point_add_lambda(CurvePoint p, CurvePoint q) {
    return cpu_mul_256_mod_p(
        cpu_sub_256_mod_p(q.y, p.y),
        cpu_eeuclid_256_mod_p(cpu_sub_256_mod_p(q.x, p.x))
    );
}

// Ритуал сложения двух точек под взором Белиала
CurvePoint belial_point_summon(CurvePoint p, CurvePoint q) {
    _uint256 lambda;
    if (eqeq_256(p.x, q.x)) {
        lambda = belial_point_double_lambda(p);
    } else {
        lambda = belial_point_add_lambda(p, q);
    }

    CurvePoint r;
    r.x = cpu_sub_256_mod_p(cpu_sub_256_mod_p(cpu_mul_256_mod_p(lambda, lambda), p.x), q.x);
    r.y = cpu_sub_256_mod_p(cpu_mul_256_mod_p(lambda, cpu_sub_256_mod_p(p.x, r.x)), p.y);
    return r;
}

// Ритуал умножения точки на скаляр под взором Асмодея
CurvePoint asmodeus_point_multiply(CurvePoint x, _uint256 y) {
    CurvePoint result;
    bool at_infinity = true;
    CurvePoint temp = x;

    for (int i = 0; i < 32; i++) {
        if ((y.h & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.g & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.f & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.e & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.d & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.c & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.b & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    for (int i = 0; i < 32; i++) {
        if ((y.a & (1ULL << i))) {
            at_infinity ? (result = temp) : (result = belial_point_summon(result, temp));
            at_infinity = false;
        }
        temp = belial_point_summon(temp, temp);
    }

    return result;
}