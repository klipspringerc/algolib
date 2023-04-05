//
// Created by SG0014000445M on 2023/1/16.
//
#include <cstdio>
#include <cmath>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }
        unsigned long max = 1<<16;
        unsigned long l = 0;
        unsigned long r = x;
        if (r > max) {
            r = max;
        }
        while (r-l > 1) {
            unsigned long mid = l + (r-l)/2;
            unsigned long prod = mid * mid;
            if (prod > x) {
                r = mid;
            } else if (prod == x) {
                return mid;
            } else {
                l = mid;
            }
        }
        return l;
    }

    float testF(int x) {
        float p = x;
        float last = p+10;
        while (abs(p-last) > 0.01) {
            last = p;
            p = (p + x/p)/2;
        }
        return p;
    }
};

int main() {
    Solution s;
    printf("result: %d\n", s.mySqrt(65));
    printf("newton method: %f\n", s.testF(65));
}