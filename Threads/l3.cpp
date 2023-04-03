#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Barrier {
public:
    Barrier(int count) : count_(count), current_count_(count) {}

    void Wait() {
        unique_lock<mutex> lock(mtx_);
        if (--current_count_ == 0) {
            current_count_ = count_;
            cv_.notify_all();
        } else {
            cv_.wait(lock, [this]() { return current_count_ == 0; });
        }
    }

private:
    int count_;
    int current_count_;
    mutex mtx_;
    condition_variable cv_;
};

const int THREAD_COUNT = 4;

void thread_func(int *counter, Barrier *barrier)
{
    (*counter)++;
    cout << "Contador esta em " << *counter << endl;
    barrier->Wait();
}

int main()
{
    int counter = 0;
    Barrier barrier(THREAD_COUNT);

    thread t1(&thread_func, &counter, &barrier);
    thread t2(&thread_func, &counter, &barrier);
    thread t3(&thread_func, &counter, &barrier);
    thread t4(&thread_func, &counter, &barrier);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    barrier.Wait(); // Wait for the barrier to be released

    return 0;
}
