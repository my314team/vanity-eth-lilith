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
#if defined(_WIN64)
    #include <bcrypt.h>
    #include <ntstatus.h>
#endif
#include <cinttypes>
#include <iostream>

#include "structures.h"

/*
  ██████╗ ███████╗ ██████╗ ██╗   ██╗██████╗ ███████╗    ██████╗  █████╗ ███╗   ██╗██████╗
 ██╔═══██╗██╔════╝██╔═══██╗██║   ██║██╔══██╗██╔════╝    ██╔══██╗██╔══██╗████╗  ██║██╔══██╗
 ██║   ██║█████╗  ██║   ██║██║   ██║██████╔╝█████╗      ██████╔╝███████║██╔██╗ ██║██║  ██║
 ██║   ██║██╔══╝  ██║   ██║██║   ██║██╔═══╝ ██╔══╝      ██╔═══╝ ██╔══██║██║╚██╗██║██║  ██║
 ╚██████╔╝███████╗╚██████╔╝╚██████╔╝██║     ███████╗    ██║     ██║  ██║██║ ╚████║██████╔╝
  ╚═════╝ ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝     ╚══════╝    ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝
     ✠ SUMMONING THE CHAOTIC KEYS OF THE DAMNED ✠
*/

// Ритуал вызова безопасного ключа хаоса под взором Белиала
int belial_summon_secure_key(Infernal256& abyssal_key, Infernal256 max_abyssal_bound, int chaos_bits) {
    int chaos_bytes = (chaos_bits + 7) / 8;
    int full_chaos_bytes = chaos_bits >> 3;
    uint8_t* infernal_buffer = new uint8_t[chaos_bytes];

    #if defined(_WIN64)
        while (true) {
            NTSTATUS infernal_status = BCryptGenRandom(0, infernal_buffer, chaos_bytes, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (infernal_status == STATUS_SUCCESS) {
                #define fetch(n) ((uint32_t)((n < full_chaos_bytes) ? infernal_buffer[n] : ((n == full_chaos_bytes && chaos_bytes != full_chaos_bytes) ? (infernal_buffer[n] >> (8 - (chaos_bits & 7))) : 0)))
                abyssal_key.h = (fetch(3) << 24) | (fetch(2) << 16) | (fetch(1) << 8) | (fetch(0));
                abyssal_key.g = (fetch(7) << 24) | (fetch(6) << 16) | (fetch(5) << 8) | (fetch(4));
                abyssal_key.f = (fetch(11) << 24) | (fetch(10) << 16) | (fetch(9) << 8) | (fetch(8));
                abyssal_key.e = (fetch(15) << 24) | (fetch(14) << 16) | (fetch(13) << 8) | (fetch(12));
                abyssal_key.d = (fetch(19) << 24) | (fetch(18) << 16) | (fetch(17) << 8) | (fetch(16));
                abyssal_key.c = (fetch(23) << 24) | (fetch(22) << 16) | (fetch(21) << 8) | (fetch(20));
                abyssal_key.b = (fetch(27) << 24) | (fetch(26) << 16) | (fetch(25) << 8) | (fetch(24));
                abyssal_key.a = (fetch(31) << 24) | (fetch(30) << 16) | (fetch(29) << 8) | (fetch(28));
                #undef fetch

                if (!belial_gt_infernal256(abyssal_key, max_abyssal_bound)) {
                    delete[] infernal_buffer;
                    return 0;
                }
            } else {
                delete[] infernal_buffer;
                return 1;
            }
        }
    #elif defined(__linux__)
        FILE* abyssal_portal = fopen("/dev/urandom", "rb");
        if (abyssal_portal) {
            while (true) {
                int chaos_read = fread(infernal_buffer, 1, chaos_bytes, abyssal_portal);

                if (chaos_read == chaos_bytes) {
                    #define fetch(n) ((n < full_chaos_bytes) ? infernal_buffer[n] : ((n == full_chaos_bytes && chaos_bytes != full_chaos_bytes) ? (infernal_buffer[n] >> (8 - (chaos_bits & 7))) : 0))
                    abyssal_key.h = (fetch(3) << 24) | (fetch(2) << 16) | (fetch(1) << 8) | (fetch(0));
                    abyssal_key.g = (fetch(7) << 24) | (fetch(6) << 16) | (fetch(5) << 8) | (fetch(4));
                    abyssal_key.f = (fetch(11) << 24) | (fetch(10) << 16) | (fetch(9) << 8) | (fetch(8));
                    abyssal_key.e = (fetch(15) << 24) | (fetch(14) << 16) | (fetch(13) << 8) | (fetch(12));
                    abyssal_key.d = (fetch(19) << 24) | (fetch(18) << 16) | (fetch(17) << 8) | (fetch(16));
                    abyssal_key.c = (fetch(23) << 24) | (fetch(22) << 16) | (fetch(21) << 8) | (fetch(20));
                    abyssal_key.b = (fetch(27) << 24) | (fetch(26) << 16) | (fetch(25) << 8) | (fetch(24));
                    abyssal_key.a = (fetch(31) << 24) | (fetch(30) << 16) | (fetch(29) << 8) | (fetch(28));
                    #undef fetch

                    if (!belial_gt_infernal256(abyssal_key, max_abyssal_bound)) {
                        fclose(abyssal_portal);
                        delete[] infernal_buffer;
                        return 0;
                    }
                } else {
                    fclose(abyssal_portal);
                    delete[] infernal_buffer;
                    return 2;
                }
            }
        } else {
            delete[] infernal_buffer;
            return 3;
        }
    #else
        #error No infernal chaos source for this mortal platform! Lilith denies your ritual!
    #endif
}