#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void threadFunction(int8_t period){
    auto start = chrono::high_resolution_clock::now();
    cout << "Thread executing" << endl;
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto period_mili = chrono::milliseconds(period*1000);
    this_thread::sleep_for(period_mili - duration);
}

int main()
{   
    auto now_time = chrono::system_clock::now();
    auto now_format = chrono::system_clock::to_time_t(now_time);
    cout << "Programa comecou às " << ctime(&now_format) << endl;
    thread t(threadFunction, 5); // cria uma nova thread para executar a função
    t.join();                      
    auto now_time_end = chrono::system_clock::now();
    auto now_format_end = chrono::system_clock::to_time_t(now_time_end);
    cout << "Programa finalizou às " << ctime(&now_format_end) << endl;
    return 0;
}
