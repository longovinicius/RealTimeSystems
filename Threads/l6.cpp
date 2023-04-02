#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int gen_data(int max)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(nullptr));
        initialized = true;
    }
    return rand() % max + 1;
}

void produtor(vector<int> &buffer, int max_buffer, sem_t *available_product, sem_t *available_vacancy, mutex &mtx)
{
    while (true)
    {
        sem_wait(available_vacancy);
        lock_guard<mutex> lock(mtx);
        int data = gen_data(100000);
        buffer.push_back(data);
        cout << data << " was added" << endl;
        cout << "BUFFER_SIZE: " << buffer.size() << endl;
        mtx.unlock(); // release the mutex before signaling the semaphore
        sem_post(available_product);
    }
}

void consumidor(vector<int> &buffer, int max_buffer, sem_t *available_product, sem_t *available_vacancy, mutex &mtx)
{
    while (true)
    {
        sem_wait(available_product);
        lock_guard<mutex> lock(mtx);
        cout << buffer.front() << " was consumed" << endl;
        buffer.erase(buffer.begin());
        cout << "BUFFER_SIZE: " << buffer.size() << endl;
        mtx.unlock();
        sem_post(available_vacancy);
    }
}

int main()
{
    int max_buffer = 5;
    sem_t available_vacancy;
    sem_t available_product;
    vector<int> buffer;
    mutex mtx;

    sem_init(&available_product, 0, 0);
    sem_init(&available_vacancy, 1, max_buffer);

    thread t_consumidor(&consumidor, ref(buffer), max_buffer, &available_product, &available_vacancy, ref(mtx));
    thread t_produtor(&produtor, ref(buffer), max_buffer, &available_product, &available_vacancy, ref(mtx));

    t_consumidor.join();
    t_produtor.join();

    sem_destroy(&available_product);
    sem_destroy(&available_vacancy);

    return 0;
}