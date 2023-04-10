#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

int Tarefa1(int par1, int par2){
    std::this_thread::sleep_for(10ms); 
}

void Tarefa2(){
    std::this_thread::sleep_for(10ms);
    
}

void Tarefa3(){
    std::this_thread::sleep_for(10ms);

}

int main(){
    
    return 0;
}