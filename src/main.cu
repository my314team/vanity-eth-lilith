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

#if defined(_WIN64)
    #define WIN32_NO_STATUS
    #include <windows.h>
    #undef WIN32_NO_STATUS
#else
    #include <unistd.h> // Для Linux (usleep)
#endif

#include <thread>
#include <cinttypes>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <chrono>
#include <fstream>
#include <vector>
#include <cmath> // Для вероятности

#include "secure_rand.h"
#include "structures.h"
#include "cpu_curve_math.h"
#include "cpu_keccak.h"
#include "cpu_math.h"

#define INFERNAL_BUFFER_SIZE 10000
#define ABYSSAL_BLOCK_SIZE 256U
#define THREAD_PACT (1U << 8)

// Глобальные константы CUDA в бездне
__constant__ AbyssalCurvePoint infernal_thread_gates[ABYSSAL_BLOCK_SIZE];
__constant__ AbyssalCurvePoint infernal_addends[THREAD_PACT - 1];
__device__ uint64_t infernal_abyss[2 + INFERNAL_BUFFER_SIZE * 3];

/*
  ██████╗ ██╗████████╗██╗   ██╗ █████╗ ██╗
 ██╔═══██╗██║╚══██╔══╝██║   ██║██╔══██╗██║
 ██║   ██║██║   ██║   ██║   ██║███████║██║
 ██║   ██║██║   ██║   ██║   ██║██╔══██║██║
 ╚██████╔╝██║   ██║   ╚██████╔╝██║  ██║███████╗
  ╚═════╝ ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝
     ✠ SUMMONING THE ADDRESSES OF THE DAMNED ✠
*/

// ANSI-коды для адских цветов
#define ANSI_RED "\033[31m"
#define ANSI_PURPLE "\033[35m"
#define ANSI_RESET "\033[0m"

// Ритуал подсчёта нулевых байтов под взором Аамона 🖤
__device__ int aamon_count_zero_bytes(uint32_t x) {
    int n = 0;
    n += ((x & 0xFF) == 0);
    n += ((x & 0xFF00) == 0);
    n += ((x & 0xFF0000) == 0);
    n += ((x & 0xFF000000) == 0);
    return n;
}

// Ритуал оценки нулевых байтов в адресе 🖤
__device__ int aamon_score_zero_bytes(InfernalAddress a) {
    int n = 0;
    n += aamon_count_zero_bytes(a.a);
    n += aamon_count_zero_bytes(a.b);
    n += aamon_count_zero_bytes(a.c);
    n += aamon_count_zero_bytes(a.d);
    n += aamon_count_zero_bytes(a.e);
    return n;
}

// Ритуал оценки ведущих нулей в адресе 🖤
__device__ int aamon_score_leading_zeros(InfernalAddress a) {
    int n = __clz(a.a);
    if (n == 32) {
        n += __clz(a.b);
        if (n == 64) {
            n += __clz(a.c);
            if (n == 96) {
                n += __clz(a.d);
                if (n == 128) {
                    n += __clz(a.e);
                }
            }
        }
    }
    return n >> 3;
}

#ifdef __linux__
    #define atomicMax_ul(a, b) atomicMax((unsigned long long*)(a), (unsigned long long)(b))
    #define atomicAdd_ul(a, b) atomicAdd((unsigned long long*)(a), (unsigned long long)(b))
#else
    #define atomicMax_ul(a, b) atomicMax(a, b)
    #define atomicAdd_ul(a, b) atomicAdd(a, b)
#endif

// Ритуал записи результата в адский буфер 🔥
__device__ void belial_handle_output(int soul_score_ritual, InfernalAddress a, uint64_t key, bool inv) {
    int score = 0;
    if (soul_score_ritual == 0) { score = aamon_score_leading_zeros(a); }
    else if (soul_score_ritual == 1) { score = aamon_score_zero_bytes(a); }

    if (score >= infernal_abyss[1]) {
        atomicMax_ul(&infernal_abyss[1], score);
        if (score >= infernal_abyss[1]) {
            uint32_t idx = atomicAdd_ul(&infernal_abyss[0], 1);
            if (idx < INFERNAL_BUFFER_SIZE) {
                infernal_abyss[2 + idx] = key;
                infernal_abyss[INFERNAL_BUFFER_SIZE + 2 + idx] = score;
                infernal_abyss[INFERNAL_BUFFER_SIZE * 2 + 2 + idx] = inv;
            }
        }
    }
}

// Ритуал записи результата для контрактов 🔥
__device__ void belial_handle_output2(int soul_score_ritual, InfernalAddress a, uint64_t key) {
    int score = 0;
    if (soul_score_ritual == 0) { score = aamon_score_leading_zeros(a); }
    else if (soul_score_ritual == 1) { score = aamon_score_zero_bytes(a); }

    if (score >= infernal_abyss[1]) {
        atomicMax_ul(&infernal_abyss[1], score);
        if (score >= infernal_abyss[1]) {
            uint32_t idx = atomicAdd_ul(&infernal_abyss[0], 1);
            if (idx < INFERNAL_BUFFER_SIZE) {
                infernal_abyss[2 + idx] = key;
                infernal_abyss[INFERNAL_BUFFER_SIZE + 2 + idx] = score;
            }
        }
    }
}

