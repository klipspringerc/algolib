//
// https://leetcode.com/problems/burst-balloons/
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
// n <= 300
// 3,1,5,8 -> 3,5,8 -> 3,8 -> 8 -> []
// at each step, the cost of a balloon may change based on neighbors
// greedy does not work if always burst the smallest
// greedy does not work if always burst the neighbor of largest
// if dp, how to represent states? 2^300 is too much

// to create independent sub problems, we need to go backwards
// if kth balloon is the last to burst, then 1 ... k-1 and k+1 .. n are 2 independent problems
// because all balloons in subproblem would burst before kth, so their right / left boundary would always be kth
// e.g. k-1 th balloon's right neighbor would always be k, would not change to k+1, ...

// then at each backward step, the coins of burst would always be left_boundary * k * right_boundary.

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> bs(n+2);
        vector<vector<int>> dp (n+2, vector<int>(n+2, -1));
        bs[0] = 1;
        bs[n+1] = 1;
        copy(nums.begin(), nums.end(), bs.begin()+1);
        return recur(bs, dp, 0, n+1);
    }

    int recur(vector<int> & nums, vector<vector<int>> & dp, int l, int r) {
        if (l > r-2)
            return 0;
        if (l+1 == r-1)
            return nums[l] * nums[l+1] * nums[r];
        if (dp[l][r] != -1)
            return dp[l][r];
        int ans = 0;
        for (int i = l+1; i <= r-1; i++) {
            int cur = nums[l] * nums[i] * nums[r];
            ans = max(ans, cur + recur(nums, dp, l, i) + recur(nums, dp, i, r));
        }
        return dp[l][r] = ans;
    }
};

int main() {
    Solution s;
    vector<int> in = {9,8,7};
    cout << s.maxCoins(in) << endl;
}