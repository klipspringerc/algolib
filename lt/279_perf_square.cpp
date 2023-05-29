//
// https://leetcode.com/problems/perfect-squares/
// return least num of square number that sum to given n
// n = 12, returns 3 (4+4+4)
// n = 13, returns 2 (4 + 9)
// n <= 10000

#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numSquares(int n)
    {
        if (n <= 0)
        {
            return 0;
        }

        // cntPerfectSquares[i] = the least number of perfect square numbers
        // which sum to i. Since cntPerfectSquares is a static vector, if
        // cntPerfectSquares.size() > n, we have already calculated the result
        // during previous function calls and we can just return the result now.
        static vector<int> cntPerfectSquares({0});

        // While cntPerfectSquares.size() <= n, we need to incrementally
        // calculate the next result until we get the result for n.
        while (cntPerfectSquares.size() <= n)
        {
            int m = cntPerfectSquares.size();
            int cntSquares = INT_MAX;
            for (int i = 1; i*i <= m; i++)
            {
                cntSquares = min(cntSquares, cntPerfectSquares[m - i*i] + 1);
            }

            cntPerfectSquares.push_back(cntSquares);
        }

        return cntPerfectSquares[n];
    }
    int numSquaresTLE(int n) {
        int start = min(int(ceil(sqrt(float(n)))), 99);
        vector <unordered_map<int, int>> dp (start+1); // dp[pos][remain];
        return recur_squares(start, n, dp);
    }

    int recur_squares(int step, int remain, vector<unordered_map<int, int>> & dp) {
        if (remain == 0)
            return 0;
        if (step == -1) {
            // remain not equals zero, not feasible
            return -1;
        }
        if (dp[step].find(remain) != dp[step].end())
            return dp[step][remain];
        int psq = (step+1) * (step+1);
        int prev = (step+2) * (step+2);
        int ans = INT_MAX;
        int m = remain / psq;
        if (remain % psq == 0) {
            return (dp[step][remain] = m);
        }
        // i == 0, does not use current perfect square num at step, otherwise use i current square numbers in sum
        for (int i = m; i >= 0; i--) {
            int r = recur_squares(step-1, remain - i * psq, dp);
            if (r != -1)
                ans = min(ans, r+i);
        }
        if (ans == INT_MAX)
            ans = -1;
        return (dp[step][remain] = ans);
    }
};

int main() {
    Solution s;
    cout << s.numSquares(18) << endl;
}

