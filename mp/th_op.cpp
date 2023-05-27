//
// Created by Shengping on 2023/5/15.
//
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

class ThreadPool {
public:
    void Start();
    void Stop();
    void QueueJob(const std::function<void()> & job);
    bool Busy();
private:
    void thread_loop();
    bool should_terminate = false;
    bool wait_pred();
    mutex queue_mutex;
    condition_variable mutex_condition; // thread wait on new jobs
    vector<thread> threads;
    queue<function<void()>> jobs;
};

void ThreadPool::thread_loop() {
    function<void()> job;
    while (1) {
        {
            unique_lock <mutex> lck(queue_mutex);
            // could pass any  bool f() as predicate
            // `this` need to be captured
            mutex_condition.wait(lck, [this]() {
                return !jobs.empty() || should_terminate;
            });

            if (should_terminate) {
                cout << "thread " << this_thread::get_id() << " terminates\n";
                return;
            }
            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::Start() {
    const uint32_t num_threads = thread::hardware_concurrency();
    cout << "system hardware concurrency: " << num_threads << endl;
    threads.resize(num_threads);
    for  (uint32_t i = 0 ; i < num_threads; i++) {
        // note here need to pass both address of function and current thread
        // https://en.cppreference.com/w/cpp/thread/thread/thread
        threads[i] = thread(&ThreadPool::thread_loop, this);
    }
}

void ThreadPool::QueueJob(const std::function<void()> &job) {
    {
        unique_lock <mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

bool ThreadPool::Busy() {
    bool busy;
    {
        unique_lock<mutex> lock(queue_mutex);
        busy = jobs.empty();
    }
    return busy;
}

void ThreadPool::Stop() {
    {
        unique_lock <mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (thread & active_t : threads)
        active_t.join();
    threads.clear();
}

void pause_thread(int n)
{
    std::this_thread::sleep_for (std::chrono::seconds(n));
    std::cout << this_thread::get_id() << ": pause of " << n << " seconds ended\n";
}

void thread_exploit() {
    std::cout << "Spawning and detaching 3 threads...\n";
    std::thread t1(pause_thread,1);
    std::thread t2(pause_thread,2);
    std::thread t3(pause_thread,3);
    std::cout << "Done spawning threads.\n";
    t1.join(); t2.join();
    t3.join();

    std::cout << "(the main thread will now pause for 2 seconds)\n";
    // give the detached threads time to finish (but not guaranteed!):
    pause_thread(2);
}

vector<int> data;

void work(int n) {
    cout <<  "thread " << this_thread::get_id() << " work routine started with n " << n << endl;
    int opc = 0;
    for (int i = 0; i < 10000; i++) {
        if (i % n == 0) {
            data[i]++;
            opc++;
        }
    }
    cout <<  "thread " << this_thread::get_id() << " work routine completed with " << opc << " ops performed " << endl;
}

int main()
{
    data.resize(10000);
    ThreadPool tp;
    tp.Start();
    tp.QueueJob([]() {
        work(3);
    });
    tp.QueueJob([]() {
        work(33);
    });
    tp.QueueJob([]() {
        work(5301);
    });
    cout << "pool is busy: " <<  tp.Busy() << endl;
    this_thread::sleep_for(chrono::seconds(1));
    tp.Stop();
    cout << "pool stopped " <<endl;
    return 0;
}