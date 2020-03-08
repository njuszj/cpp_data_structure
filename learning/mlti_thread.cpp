#include<thread>
#include<iostream>
#include<cstdio>
#include<mutex>
#include<condition_variable>

using namespace std;
int flag = 10;
mutex mu;
condition_variable cv;

void func(int x, char c){
    for(int i=0; i<50 ; i++){
        unique_lock<mutex> lock(mu);
        while(flag != x) 
            cv.wait(lock);
        for(int j=0;j<x;j++){
            cout << c << ":" << j << endl;
        }
        flag = (x==10) ? 100 : 10;
        cv.notify_one();
    }
}

int main(){
    thread t1(func, 10, 'A');
    func(10, 'B');
    t1.join();
}