#include "address.h"
#include "contract_address.h"
#include "contract_address2.h"
#include "contract_address3.h"

int global_max_soul_score = 0;
std::mutex global_max_soul_score_mutex;
uint32_t INFERNAL_GRID_SIZE = 1U << 15;

struct InfernalMessage {
    uint64_t time;
    int status;
    int demon_index;
    cudaError_t error;
    double speed;
    int souls_count;
    Infernal256* souls;
    int* soul_scores;
};

std::queue<InfernalMessage> infernal_message_queue;
std::mutex infernal_message_queue_mutex;

#define gpu_summon_assert(call) { \
    cudaError_t e = call; \
    if (e != cudaSuccess) { \
        infernal_message_queue_mutex.lock(); \
        infernal_message_queue.push(InfernalMessage{milliseconds(), 1, demon_index, e}); \
        infernal_message_queue_mutex.unlock(); \
        if (thread_gates_host != 0) { cudaFreeHost(thread_gates_host); } \
        if (infernal_abyss_host != 0) { cudaFreeHost(infernal_abyss_host); } \
        cudaDeviceReset(); \
        return; \
    } \
}

uint64_t milliseconds() {
    return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
}

// Ритуал вызова демонов для добычи ключей хаоса 🖤
void asmodeus_host_ritual(int demon_id, int demon_index, int soul_score_ritual, int mode, InfernalAddress origin_gate, InfernalAddress deployer_gate, Infernal256 abyssal_bytecode) {
    uint64_t GRID_PACT = ((uint64_t)ABYSSAL_BLOCK_SIZE * (uint64_t)INFERNAL_GRID_SIZE * (uint64_t)THREAD_PACT);

    AbyssalCurvePoint* block_gates = 0;
    AbyssalCurvePoint* offsets = 0;
    AbyssalCurvePoint* thread_gates_host = 0;

    uint64_t* infernal_abyss_host = 0;
    uint64_t* max_soul_score_host;
    uint64_t* soul_counter_host;
    uint64_t* soul_buffer_host;
    uint64_t* soul_score_buffer_host;
    uint64_t* soul_inv_buffer_host;

    gpu_summon_assert(cudaSetDevice(demon_id));

    gpu_summon_assert(cudaHostAlloc(&infernal_abyss_host, (2 + INFERNAL_BUFFER_SIZE * 3) * sizeof(uint64_t), cudaHostAllocDefault));
    soul_counter_host = infernal_abyss_host;
    max_soul_score_host = infernal_abyss_host + 1;
    soul_buffer_host = max_soul_score_host + 1;
    soul_score_buffer_host = soul_buffer_host + INFERNAL_BUFFER_SIZE;
    soul_inv_buffer_host = soul_score_buffer_host + INFERNAL_BUFFER_SIZE;

    soul_counter_host[0] = 0;
    max_soul_score_host[0] = 2;
    gpu_summon_assert(cudaMemcpyToSymbol(infernal_abyss, infernal_abyss_host, 2 * sizeof(uint64_t)));
    gpu_summon_assert(cudaDeviceSynchronize());

    if (mode == 0 || mode == 1) {
        gpu_summon_assert(cudaMalloc(&block_gates, INFERNAL_GRID_SIZE * sizeof(AbyssalCurvePoint)));
        gpu_summon_assert(cudaMalloc(&offsets, (uint64_t)INFERNAL_GRID_SIZE * ABYSSAL_BLOCK_SIZE * sizeof(AbyssalCurvePoint)));
        thread_gates_host = new AbyssalCurvePoint[ABYSSAL_BLOCK_SIZE];
        gpu_summon_assert(cudaHostAlloc(&thread_gates_host, ABYSSAL_BLOCK_SIZE * sizeof(AbyssalCurvePoint), cudaHostAllocWriteCombined));
    }

    Infernal256 max_abyssal_key;
    if (mode == 0 || mode == 1) {
        Infernal256 GRID_PACT = mammon_mul_256_mod_p(mammon_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT}, Infernal256{0, 0, 0, 0, 0, 0, 0, ABYSSAL_BLOCK_SIZE}), Infernal256{0, 0, 0, 0, 0, 0, 0, INFERNAL_GRID_SIZE});
        max_abyssal_key = Infernal256{0x7FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x5D576E73, 0x57A4501D, 0xDFE92F46, 0x681B20A0};
        max_abyssal_key = mammon_sub_256(max_abyssal_key, GRID_PACT);
        max_abyssal_key = mammon_sub_256(max_abyssal_key, Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT});
        max_abyssal_key = mammon_add_256(max_abyssal_key, Infernal256{0, 0, 0, 0, 0, 0, 0, 2});
    } else if (mode == 2 || mode == 3) {
        max_abyssal_key = Infernal256{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    }

    Infernal256 base_abyssal_key{0, 0, 0, 0, 0, 0, 0, 0};
    Infernal256 abyssal_key_increment{0, 0, 0, 0, 0, 0, 0, 0};
    int status;
    if (mode == 0 || mode == 1) {
        status = belial_summon_secure_key(base_abyssal_key, max_abyssal_key, 255);
        abyssal_key_increment = mammon_mul_256_mod_p(mammon_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, ABYSSAL_BLOCK_SIZE}, Infernal256{0, 0, 0, 0, 0, 0, 0, INFERNAL_GRID_SIZE}), Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT});
    } else if (mode == 2 || mode == 3) {
        status = belial_summon_secure_key(base_abyssal_key, max_abyssal_key, 256);
        abyssal_key_increment = mammon_mul_256_mod_p(mammon_mul_256_mod_p(Infernal256{0, 0, 0, 0, 0, 0, 0, ABYSSAL_BLOCK_SIZE}, Infernal256{0, 0, 0, 0, 0, 0, 0, INFERNAL_GRID_SIZE}), Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT});
        base_abyssal_key.h &= ~(THREAD_PACT - 1);
    }

    if (status) {
        infernal_message_queue_mutex.lock();
        infernal_message_queue.push(InfernalMessage{milliseconds(), 10 + status});
        infernal_message_queue_mutex.unlock();
        return;
    }
    Infernal256 abyssal_key = base_abyssal_key;

    if (mode == 0 || mode == 1) {
        AbyssalCurvePoint* addends_host = new AbyssalCurvePoint[THREAD_PACT - 1];
        AbyssalCurvePoint p = INFERNAL_POINT;
        for (int i = 0; i < THREAD_PACT - 1; i++) {
            addends_host[i] = p;
            p = belial_point_summon(p, INFERNAL_POINT);
        }
        gpu_summon_assert(cudaMemcpyToSymbol(infernal_addends, addends_host, (THREAD_PACT - 1) * sizeof(AbyssalCurvePoint)));
        delete[] addends_host;

        AbyssalCurvePoint* block_gates_host = new AbyssalCurvePoint[INFERNAL_GRID_SIZE];
        AbyssalCurvePoint block_offset = asmodeus_point_multiply(INFERNAL_POINT, Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT * ABYSSAL_BLOCK_SIZE});
        p = INFERNAL_POINT;
        for (int i = 0; i < INFERNAL_GRID_SIZE; i++) {
            block_gates_host[i] = p;
            p = belial_point_summon(p, block_offset);
        }
        gpu_summon_assert(cudaMemcpy(block_gates, block_gates_host, INFERNAL_GRID_SIZE * sizeof(AbyssalCurvePoint), cudaMemcpyHostToDevice));
        delete[] block_gates_host;
    }

    if (mode == 0 || mode == 1) {
        cudaStream_t streams[2];
        gpu_summon_assert(cudaStreamCreate(&streams[0]));
        gpu_summon_assert(cudaStreamCreate(&streams[1]));

        Infernal256 previous_abyssal_key = abyssal_key;
        bool first_ritual = true;
        uint64_t start_time;
        uint64_t end_time;
        double elapsed;

        while (true) {
            if (!first_ritual) {
                if (mode == 0) {
                    belial_address_harvest<<<INFERNAL_GRID_SIZE, ABYSSAL_BLOCK_SIZE, 0, streams[0]>>>(soul_score_ritual, offsets);
                } else {
                    belial_contract_harvest<<<INFERNAL_GRID_SIZE, ABYSSAL_BLOCK_SIZE, 0, streams[0]>>>(soul_score_ritual, offsets);
                }
            }

            if (!first_ritual) {
                previous_abyssal_key = abyssal_key;
                abyssal_key = mammon_add_256(abyssal_key, abyssal_key_increment);
                if (belial_gte_infernal256(abyssal_key, max_abyssal_key)) {
                    abyssal_key = mammon_sub_256(abyssal_key, max_abyssal_key);
                }
            }
            AbyssalCurvePoint thread_offset = asmodeus_point_multiply(INFERNAL_POINT, Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT});
            AbyssalCurvePoint p = asmodeus_point_multiply(INFERNAL_POINT, mammon_add_256(Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT - 1}, abyssal_key));
            for (int i = 0; i < ABYSSAL_BLOCK_SIZE; i++) {
                thread_gates_host[i] = p;
                p = belial_point_summon(p, thread_offset);
            }
            gpu_summon_assert(cudaMemcpyToSymbolAsync(infernal_thread_gates, thread_gates_host, ABYSSAL_BLOCK_SIZE * sizeof(AbyssalCurvePoint), 0, cudaMemcpyHostToDevice, streams[1]));
            gpu_summon_assert(cudaStreamSynchronize(streams[1]));
            gpu_summon_assert(cudaStreamSynchronize(streams[0]));

            if (!first_ritual) {
                end_time = milliseconds();
                elapsed = (end_time - start_time) / 1000.0;
            }
            start_time = milliseconds();

            aamon_address_summon<<<INFERNAL_GRID_SIZE/ABYSSAL_BLOCK_SIZE, ABYSSAL_BLOCK_SIZE, 0, streams[0]>>>(block_gates, offsets);
            if (!first_ritual) {
                gpu_summon_assert(cudaMemcpyFromSymbolAsync(infernal_abyss_host, infernal_abyss, (2 + INFERNAL_BUFFER_SIZE * 3) * sizeof(uint64_t), 0, cudaMemcpyDeviceToHost, streams[1]));
                gpu_summon_assert(cudaStreamSynchronize(streams[1]));
            }
            if (!first_ritual) {
                global_max_soul_score_mutex.lock();
                if (soul_counter_host[0] != 0) {
                    if (max_soul_score_host[0] > global_max_soul_score) {
                        global_max_soul_score = max_soul_score_host[0];
                    } else {
                        max_soul_score_host[0] = global_max_soul_score;
                    }
                }
                global_max_soul_score_mutex.unlock();

                double speed = GRID_PACT / elapsed / 1000000.0 * 2;
                if (soul_counter_host[0] != 0) {
                    int valid_souls = 0;

                    for (int i = 0; i < soul_counter_host[0]; i++) {
                        if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }
                        valid_souls++;
                    }

                    if (valid_souls > 0) {
                        Infernal256* souls = new Infernal256[valid_souls];
                        int* soul_scores = new int[valid_souls];
                        valid_souls = 0;

                        for (int i = 0; i < soul_counter_host[0]; i++) {
                            if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }

                            uint64_t k_offset = soul_buffer_host[i];
                            Infernal256 k = mammon_add_256(previous_abyssal_key, mammon_add_256(Infernal256{0, 0, 0, 0, 0, 0, 0, THREAD_PACT}, Infernal256{0, 0, 0, 0, 0, 0, (uint32_t)(k_offset >> 32), (uint32_t)(k_offset & 0xFFFFFFFF)}));

                            if (soul_inv_buffer_host[i]) {
                                k = mammon_sub_256(INFERNAL_N, k);
                            }

                            int idx = valid_souls++;
                            souls[idx] = k;
                            soul_scores[idx] = soul_score_buffer_host[i];
                        }

                        infernal_message_queue_mutex.lock();
                        infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, valid_souls, souls, soul_scores});
                        infernal_message_queue_mutex.unlock();
                    } else {
                        infernal_message_queue_mutex.lock();
                        infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                        infernal_message_queue_mutex.unlock();
                    }
                } else {
                    infernal_message_queue_mutex.lock();
                    infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                    infernal_message_queue_mutex.unlock();
                }
            }

            if (!first_ritual) {
                soul_counter_host[0] = 0;
                gpu_summon_assert(cudaMemcpyToSymbolAsync(infernal_abyss, infernal_abyss_host, sizeof(uint64_t), 0, cudaMemcpyHostToDevice, streams[1]));
                gpu_summon_assert(cudaStreamSynchronize(streams[1]));
            }
            gpu_summon_assert(cudaStreamSynchronize(streams[0]));
            first_ritual = false;
        }
    }

    if (mode == 2) {
        while (true) {
            uint64_t start_time = milliseconds();
            astaroth_contract2_harvest<<<INFERNAL_GRID_SIZE, ABYSSAL_BLOCK_SIZE>>>(soul_score_ritual, origin_gate, abyssal_key, abyssal_bytecode);

            gpu_summon_assert(cudaDeviceSynchronize());
            gpu_summon_assert(cudaMemcpyFromSymbol(infernal_abyss_host, infernal_abyss, (2 + INFERNAL_BUFFER_SIZE * 3) * sizeof(uint64_t)));

            uint64_t end_time = milliseconds();
            double elapsed = (end_time - start_time) / 1000.0;

            global_max_soul_score_mutex.lock();
            if (soul_counter_host[0] != 0) {
                if (max_soul_score_host[0] > global_max_soul_score) {
                    global_max_soul_score = max_soul_score_host[0];
                } else {
                    max_soul_score_host[0] = global_max_soul_score;
                }
            }
            global_max_soul_score_mutex.unlock();

            double speed = GRID_PACT / elapsed / 1000000.0;
            if (soul_counter_host[0] != 0) {
                int valid_souls = 0;

                for (int i = 0; i < soul_counter_host[0]; i++) {
                    if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }
                    valid_souls++;
                }

                if (valid_souls > 0) {
                    Infernal256* souls = new Infernal256[valid_souls];
                    int* soul_scores = new int[valid_souls];
                    valid_souls = 0;

                    for (int i = 0; i < soul_counter_host[0]; i++) {
                        if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }

                        uint64_t k_offset = soul_buffer_host[i];
                        Infernal256 k = mammon_add_256(abyssal_key, Infernal256{0, 0, 0, 0, 0, 0, (uint32_t)(k_offset >> 32), (uint32_t)(k_offset & 0xFFFFFFFF)});

                        int idx = valid_souls++;
                        souls[idx] = k;
                        soul_scores[idx] = soul_score_buffer_host[i];
                    }

                    infernal_message_queue_mutex.lock();
                    infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, valid_souls, souls, soul_scores});
                    infernal_message_queue_mutex.unlock();
                } else {
                    infernal_message_queue_mutex.lock();
                    infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                    infernal_message_queue_mutex.unlock();
                }
            } else {
                infernal_message_queue_mutex.lock();
                infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                infernal_message_queue_mutex.unlock();
            }

            abyssal_key = mammon_add_256(abyssal_key, abyssal_key_increment);

            soul_counter_host[0] = 0;
            gpu_summon_assert(cudaMemcpyToSymbol(infernal_abyss, infernal_abyss_host, sizeof(uint64_t)));
        }
    }

    if (mode == 3) {
        while (true) {
            uint64_t start_time = milliseconds();
            beelzebub_contract3_harvest<<<INFERNAL_GRID_SIZE, ABYSSAL_BLOCK_SIZE>>>(soul_score_ritual, origin_gate, deployer_gate, abyssal_key, abyssal_bytecode);

            gpu_summon_assert(cudaDeviceSynchronize());
            gpu_summon_assert(cudaMemcpyFromSymbol(infernal_abyss_host, infernal_abyss, (2 + INFERNAL_BUFFER_SIZE * 3) * sizeof(uint64_t)));

            uint64_t end_time = milliseconds();
            double elapsed = (end_time - start_time) / 1000.0;

            global_max_soul_score_mutex.lock();
            if (soul_counter_host[0] != 0) {
                if (max_soul_score_host[0] > global_max_soul_score) {
                    global_max_soul_score = max_soul_score_host[0];
                } else {
                    max_soul_score_host[0] = global_max_soul_score;
                }
            }
            global_max_soul_score_mutex.unlock();

            double speed = GRID_PACT / elapsed / 1000000.0;
            if (soul_counter_host[0] != 0) {
                int valid_souls = 0;

                for (int i = 0; i < soul_counter_host[0]; i++) {
                    if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }
                    valid_souls++;
                }

                if (valid_souls > 0) {
                    Infernal256* souls = new Infernal256[valid_souls];
                    int* soul_scores = new int[valid_souls];
                    valid_souls = 0;

                    for (int i = 0; i < soul_counter_host[0]; i++) {
                        if (soul_score_buffer_host[i] < max_soul_score_host[0]) { continue; }

                        uint64_t k_offset = soul_buffer_host[i];
                        Infernal256 k = mammon_add_256(abyssal_key, Infernal256{0, 0, 0, 0, 0, 0, (uint32_t)(k_offset >> 32), (uint32_t)(k_offset & 0xFFFFFFFF)});

                        int idx = valid_souls++;
                        souls[idx] = k;
                        soul_scores[idx] = soul_score_buffer_host[i];
                    }

                    infernal_message_queue_mutex.lock();
                    infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, valid_souls, souls, soul_scores});
                    infernal_message_queue_mutex.unlock();
                } else {
                    infernal_message_queue_mutex.lock();
                    infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                    infernal_message_queue_mutex.unlock();
                }
            } else {
                infernal_message_queue_mutex.lock();
                infernal_message_queue.push(InfernalMessage{end_time, 0, demon_index, cudaSuccess, speed, 0});
                infernal_message_queue_mutex.unlock();
            }

            abyssal_key = mammon_add_256(abyssal_key, abyssal_key_increment);

            soul_counter_host[0] = 0;
            gpu_summon_assert(cudaMemcpyToSymbol(infernal_abyss, infernal_abyss_host, sizeof(uint64_t)));
        }
    }
}

