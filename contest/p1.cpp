//
// 2015 Asia Singapore Preliminary Contest
// Created by KevinCui on 22/8/18.
//
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long int ll;

ll M, N;

bool compare_1() {
    ll fac = 1;
    ll last_fac;
    for (int i = 2; i<=N; i++) {
        last_fac = fac;
        fac *= i;
        if (fac > M || fac < last_fac)
            return false;
    }
    return true;
}

bool compare_2() {
    ll fac = 1;
    ll last_fac;
    for (int i = 0; i < N; i++) {
        last_fac = fac;
        fac *= 2;
        if (fac > M || fac < last_fac)
            return false;
    }
    return true;
}

bool compare_3(int p) {
    ll fac = 1;
    ll last_fac;
    for (int i = 0; i < p; i++) {
        last_fac = fac;
        fac *= N;
        if (fac > M || fac < last_fac)
            return false;
    }
    return true;
}

bool compare_6() {
    double r = N;
    r *= log((double)N) / log(2.0);
    return (double)M - r > -1e-9;
}

bool compare_7() {
    return M >= N;
}

int T;

int main() {
    while (scanf("%lld %lld %d", &M, &N, &T) == 3) {
        bool ac;
        if (T == 1)
            ac = compare_1();
        if (T == 2)
            ac = compare_2();
        if (T == 3)
            ac = compare_3(4);
        if (T == 4)
            ac = compare_3(3);
        if (T == 5)
            ac = compare_3(2);
        if (T == 6)
            ac = compare_6();
        if (T == 7)
            ac = compare_7();
        if (ac)
            puts("AC");
        else
            puts("TLE");
    }
}