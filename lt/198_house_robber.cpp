//
// https://leetcode.com/problems/house-robber/
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        // dp[i][1] means max profit with rob performed at i, dp[i][0] is max profit with no rob performed at i
        dp[0][1] = nums[0];
        dp[0][0] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][1] = dp[i-1][0] + nums[i];
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        }
        return max(dp[n-1][1], dp[n-1][0]);
    }

    int robCircle(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return max(nums[0], 0);
        vector<vector<int>> dp(n, vector<int>(2, 0)); // dp is the optimal solution including existence of nums[0]
        vector<vector<int>> dps(n, vector<int>(2, 0)); // dps is the optimal solution ignoring the existence of nums[0]
        // dp[i][1] means max profit with rob performed at i, dp[i][0] is max profit with no rob performed at i
        dp[0][1] = nums[0];
        dp[0][0] = 0;
        dps[0][1] = 0;
        dps[0][0] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][1] = dp[i-1][0] + nums[i];
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
            dps[i][1] = dps[i-1][0] + nums[i];
            dps[i][0] = max(dps[i-1][0], dps[i-1][1]);
        }
        // compare the best solution with nums[0] but without nums[n-1], and the best solution without nums[0].
        return max(dp[n-1][0], max(dps[n-1][0], dps[n-1][1]));
    }
};

int main() {
    Solution s;
    vector<int> input = {1,2,3};
    printf("max profit: %d\n", s.robCircle(input));

}