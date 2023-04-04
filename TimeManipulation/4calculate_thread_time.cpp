#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

void myTask()
{
    std::cout << "Executando tarefa...\n";
}

int main()
{

    auto start_time = high_resolution_clock::now(); // starttime

    std::thread t(myTask);
    t.join(); // aguarda a thread terminar

    auto end_time = high_resolution_clock::now(); // endtime

    // Calcula a duração de execução da tarefa
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    std::cout << "Duração da execução da tarefa: " << duration.count() << " ms\n";

    return 0;
}
