//
// https://leetcode.com/problems/coin-change/
// https://leetcode.com/problems/coin-change-ii/
// classical dp: bottom up approach
// given coin denominations, return smallest number of coin to make up the amount
//

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // return min number of coins required to make up the amount
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp (amount+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (auto c : coins) {
                if (i - c >=0 && dp[i-c] < INT_MAX)
                    dp[i] = min(dp[i], dp[i-c] + 1);
            }
        }
        if (dp[amount] == INT_MAX)
            return -1;
        return dp[amount];
    }

    // return number of combinations that make up that amount
    int change(int amount, vector<int>& coins) {
        size_t n {coins.size()};
        vector<vector<int>> dp (n, vector<int>(amount+1, -1));  // dp[pos][remain] stores used coin position at position with remaining amount
        return recur(coins, dp, 0, amount);
    }

    int recur(vector<int> & coins, vector<vector<int>> & dp, int pos, int remain) {
        size_t n = coins.size();
        if (remain == 0)
            return 1;
        if (pos >= n)
            return 0;
        if (dp[pos][remain] != -1)
            return dp[pos][remain];
        dp[pos][remain] = 0;
        for (int i = 0; i * coins[pos] <= remain ; i++) {
            dp[pos][remain] += recur(coins, dp, pos+1, remain- i * coins[pos]);
        }
        return dp[pos][remain];
    }
};

int main() {
    Solution s;
    vector<int> input = {5};
    cout << s.coinChange(input, 5) << endl;
    cout << s.change(5, input) << endl;
}

