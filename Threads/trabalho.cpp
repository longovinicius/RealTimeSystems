#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

const int BUFFER_SIZE = 10;
const int NUM_ESCRITORES = 3;
const int NUM_LEITORES = 5;

/*
TODO:
-Escritores acesso exclusivo a zona critica
-Testar codigo

*/

void escritor(std::vector<int> &buffer, std::mutex mtx, std::condition_variable espaco_disponivel_cv)
{
    int data_gen = 0;
    std::unique_lock<std::mutex> lock(mtx);
    while (true)
    {
        espaco_disponivel_cv.wait(lock, [&]
                                  { return !buffer.empty(); });
        buffer.push_back(data_gen);
        data_gen++;
        espaco_disponivel_cv.notify_one();
    }
}

void leitor(std::vector<int> &buffer, std::mutex mtx, std::condition_variable leitura_disponivel_cv)
{
    std::unique_lock<std::mutex> lock(mtx);
    while (true)
    {
        leitura_disponivel_cv.wait(lock, [&]
                                   { return buffer.size() < BUFFER_SIZE; });
        int data_read = buffer.front();
        buffer.pop_back();
        leitura_disponivel_cv.notify_one();
    }
}

int main()
{
    std::vector<int> buffer(BUFFER_SIZE);
    std::mutex mtx;
    std::condition_variable espaco_dispinivel_cv;
    std::condition_variable leitura_disponivel_cv;
    int buffer_index = 0;

    std::vector<std::thread> leitores;
    std::vector<std::thread> escritores;

    for (int id = 0; id < NUM_ESCRITORES; id++)
    {
        leitores.emplace_back(escritor, std::ref(buffer), std::ref(espaco_dispinivel_cv), id);
    }
    for (int id = 0; id < NUM_LEITORES; id++)
    {
        escritores.emplace_back(leitor, std::ref(buffer), std::ref(leitura_disponivel_cv), id);
    }
    for (auto &thread : escritores)
    {
        thread.join();
    }
    for (auto &thread : leitores)
    {
        thread.join();
    }

    return 0;
}