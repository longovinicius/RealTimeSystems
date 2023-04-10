#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

auto hr_current_time() -> std::chrono::_V2::system_clock::time_point
{
    return chrono::high_resolution_clock::now();
}

auto current_time_t()
{
    auto now = chrono::system_clock::now();      // obtém o tempo atual
    return chrono::system_clock::to_time_t(now); // converte para o formato de tempo padrão
}

void threadFunction(int8_t period)
{
    auto start = hr_current_time();
    cout << "Thread executing" << endl;
    auto end = hr_current_time();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto period_mili = chrono::milliseconds(period * 1000);
    this_thread::sleep_for(period_mili - duration);
}

int main()
{
    time_t start_time_t = current_time_t(); // time_t convertion
    cout << "Programa comecou às " << ctime(&start_time_t) << endl;
    thread t(threadFunction, 5); // cria uma nova thread para executar a função
    t.join();
    time_t end_time_t = current_time_t();
    cout << "Programa finalizou às " << ctime(&end_time_t) << endl;
    return 0;
}
