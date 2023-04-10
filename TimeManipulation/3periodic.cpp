
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

auto current_time_t(){
    auto now = chrono::system_clock::now();  // obtém o tempo atual
    return chrono::system_clock::to_time_t(now);  // converte para o formato de tempo padrão
}

void threadFunction() {
    auto now_t = current_time_t();
    cout << "Thread executando às " << ctime(&now_t); // imprime a hora atual
}

int main() {

    auto start_t = current_time_t(); 
    cout << "Programa comecando às " << ctime(&start_t);
    int period = 5;
    auto period_mili = chrono::milliseconds(period*1000);
    this_thread::sleep_for(period_mili);
    thread t(threadFunction); // cria uma nova thread para executar a função
    t.join(); // aguarda a thread terminar

    return 0;
}