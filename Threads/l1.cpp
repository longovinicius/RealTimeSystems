#include <iostream>
#include <thread>

using namespace std;

static int COUNTER = 0;

void thread_func()
{   
    COUNTER += 1;
    cout << "Contador esta em " << COUNTER << endl;
}

int main()
{

    thread t1(thread_func);
    thread t2(thread_func);
    thread t3(thread_func);
    thread t4(thread_func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}