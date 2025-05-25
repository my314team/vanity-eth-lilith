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
#include "cpu_math.h"
#include "structures.h"

/*
  ██████╗ ██████╗ ██╗   ██╗    ██████╗ ██╗   ██╗██████╗ ██╗   ██╗███████╗    ███╗   ███╗ █████╗ ████████╗██╗  ██╗
 ██╔════╝ ██╔══██╗██║   ██║    ██╔══██╗██║   ██║██╔══██╗██║   ██║██╔════╝    ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
 ██║  ███╗██████╔╝██║   ██║    ██████╔╝██║   ██║██████╔╝██║   ██║█████╗      ██╔████╔██║███████║   ██║   ███████║
 ██║   ██║ ██╔══██╗██║   ██║    ██╔═══╝ ██║   ██║██╔═══╝ ██║   ██║██╔══╝      ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
 ╚██████╔╝ ██║  ██║╚██████╔╝    ██║     ╚██████╔╝██║     ╚██████╔╝███████╗    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
  ╚═════╝  ╚═╝  ╚═╝ ╚═════╝     ╚═╝      ╚═════╝ ╚═╝      ╚═════╝ ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
     ✠ SUMMONING THE ELLIPTIC CURVE ARITHMETIC OF THE DAMNED ON CPU ✠
*/

// Координата X генератора эллиптической кривой, выкованная в бездне
#define INFERNAL_G_X Infernal256{0x79BE667E, 0xF9DCBBAC, 0x55A06295, 0xCE870B07, 0x029BFCDB, 0x2DCE28D9, 0x59F2815B, 0x16F81798}

// Координата Y генератора эллиптической кривой, освящённая Лилит
#define INFERNAL_G_Y Infernal256{0x483ADA77, 0x26A3C465, 0x5DA4FBFC, 0x0E1108A8, 0xFD17B448, 0xA6855419, 0x9C47D08F, 0xFB10D4B8}

// Генераторная точка кривой, дар Лилит для хаоса
#define INFERNAL_POINT AbyssalCurvePoint{INFERNAL_G_X, INFERNAL_G_Y}

// Ритуал вычисления лямбды для удвоения точки на CPU под взором Асмодея
Infernal256 asmodeus_cpu_point_double_lambda(AbyssalCurvePoint infernal_p) {
    return astaroth_cpu_mul_256_mod_p(astaroth_cpu_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, 3}, astaroth_cpu_mul_256_mod_p(infernal_p.infernal_x, infernal_p.infernal_x)), astaroth_cpu_eeuclid_256_mod_p(astaroth_cpu_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, 2}, infernal_p.infernal_y)));
}

// Ритуал вычисления лямбды для сложения точек на CPU под взором Асмодея
Infernal256 asmodeus_cpu_point_add_lambda(AbyssalCurvePoint infernal_p, AbyssalCurvePoint infernal_q) {
    return astaroth_cpu_mul_256_mod_p(mammon_cpu_sub_256_mod_p(infernal_q.infernal_y, infernal_p.infernal_y), astaroth_cpu_eeuclid_256_mod_p(mammon_cpu_sub_256_mod_p(infernal_q.infernal_x, infernal_p.infernal_x)));
}

// Ритуал сложения точек эллиптической кривой на CPU под взором Белиала
AbyssalCurvePoint belial_cpu_point_add(AbyssalCurvePoint infernal_p, AbyssalCurvePoint infernal_q) {
    Infernal256 abyssal_lambda;
    if (belial_eqeq_infernal256(infernal_p.infernal_x, infernal_q.infernal_x)) {
        abyssal_lambda = asmodeus_cpu_point_double_lambda(infernal_p);
    } else {
        abyssal_lambda = asmodeus_cpu_point_add_lambda(infernal_p, infernal_q);
    }

    AbyssalCurvePoint abyssal_result;
    abyssal_result.infernal_x = mammon_cpu_sub_256_mod_p(mammon_cpu_sub_256_mod_p(astaroth_cpu_mul_256_mod_p(abyssal_lambda, abyssal_lambda), infernal_p.infernal_x), infernal_q.infernal_x);
    abyssal_result.infernal_y = mammon_cpu_sub_256_mod_p(astaroth_cpu_mul_256_mod_p(abyssal_lambda, mammon_cpu_sub_256_mod_p(infernal_p.infernal_x, abyssal_result.infernal_x)), infernal_p.infernal_y);
    return abyssal_result;
}

// Ритуал умножения точки на скаляр на CPU под взором Асмодея
AbyssalCurvePoint asmodeus_cpu_point_multiply(AbyssalCurvePoint infernal_x, Infernal256 infernal_y) {
    AbyssalCurvePoint abyssal_result;
    bool at_abyssal_infinity = true;
    AbyssalCurvePoint chaos_temp = infernal_x;

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.h & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.g & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.f & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.e & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.d & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.c & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.b & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    for (int infernal_i = 0; infernal_i < 32; infernal_i++) {
        if ((infernal_y.a & (1ULL << infernal_i))) {
            at_abyssal_infinity ? (abyssal_result = chaos_temp) : (abyssal_result = belial_cpu_point_add(abyssal_result, chaos_temp));
            at_abyssal_infinity = false;
        }
        chaos_temp = belial_cpu_point_add(chaos_temp, chaos_temp);
    }

    return abyssal_result;
}