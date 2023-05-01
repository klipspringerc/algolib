//
// https://leetcode.com/problems/paint-house-iii/description/
// Knapsack DP solution
// Determine unique state requires 3 parameters: current house position, last house's color, remaining target value.
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // n number of colors
        // m number of houses
        // dp stores min cost of coloring house i with last house's color being k and remaining target value.
        vector<vector<vector<int>>> dp(m, vector<vector<int>> (n+1, vector<int>(target+1, -2)));
        // dp[0][0][target] coloring first, previous no color, remaining target full
        // small trick to start with last=0, so any paint would cause target-1.
        return minCostRecur(houses, cost, 0, 0, target, dp);
    }
    int minCostRecur(vector<int>& houses, vector<vector<int>>& cost, int idx, int last, int target, vector<vector<vector<int>>>& dp) {
        int n = houses.size();
        int m = cost[0].size();
        if (target < 0 || idx == n && target > 0)
            return -1; // -1 represent no viable solutions
        // termination condition: reaching last house with target achieved.
        if (idx == n && target == 0)
            return 0;
        if (dp[idx][last][target] != -2)
            return dp[idx][last][target];
        int ans = INT_MAX;
        // if painted last summer, cannot change color, just update target based on current house color
        if (houses[idx] > 0) {
            int remain_cost;
            if (houses[idx] == last) {
                // still the same color as last house, so target value unchanged.
                remain_cost = minCostRecur(houses, cost, idx+1, last, target, dp);
            } else {
                remain_cost = minCostRecur(houses, cost, idx+1, houses[idx], target-1, dp);
            }
            if (remain_cost > -1) {
//                printf("updating painted house no. %d min host to %d\n", idx, remain_cost);
                ans = remain_cost;
            }
        } else {
            // not painted house must be painted, so try all colors
            for (int k = 0; k < m; k++) {
                int cur_cost = cost[idx][k];
                int remain_cost;
                if (k+1 == last) {
                    // paint the same color as the house before, so target value would not change
                    remain_cost = minCostRecur(houses, cost, idx+1, last, target, dp);
                } else {
                    // paint a different color than the house before -> new neighborhood, so we reduce target value by 1.
                    remain_cost = minCostRecur(houses, cost, idx+1, k+1, target-1, dp);
                }
                if (remain_cost > -1) {
                    ans = min(ans, remain_cost + cur_cost);
//                    printf("obtaining paint house no. %d to %d cost %d + %d , current min %d \n", idx, k+1, cur_cost, remain_cost, ans);
                }
            }
        }
        if (ans == INT_MAX) {
            return dp[idx][last][target] = -1; // note that `no possible solution` is itself a result need to be stored
        }
        return dp[idx][last][target] = ans;
    }
};

int main() {
    Solution s;
    vector<int> houses = {0,0,0,0,0};
//    vector<int> houses = {1};
//    vector<int> houses = {3,2,1,3,0};
    vector<vector<int>> costs = {
//            {1,1},
            {1,10},{10,1},{10,1},{1,10},{5,1},
//            {1,1,1},{10,1,1},{10,1,1},{1,10,1},{1,1,4}
    };
    printf("min cost: %d\n", s.minCost(houses, costs, 5, 2, 1));
}