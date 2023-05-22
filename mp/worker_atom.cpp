//
//
//


#include <thread>
#include <vector>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <atomic>
#include <cassert>

using namespace std;

int shared_sum = 0;
atomic<int> mp_sum (0);

void sum_worker(const vector<int> & in, int s, int e) {
    int sum = 0;
    for (int i = s; i < e; i++) {
        sum += in[i];
        mp_sum += in[i];
    }
    cout << "get thead sum " << sum <<endl;
//    shared_sum += sum;
}

void observer() {
    for (int i = 0 ; i  < 10; i++) {
        this_thread::sleep_for(chrono::microseconds (10));
        printf("current sum:  %d \n", mp_sum.load());
    }
}


int main() {
    vector<int> data (10000, 1);
    thread t1(sum_worker, data, 0, 3000), t2(sum_worker, data, 3000, 6000), t3(sum_worker, data, 6000, 10000);
    thread t4(observer);
    t4.detach();
    t1.join();
    t2.join();
    t3.join();
    cout << "completed with sum: " << mp_sum.load() << endl;
    assert(mp_sum.load() == 10000);
    return 0;
}