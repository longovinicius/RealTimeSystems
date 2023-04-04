
 

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

void threadFunction() {
    int period = 5; // período em segundos

    while (true) {
        auto now = system_clock::now(); // obtém o tempo atual
        auto now_c = system_clock::to_time_t(now); // converte para o formato de tempo padrão
        std::cout << "Thread executando às " << std::ctime(&now_c); // imprime a hora atual
        std::this_thread::sleep_for(seconds(period)); // aguarda o período de 5 segundos
    }
}

int main() {
    std::thread t(threadFunction); // cria uma nova thread para executar a função
    t.join(); // aguarda a thread terminar

    return 0;
}