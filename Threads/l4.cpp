#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>

using namespace std;

void thread_func(int *counter, sem_t *sem, mutex *mtx, int id)
{
    sem_post(sem);
    lock_guard<mutex> lock(*mtx);
    (*counter)++;
    cout << "Contador esta em " << *counter << " na Thread " << id << endl;
}

int main()
{

    int counter = 0;

    sem_t sem;
    sem_init(&sem, 0, 0);

    mutex mtx;

    thread t1(&thread_func, &counter, &sem, &mtx, 0);
    thread t2(&thread_func, &counter, &sem, &mtx, 1);
    thread t3(&thread_func, &counter, &sem, &mtx, 2);
    thread t4(&thread_func, &counter, &sem, &mtx, 3);

    for (int i = 0; i < 4; i++)
    {
        sem_wait(&sem);
    }

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}