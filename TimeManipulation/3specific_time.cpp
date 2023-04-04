#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

void threadFunction()
{
    std::cout << "Thread executando às 9h da manhã\n";
}

int main()
{
    // Obtém o tempo atual e calcula o tempo até as 9h da manhã
    auto now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    local_tm.tm_hour = 9;
    local_tm.tm_min = 0;
    local_tm.tm_sec = 0;
    auto target_time = std::chrono::system_clock::from_time_t(mktime(&local_tm));
    if (now > target_time)
    {
        target_time += std::chrono::hours(24);
    }
    auto duration = target_time - now;

    // Aguarda até as 9h da manhã
    std::this_thread::sleep_for(duration);

    // Cria uma nova thread para executar a função às 9h
    std::thread t(threadFunction);
    t.join(); // aguarda a thread terminar

    return 0;
}
