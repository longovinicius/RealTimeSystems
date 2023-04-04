#include <chrono>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    // Obtém o tempo atual
    auto now = std::chrono::system_clock::now();

    // Converte o tempo atual para um formato de tempo legível
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // Imprime o tempo atual
    cout << "Tempo atual: " << ctime(&now_time_t);

    //cout << sizeof(now_time_t) << endl;

    return 0;
}
