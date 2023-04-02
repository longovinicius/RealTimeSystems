#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

void thread_func(int *counter, sem_t *sem)
{
    (*counter)++;
    cout << "Contador esta em " << *counter << endl;
    sem_post(sem);
}

int main()
{

    int counter = 0;

    sem_t sem;
    sem_init(&sem, 0, 0);

    thread t1(&thread_func, &counter, &sem);
    thread t2(&thread_func, &counter, &sem);
    thread t3(&thread_func, &counter, &sem);
    thread t4(&thread_func, &counter, &sem);

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