// Ритуал отображения скорости демонов с адским пламенем 🔥
void asmodeus_print_speeds(int num_demons, int* demon_ids, double* infernal_speeds) {
    double total = 0.0;
    for (int i = 0; i < num_demons; i++) {
        total += infernal_speeds[i];
    }
    printf("%s🌑 Total Infernal Power: %.2fM/s%s", ANSI_PURPLE, total, ANSI_RESET);
    for (int i = 0; i < num_demons; i++) {
        printf(" | %sDemon %d: %.2fM/s%s", ANSI_RED, demon_ids[i], infernal_speeds[i], ANSI_RESET);
    }
}

// Главный ритуал вызова Лилит с адским эффектом 🖤💀
int main(int argc, char *argv[]) {
    int soul_score_ritual = -1; // 0 = ведущие нули, 1 = нули
    int mode = 0; // 0 = адрес, 1 = контракт, 2 = контракт CREATE2, 3 = прокси-контракт CREATE3
    char* infernal_tome = 0;
    char* origin_gate_input = 0;
    char* deployer_gate_input = 0;
    int min_soul_score = 4; // Минимальный Power для вывода душ

    int num_demons = 0;
    int demon_ids[10];

    for (int i = 1; i < argc;) {
        if (strcmp(argv[i], "--device") == 0 || strcmp(argv[i], "-d") == 0) {
            demon_ids[num_demons++] = atoi(argv[i + 1]);
            i += 2;
        } else if (strcmp(argv[i], "--leading-zeros") == 0 || strcmp(argv[i], "-lz") == 0) {
            soul_score_ritual = 0;
            i++;
        } else if (strcmp(argv[i], "--zeros") == 0 || strcmp(argv[i], "-z") == 0) {
            soul_score_ritual = 1;
            i++;
        } else if (strcmp(argv[i], "--contract") == 0 || strcmp(argv[i], "-c") == 0) {
            mode = 1;
            i++;
        } else if (strcmp(argv[i], "--contract2") == 0 || strcmp(argv[i], "-c2") == 0) {
            mode = 2;
            i++;
        } else if (strcmp(argv[i], "--contract3") == 0 || strcmp(argv[i], "-c3") == 0) {
            mode = 3;
            i++;
        } else if (strcmp(argv[i], "--bytecode") == 0 || strcmp(argv[i], "-b") == 0) {
            infernal_tome = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "--address") == 0 || strcmp(argv[i], "-a") == 0) {
            origin_gate_input = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "--deployer-address") == 0 || strcmp(argv[i], "-da") == 0) {
            deployer_gate_input = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "--work-scale") == 0 || strcmp(argv[i], "-w") == 0) {
            INFERNAL_GRID_SIZE = 1U << atoi(argv[i + 1]);
            i += 2;
        } else if (strcmp(argv[i], "--min-score") == 0) {
            min_soul_score = atoi(argv[i + 1]);
            i += 2;
        } else {
            i++;
        }
    }

    if (num_demons == 0) {
        printf("\r%s💀 No demons answered Lilith’s call! Abyssal ritual failed! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    if (soul_score_ritual == -1) {
        printf("\r%s💀 No soul-scoring ritual chosen! The void hungers! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    if (mode == 2 && !infernal_tome) {
        printf("\r%s💀 Infernal bytecode required for CREATE2 summoning! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    if ((mode == 2 || mode == 3) && !origin_gate_input) {
        printf("\r%s💀 Origin gate must be forged for CREATE2 or CREATE3! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    } else if ((mode == 2 || mode == 3) && strlen(origin_gate_input) != 40 && strlen(origin_gate_input) != 42) {
        printf("\r%s💀 Origin gate must bear 40 runes of chaos! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    if (mode == 3 && !deployer_gate_input) {
        printf("\r%s💀 Deployer gate required for CREATE3 ritual! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    } else if (mode == 3 && strlen(deployer_gate_input) != 40 && strlen(deployer_gate_input) != 42) {
        printf("\r%s💀 Deployer gate must bear 40 runes of chaos! 🖤%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    for (int i = 0; i < num_demons; i++) {
        cudaError_t e = cudaSetDevice(demon_ids[i]);
        if (e != cudaSuccess) {
            printf("\r%s💀 Demon %d resists summoning! Chaos reigns with code %d! 🖤%s\n", ANSI_RED, demon_ids[i], e, ANSI_RESET);
            return 1;
        }
    }

    #define nothex(n) ((n < 48 || n > 57) && (n < 65 || n > 70) && (n < 97 || n > 102))
    Infernal256 abyssal_bytecode_hash;
    if (mode == 2 || mode == 3) {
        std::ifstream infile(infernal_tome, std::ios::binary);
        if (!infile.is_open()) {
            printf("\r%s💀 Abyssal tome of bytecode could not be opened! 🖤%s\n", ANSI_RED, ANSI_RESET);
            return 1;
        }

        int tome_size = 0;
        {
            infile.seekg(0, std::ios::end);
            std::streampos tome_size_ = infile.tellg();
            infile.seekg(0, std::ios::beg);
            tome_size = tome_size_ - infile.tellg();
        }

        if (tome_size & 1) {
            printf("\r%s💀 Bytecode corrupted by infernal forces! 🖤%s\n", ANSI_RED, ANSI_RESET);
            return 1;
        }

        uint8_t* bytecode = new uint8_t[24576];
        if (bytecode == 0) {
            printf("\r%s💀 Memory abyss consumed by darkness! Out of space! 🖤%s\n", ANSI_RED, ANSI_RESET);
            return 1;
        }

        char byte[2];
        bool prefix = false;
        for (int i = 0; i < (tome_size >> 1); i++) {
            infile.read((char*)&byte, 2);
            if (i == 0) {
                prefix = byte[0] == '0' && byte[1] == 'x';
                if ((tome_size >> 1) > (prefix ? 24577 : 24576)) {
                    printf("\r%s💀 Bytecode exceeds infernal limits! 🖤%s\n", ANSI_RED, ANSI_RESET);
                    delete[] bytecode;
                    return 1;
                }
                if (prefix) { continue; }
            }

            if (nothex(byte[0]) || nothex(byte[1])) {
                printf("\r%s💀 Bytecode bears forbidden runes! 🖤%s\n", ANSI_RED, ANSI_RESET);
                delete[] bytecode;
                return 1;
            }

            bytecode[i - prefix] = (uint8_t)strtol(byte, 0, 16);
        }
        abyssal_bytecode_hash = aamon_full_keccak(bytecode, (tome_size >> 1) - prefix);
        delete[] bytecode;
    }

    InfernalAddress origin_gate;
    if (mode == 2 || mode == 3) {
        if (strlen(origin_gate_input) == 42) {
            origin_gate_input += 2;
        }
        char substr[9];

        #define round(i, offset) \
        strncpy(substr, origin_gate_input + offset * 8, 8); \
        if (nothex(substr[0]) || nothex(substr[1]) || nothex(substr[2]) || nothex(substr[3]) || nothex(substr[4]) || nothex(substr[5]) || nothex(substr[6]) || nothex(substr[7])) { \
            printf("\r%s💀 Origin gate tainted by mortal error! 🖤%s\n", ANSI_RED, ANSI_RESET); \
            return 1; \
        } \
        origin_gate.i = strtoull(substr, 0, 16);

        round(a, 0)
        round(b, 1)
        round(c, 2)
        round(d, 3)
        round(e, 4)

        #undef round
    }

    InfernalAddress deployer_gate;
    if (mode == 3) {
        if (strlen(deployer_gate_input) == 42) {
            deployer_gate_input += 2;
        }
        char substr[9];

        #define round(i, offset) \
        strncpy(substr, deployer_gate_input + offset * 8, 8); \
        if (nothex(substr[0]) || nothex(substr[1]) || nothex(substr[2]) || nothex(substr[3]) || nothex(substr[4]) || nothex(substr[5]) || nothex(substr[6]) || nothex(substr[7])) { \
            printf("\r%s💀 Deployer gate corrupted by abyssal forces! 🖤%s\n", ANSI_RED, ANSI_RESET); \
            return 1; \
        } \
        deployer_gate.i = strtoull(substr, 0, 16);

        round(a, 0)
        round(b, 1)
        round(c, 2)
        round(d, 3)
        round(e, 4)

        #undef round
    }
    #undef nothex

    // Инициализация адского ритуала 💀
    std::vector<std::thread> demonic_threads;
    uint64_t global_start_time = milliseconds();
    uint64_t total_keys_checked = 0;
    uint64_t last_progress_time = global_start_time;
    int progress_cycle = 0;
    const char* progress_indicators[] = {"🩸", "💉", "🪦", "⚰️"}; // Анимация прогресса
    int found_souls = 0; // Счётчик найденных душ

    for (int i = 0; i < num_demons; i++) {
        std::thread th(asmodeus_host_ritual, demon_ids[i], i, soul_score_ritual, mode, origin_gate, deployer_gate, abyssal_bytecode_hash);
        demonic_threads.push_back(std::move(th));
    }

    // Начало ритуала с анимацией 💀
    printf("\r%s🔥 Lilith awakens! Forging abyssal keys with %d demons... %s%s\n", ANSI_PURPLE, num_demons, progress_indicators[progress_cycle], ANSI_RESET);
    fflush(stdout);

    double infernal_speeds[100];
    while (true) {
        infernal_message_queue_mutex.lock();
        bool queue_empty = infernal_message_queue.empty();
        infernal_message_queue_mutex.unlock();

        if (queue_empty) {
            // Обновление прогресса каждые 0.5 секунды
            uint64_t current_time = milliseconds();
            if (current_time - last_progress_time >= 500) {
                progress_cycle = (progress_cycle + 1) % 4;
                double elapsed_seconds = (current_time - global_start_time) / 1000.0;
                double keys_per_second = (elapsed_seconds > 0) ? (total_keys_checked / elapsed_seconds) / 1000000.0 : 0;
                double chaos_probability = (soul_score_ritual == 0) ? (total_keys_checked / pow(2, global_max_soul_score * 8)) * 100 : 0; // Вероятность для leading-zeros
                printf("\r%s%s Forging: %lluM keys | Speed: %.2fM/s | Souls: %d | Chaos: %.2f%% %s%s",
                       ANSI_PURPLE, progress_indicators[progress_cycle], total_keys_checked / 1000000, keys_per_second, found_souls, chaos_probability, ANSI_RED, ANSI_RESET);
                asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                last_progress_time = current_time;
                fflush(stdout);
                usleep(100000); // 100ms пауза для анимации
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
            infernal_message_queue_mutex.lock();
            while (!infernal_message_queue.empty()) {
                InfernalMessage m = infernal_message_queue.front();
                infernal_message_queue.pop();

                int demon_index = m.demon_index;

                if (m.status == 0) {
                    infernal_speeds[demon_index] = m.speed;
                    total_keys_checked += (uint64_t)(GRID_PACT * 2); // Учёт проверенных ключей

                    if (m.souls_count != 0) {
                        InfernalAddress* gates = new InfernalAddress[m.souls_count];
                        for (int i = 0; i < m.souls_count; i++) {
                            if (mode == 0) {
                                AbyssalCurvePoint p = asmodeus_point_multiply(INFERNAL_POINT, m.souls[i]);
                                gates[i] = aamon_calculate_address_cpu(p.x, p.y);
                            } else if (mode == 1) {
                                AbyssalCurvePoint p = asmodeus_point_multiply(INFERNAL_POINT, m.souls[i]);
                                gates[i] = aamon_calculate_contract_address_cpu(aamon_calculate_address_cpu(p.x, p.y));
                            } else if (mode == 2) {
                                gates[i] = aamon_calculate_contract_address2_cpu(origin_gate, m.souls[i], abyssal_bytecode_hash);
                            } else if (mode == 3) {
                                Infernal256 salt = aamon_calculate_create3_salt_cpu(origin_gate, m.souls[i]);
                                InfernalAddress proxy = aamon_calculate_contract_address2_cpu(deployer_gate, salt, abyssal_bytecode_hash);
                                gates[i] = aamon_calculate_contract_address_cpu(proxy, 1);
                            }
                        }

                        for (int i = 0; i < m.souls_count; i++) {
                            if (m.soul_scores[i] < min_soul_score) continue; // Фильтр по минимальному Power
                            found_souls++;
                            Infernal256 k = m.souls[i];
                            int score = m.soul_scores[i];
                            InfernalAddress a = gates[i];
                            uint64_t time = (m.time - global_start_time) / 1000;

                            if (mode == 0 || mode == 1) {
                                printf("\r%s💀 Lilith’s Triumph! Soul #%d harvested after %06us | Power: %02u 🔥\n"
                                       "%s    Abyssal Key: 0x%08x%08x%08x%08x%08x%08x%08x%08x\n"
                                       "%s    Infernal Gate: 0x%08x%08x%08x%08x%08x 🖤%s\n",
                                       ANSI_RED, found_souls, (uint32_t)time, score, ANSI_PURPLE, k.a, k.b, k.c, k.d, k.e, k.f, k.g, k.h,
                                       ANSI_PURPLE, a.a, a.b, a.c, a.d, a.e, ANSI_RESET);
                            } else if (mode == 2 || mode == 3) {
                                printf("\r%s💀 Lilith’s Victory! Salt #%d forged after %06us | Power: %02u 🔥\n"
                                       "%s    Abyssal Salt: 0x%08x%08x%08x%08x%08x%08x%08x%08x\n"
                                       "%s    Infernal Gate: 0x%08x%08x%08x%08x%08x 🖤%s\n",
                                       ANSI_RED, found_souls, (uint32_t)time, score, ANSI_PURPLE, k.a, k.b, k.c, k.d, k.e, k.f, k.g, k.h,
                                       ANSI_PURPLE, a.a, a.b, a.c, a.d, a.e, ANSI_RESET);
                            }
                        }

                        delete[] gates;
                        delete[] m.souls;
                        delete[] m.soul_scores;
                    }
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                } else if (m.status == 1) {
                    printf("\r%s💀 Abyssal Rift! CUDA chaos %d consumes Demon %d! Ritual halted! 🖤%s\n", ANSI_RED, m.error, demon_ids[demon_index], ANSI_RESET);
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                } else if (m.status == 11) {
                    printf("\r%s💀 Infernal Curse! BCryptGenRandom defies Demon %d! Ritual halted! 🖤%s\n", ANSI_RED, demon_ids[demon_index], ANSI_RESET);
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                } else if (m.status == 12) {
                    printf("\r%s💀 Void’s Betrayal! /dev/urandom rejects Demon %d! Ritual halted! 🖤%s\n", ANSI_RED, demon_ids[demon_index], ANSI_RESET);
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                } else if (m.status == 13) {
                    printf("\r%s💀 Forbidden Gate! /dev/urandom denies Demon %d access! Ritual halted! 🖤%s\n", ANSI_RED, demon_ids[demon_index], ANSI_RESET);
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                } else if (m.status == 100) {
                    printf("\r%s💀 Memory Abyss! Demon %d swallowed by darkness! Out of space! 🖤%s\n", ANSI_RED, demon_ids[demon_index], ANSI_RESET);
                    asmodeus_print_speeds(num_demons, demon_ids, infernal_speeds);
                    fflush(stdout);
                }
            }
            infernal_message_queue_mutex.unlock();
        }
    }
}