#include <thread>
#include <iostream>
#include <chrono>
#include <random>

auto perf_counter() {
    return std::chrono::high_resolution_clock::now();
}

void generate_random_motor_info(int motor_info[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 4095);
    for (int i = 0; i < 5; i++) {
        motor_info[i] = distrib(gen);
    }
}

void param_read(int motor_info[], int (&parameters)[2]) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    parameters[0] = motor_info[0] + motor_info[1];
    parameters[1] = motor_info[2] + motor_info[3];
}

void calculations(int parameters[], int& result) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    result = parameters[0] * parameters[1];
}

void screen_update(int result) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Resultado dos calculos: " << result << std::endl;
}

int main() {
    
    int motor_info[5];
    int motor_parameters[2];
    int calc_result;
    std::chrono::milliseconds period_mili = std::chrono::milliseconds(25);
    std::chrono::milliseconds total_duration_mili = std::chrono::milliseconds(0);
    std::chrono::milliseconds time_left;
    int num_periods = 4;

    for (int i = 0; i < num_periods; i++) {
        auto start = perf_counter();
        generate_random_motor_info(motor_info);
        switch (i) {
            case 0: {
                std::thread t1(param_read, motor_info, std::ref(motor_parameters));
                t1.join();
                std::thread t2(calculations, std::ref(motor_parameters), std::ref(calc_result));
                t2.join();
                break;
            }
            case 1: {
                std::thread t1(param_read, motor_info, std::ref(motor_parameters));
                t1.join();
                break;
            }
            case 2: {
                std::thread t1(param_read, motor_info, std::ref(motor_parameters));
                t1.join();
                std::thread t2(calculations, std::ref(motor_parameters), std::ref(calc_result));
                t2.join();
                break;
            }
            case 3: {
                std::thread t1(param_read, motor_info, std::ref(motor_parameters));
                t1.join();
                std::thread t3(screen_update, calc_result);
                t3.join();
                break;
            }
        }
        auto end = perf_counter();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tempo usado(" << i << "): " << duration.count() << "ms" << std::endl;
        time_left = period_mili - duration;
        total_duration_mili += (duration + time_left);
        std::this_thread::sleep_for(time_left);
    }

    std::cout << "Tempo total: " << total_duration_mili.count() << "ms" << std::endl;

    return 0;
}
