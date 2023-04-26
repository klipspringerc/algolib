//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
//
#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int maxProfitSubOpt(vector<int>& prices) {

        // Could be reduced to 2 states: holding and non-holding,
        // only compute purchase operation from non-holding status more than one day ago
        // max(dp[i-2][1]-price[i], dp[i-1][0])

        // 0: holding
        // 1: noholding, cooldown
        // 2: noholding, no cooldown
        int n = prices.size();
        vector<vector<int>> dp(n+1, vector<int>(3,0));
        dp[0][0]= 0-prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][2] - prices[i], dp[i-1][1] -prices[i]));
            dp[i][1] = dp[i-1][0] + prices[i-1];
            dp[i][2] = max(dp[i-1][1], dp[i-1][2]);
        }
        for (int i = 0; i < prices.size(); i++) {
            printf("%d %d %d, ", dp[i][0], dp[i][1], dp[i][2]);
        }
        printf("\n");
        return max(dp[n-1][0] + prices[n-1] , max(dp[n-1][2], dp[n-1][1]));
    }
    // now limit to max 2 transactions
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp (n, vector<vector<int>>(2, vector<int>(3, 0)));
        // dp[day][buy][remain]
        dp[0][0][1] = 0-prices[0];
        dp[0][1][2] = 0;
        // impossible cases;
        dp[0][0][0] = -10000;
        dp[0][0][2] = -10000;
        dp[0][1][0] = -10000;
        dp[0][1][1] = -10000;
        //
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][1][2]-prices[i]);
            dp[i][0][0] = max(dp[i-1][0][0], dp[i-1][1][1]-prices[i]);
            dp[i][1][2] = dp[i-1][1][2];
            dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][1] + prices[i]);
            dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][0][0] + prices[i]);
        }
        return max(dp[n-1][1][1], max(dp[n-1][1][0], dp[n-1][1][2]));
    }

    int maxProfitSimp(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp (n, vector<int>(3, 0));
        // dp[day][remain_tx]
        dp[0][2] = 0; // start with first day, 2 tx remaining
        dp[0][1] = -10000;
        dp[0][0] = -10000;
        for (int i = 1; i < prices.size(); i++) {
            dp[i][2] = dp[i-1][2];
            int max1 = dp[i-1][1];
            int max0 = dp[i-1][0];
            for (int j = 0; j < i; j++) {
                max1 = max(max1, dp[j][2] + prices[i] - prices[j]);
                max0 = max(max0, dp[j][1] + prices[i] - prices[j]);
            }
            dp[i][1] = max1;
            dp[i][0] = max0;
        }
        for (int i = 0; i < prices.size();i++)
            printf("{%d %d %d}  ", dp[i][2], dp[i][1], dp[i][0]);
        printf("\n");
        return max(dp[n-1][0],max(dp[n-1][1],dp[n-1][2]));
    }

    int maxProfitGreedy(vector<int>& prices) {
        int one_max = -1;
        int sec_max = -1;
        int cur = 0;
        int pur = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < pur) {
                pur = prices[i];
            } else {
                cur = prices[i] - pur;
                if (cur > one_max) {
                    sec_max = one_max;
                    one_max = cur;
                }
            }
        }
        if (sec_max == -1)
            sec_max = 0;
        return one_max + sec_max;
    }
};

int main() {
    Solution s;
    vector<int> input = {1,2,3,0,4,0};
    printf("result: %d \n", s.maxProfitSimp(input));
}