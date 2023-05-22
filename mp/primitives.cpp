//
// concurrency primitives
//

#include <mutex>
#include <iostream>
#include <cstdio>
#include <vector>
#include <thread>

using namespace std;
vector<int> data (10000,2);

int write_routine(int l, int r) {
    cout << "write routine invoked on thread " << this_thread::get_id() << endl;
    static mutex mtx;
    lock_guard<mutex> guard(mtx);
    cout << "thread " << this_thread::get_id();
    printf(" start updating boundary %d - %d\n", l, r);
    for (int i = l; i < r; i++) {
        data[i]++;
    }
    cout << "thread " << this_thread::get_id();
    printf(" finished updating boundary %d - %d\n", l, r);
    return 0;
}

int main() {
    thread t[3];
    for (int i = 0; i < 3; i++) {
        t[i] = thread(write_routine, 0, 10000);
    }
    for (int i = 0; i < 3; i++) {
        t[i].join();
    }
    for (int i = 10; i < 13; i++)
        cout << data[i] << " ";
    cout << endl;
    return 0;
}