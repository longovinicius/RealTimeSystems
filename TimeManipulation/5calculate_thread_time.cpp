#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

auto hr_time(){
    return chrono::high_resolution_clock::now();
}
void my_thread(){
    auto t_start = hr_time();
    cout << "Thread is executing rn" << endl;
    this_thread::sleep_for(5s);
    auto t_end = hr_time();
    chrono::milliseconds time_taken = chrono::duration_cast<chrono::milliseconds>(t_end - t_start);
    cout << "Thread took " << time_taken.count() << " milliseconds" << endl;
}

int main(){
    thread t1(my_thread);
    t1.join();
    
    return 0;
}