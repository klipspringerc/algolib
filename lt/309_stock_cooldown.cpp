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

    // since last dp only relies on previous day output, so simplify to non dp.
    int maxProfitDPS(vector<int>& prices) {
        int dpBuy1 = 0-prices[0];
        int dpNohold2 = 0;
        // impossible cases;
        int dpBuy0 = -10000;
        int dpNohold0 = -10000;
        int dpNohold1 = -10000;
        //
        for (int i = 1; i < prices.size(); i++) {
            int newBuy1 = max(dpBuy1, dpNohold2-prices[i]);
            int newBuy0 = max(dpBuy0, dpNohold1-prices[i]);
            dpNohold1 = max(dpNohold1, dpBuy1 + prices[i]);
            dpNohold0 = max(dpNohold0, dpBuy0 + prices[i]);
            dpBuy1 = newBuy1, dpBuy0 = newBuy0;
        }
        return max(dpNohold2, max(dpNohold1, dpNohold0));
    }

    int maxProfitGreedy(vector<int>& prices) {
        int profit1 = INT_MIN;
        int buy1 = INT_MAX;
        int profit2 = INT_MIN;
        int buy2 = INT_MAX;
        for (int i = 0; i < prices.size(); i++) {
            buy1 = min(buy1, prices[i]);
            profit1 = max(profit1, prices[i] - buy1);
            buy2 = min(buy2, prices[i] - profit1);
            profit2 = max(profit2, prices[i] - buy2);
        }
        return profit2;
    }

    // at most transact k times;
    int maxProfit(int k, vector<int>& prices) {
        vector<int> dpBuy (k+1, -10000);
        vector<int> dpNoHold (k+1, -10000);
        vector<int> nBuy(k+1, -10000);
        dpBuy[k-1] = 0-prices[0];
        dpNoHold[k] = 0;
        for (int i = 0 ; i < prices.size(); i++) {
            for (int t = k-1; t > -1; t--) {
                nBuy[t] = max(dpBuy[t], dpNoHold[t+1] - prices[i]);
            }
            for (int t = k-1; t > -1; t--) {
                dpNoHold[t] = max(dpNoHold[t], dpBuy[t] + prices[i]);
                dpBuy[t] = nBuy[t];
            }
        }
        int profit = 0;
        for (int t = 0; t < k; t++) {
            if (dpNoHold[t] > profit)
                profit = dpNoHold[t];
        }
        return profit;
    }
};

int main() {
    Solution s;
    vector<int> input = {3,2,6,5,0,3,0,4};
//    printf("result: %d \n", s.maxProfitGreedy(input));
    printf("result: %d \n", s.maxProfit(1, input));
}