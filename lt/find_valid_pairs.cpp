//
// Created by Shengping Cui on 2023/4/25.
//

#include<cstdio>
#include<set>
#include<ctime>
#include <unistd.h>

using namespace std;

void find_pairs(long long s) {

    set<long long> dict;
    dict.insert(1);
    dict.insert(2);
    long long num1 = 1ll, num2 = 2ll;
    long long i = 0;
    while(true) {
        long long int sum = num1 + num2;
        if (sum > (long long)(1e18))
            break;
        dict.insert(sum);
        num1 = num2;
        num2 = sum;
        i++;
    }
//    printf("count 8: %ld\n", dict.count(8ll));
//    printf("mark %lld, calculated until %lld, iteration count %lld \n", (long long)(1e18), num2,i);
    for (long long v : dict) {
        printf("test value %lld\n", v);
        if (v > s)
            break;
        long long int b = s - v;
        if (v > b)
            break;
        if (dict.count(b) > 0) {
            printf("found pair: %lld %lld\n", v, b);
        }
    }
//    for (long long int a = 1; a < s; a++) {
//        long long int b = s - a;
//        if (b < a) {
//            printf("end\n");
//            return;
//        }
//        if (dict.count(a) > 0 && dict.count(b) > 0) {
//            printf("found pair: %lld %lld\n", a, b);
//        }
//    }

}

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

int main() {
    struct timespec start, finish, delta;

    std::clock_t a = std::clock();
    clock_gettime(CLOCK_MONOTONIC, &start);
    find_pairs(7000);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    sub_timespec(start, finish, &delta);
    std::clock_t b = std::clock();
    printf("time elapsed %d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);
    printf("time elapsed %ld\n", b-a);
}