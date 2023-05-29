//
// https://leetcode.com/problems/number-of-digit-one/description/
//
// Patterns?   0-9: 1 time 1*1
// 0-99: 10 times 1*, 10 times *1   2 *10
// 0-999?  100 times 1**, 10*10 times *1*, 10 * 10 times **1  3 * 100
// 0-9999  1000 times 1*** 10*10*10 time *1**,     4 * 1000


// 13  11 12 13, 3


#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


class Solution {
public:
    int countDigitOne(int n) {
        int count_digits = 0;
        int num = n;
        vector<int> digits;

        while (num > 0) {
            digits.push_back(num % 10);
            count_digits++;
            num /=10;
        }
        unsigned long long acc = 0;
        unsigned long long base = 1;
        unsigned long long count1 = 0;
        for (int i = 0; i < digits.size(); i++) {
            int cur = digits[i];
            // if current digit == 0, no contribution of ones from this position
            if (cur >=1 ) {
                // for 038, no extra 1 would be added for this position
                if (cur == 1)
                    count1 += acc+1;  // e.g. add 23+1 for num 123 (range [100,123] )
                else if (cur >=2)
                    count1 += base;  // e.g. add 100 for 1xx counts in num range [100,199]

                count1 += cur * (i * (base/10)); // add [0,99] for each 1 after current position: digits 0-099, 100-199, 200-299
            }
            acc += cur * base;
            base *=10;
        }
        return count1;
    }
};

int main() {
    Solution s;
    // 123:   24 + 20 + 10 + 2 + 1
    cout << s.countDigitOne(1000000000) <<endl;
}
