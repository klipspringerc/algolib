//
// https://leetcode.com/problems/minimum-path-sum/
// Solution: dp

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp (n);
        dp[0] = grid[0][0];
        // calculate first row path sum
        for(int i = 1; i < n; i++) {
            dp[i] = dp[i-1] + grid[0][i];
        }
        for (int i = 1; i < m; i++) {
            dp[0] = dp[0] + grid[i][0];
            for (int j = 1; j < n; j++) {
                if (dp[j-1] < dp[j])
                    dp[j] = dp[j-1] + grid[i][j];
                else
                    dp[j] = dp[j] + grid[i][j];
            }
        }
        return dp[n-1];
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
            {1,2,3},
            {4,5,6},
//            {5,2,2}
//            {1},
//            {1},
//            {5}
    };
    printf("min sum %d\n", s.minPathSum(grid));
}