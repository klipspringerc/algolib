//
// https://leetcode.com/problems/powx-n/
// Solution: inline comments
//

#include <cstdio>

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1;
        }
        if (x == 0 || x == 1 || n == 1) {
            return x;
        }
        if (n < 0) {
            return 1 / (x * myPow(x, -(n+1))); // need to handle asymmetric range (note 32 bit int is -2^31 to 2^31-1)
        }
        double intermediate = myPow(x, n/2); // reduce calculations
        if (n & 1) {
            return intermediate * intermediate * x;
        } else {
            return intermediate * intermediate;
        }
    }
};

int main() {
    Solution s;
    printf("result: %f\n", s.myPow(12, 2));
}