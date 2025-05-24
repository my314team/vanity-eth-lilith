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
#include "curve_math.h"

/*
  ██████╗ ██╗   ██╗██████╗ ██╗   ██╗███████╗
 ██╔═══██╗██║   ██║██╔══██╗██║   ██║██╔════╝
 ██║   ██║██║   ██║██████╔╝██║   ██║█████╗
 ██║   ██║██║   ██║██╔═══╝ ██║   ██║██╔══╝
 ╚██████╔╝╚██████╔╝██║     ╚██████╔╝███████╗
  ╚═════╝  ╚═════╝ ╚═╝      ╚═════╝ ╚══════╝
     ✠ SUMMONING THE POINTS OF THE DAMNED ✠
*/

// Ритуал удвоения точки для вызова лямбды
Infernal256 belial_point_double_lambda(AbyssalCurvePoint p) {
    return belial_mul_256_mod_p(
        belial_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, 3}, belial_mul_256_mod_p(p.x, p.x)),
        belial_eeuclid_256_mod_p(belial_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, 2}, p.y))
    );
}

// Ритуал сложения точек для вызова лямбды
Infernal256 belial_point_add_lambda(AbyssalCurvePoint p, AbyssalCurvePoint q) {
    return belial_mul_256_mod_p(
        aamon_sub_256_mod_p(q.y, p.y),
        belial_eeuclid_256_mod_p(aamon_sub_256_mod_p(q.x, p.x))
    );
}

// Ритуал сложения двух точек под взором Белиала
AbyssalCurvePoint belial_point_summon(AbyssalCurvePoint p, AbyssalCurvePoint q) {
    Infernal256 lambda;
    if (belial_eqeq_infernal256(p.x, q.x)) {
        lambda = belial_point_double_lambda(p);
    } else {
        lambda = belial_point_add_lambda(p, q);
    }

    AbyssalCurvePoint r;
    r.x = aamon_sub_256_mod_p(aamon_sub_256_mod_p(belial_mul_256_mod_p(lambda, lambda), p.x), q.x);
    r.y = aamon_sub_256_mod_p(belial_mul_256_mod_p(lambda, aamon_sub_256_mod_p(p.x, r.x)), p.y);
    return r;
}

// Ритуал умножения точки на скаляр под взором Асмодея
AbyssalCurvePoint asmodeus_point_multiply(AbyssalCurvePoint x, Infernal256 y) {
    AbyssalCurvePoint result;
    bool at_infinity = true;
    AbyssalCurvePoint temp = x;

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