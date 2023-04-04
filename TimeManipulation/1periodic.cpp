#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void threadFunction()
{
    auto now = chrono::system_clock::now();                             // obtém o tempo atual
    auto now_c = chrono::system_clock::to_time_t(now);                  // converte para o formato de tempo padrão
    std::cout << "Thread executando às " << std::ctime(&now_c) << endl; // imprime a hora atual
}

int main()
{   
    auto now = chrono::system_clock::now();
    auto now_format = chrono::system_clock::to_time_t(now);
    cout << "Programa comecou às " << ctime(&now_format) << endl;
    this_thread::sleep_for(5s); 
    thread t(threadFunction); // cria uma nova thread para executar a função
    t.join();                      

    return 0;
}