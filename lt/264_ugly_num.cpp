//
// https://leetcode.com/problems/ugly-number-ii/
// return the n the number only prime factors 2 3 5

// solution sieve to get prime numbers, then
// either prime numbers, or 2,3,5 constructs

// n < = 1690

// 1 2 3 2*2 5 2*3 2*2*2 3*3 2*5 2*2*3 3*5 2*2*2*2 2*3*3
// seg fault start at 10^8

#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0]=1;
        int x=0, y=0, z=0;
        for(int i=1; i<n; i++){
            dp[i] = min(dp[x]*2, min(dp[y]*3, dp[z]*5));
            if(dp[i] == 2*dp[x]) x++;
            if(dp[i] == 3*dp[y]) y++;
            if(dp[i] == 5*dp[z]) z++;
        }
        return dp[n-1];
    }

    int nthUglyNumberTLE(int n) {
        bitset<1000000000> * sieve = new bitset<1000000000>();
        size_t N = 1000000000;
        (*sieve)[1] = true;
        int count = 1;
        for (size_t num = 1; num < N; num++) {
            if ((*sieve)[num]) {
                for (size_t n = num * 2; n < N; n *= 2) {
                    if (!(*sieve)[n]) {
                        (*sieve)[n] = true;
                        count ++;
                    }
                }
                for (size_t n = num * 3; n < N; n *= 3) {
                    if (!(*sieve)[n]) {
                        (*sieve)[n] = true;
                        count ++;
                    }
                }
                for (size_t n = num * 5; n < N; n *= 5) {
                    if (!(*sieve)[n]) {
                        (*sieve)[n] = true;
                        count ++;
                    }
                }
            }
        }
        cout << "total num " << count << endl;
        size_t ord =0;
        for (size_t num = 1; num < N; num++) {
            if ((*sieve)[num]) {
                ord++;
                if (ord ==n)
                    return num;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    cout <<s.nthUglyNumber(1600) <<endl;

}