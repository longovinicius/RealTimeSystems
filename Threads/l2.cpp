#include <iostream>
#include <thread>

using namespace std;

void thread_func(int *counter)
{
    (*counter)++;
    cout << "Contador esta em " << *counter << endl;
}

int main()
{

    int counter = 0;

    thread t1(&thread_func, &counter);
    thread t2(&thread_func, &counter);
    thread t3(&thread_func, &counter);
    thread t4(&thread_func, &counter);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}