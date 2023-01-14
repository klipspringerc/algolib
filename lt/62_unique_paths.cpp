//
// https://leetcode.com/problems/unique-paths/description/
// Solution:
//   robot can only move down & right, so DP:
//   each state represent the number of unique pathway to the current tile
//   each step sum the count of above and left tiles
//
//   because each tile would only be use by below and right tile,
//   so possible to reduce total state stored: 1D array, calculate state row by row

//
// https://leetcode.com/problems/unique-paths-ii/description/
// Solution: consider cases where left+top obstacles lead to unreachable tiles
//   mark unreachable tiles with path count zero
//

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) {
            return 1;
        }
        int * dp = (int *) malloc(n * sizeof (int));
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
        }
        for (int i = 1; i < m; i++) {
            dp[0] = 1;
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[n-1];
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid[0].size();
        int m = obstacleGrid.size();
        int * dp = (int *) malloc(n * sizeof (int));
        if (obstacleGrid[0][0]) {
            return 0;
        }
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            // for the first row, any obstacle would mean no way to tiles to the RHS
            dp[i] = (obstacleGrid[0][i] == 0 && dp[i-1])? 1:0;
        }
        if (m == 1) {
            return dp[n-1];
        }

        for (int i = 1; i < m; i++) {
            // if first tile has obstacle, or the tile above has no way to it,
            // first tile is also unreachable -> 0
            if (obstacleGrid[i][0] || dp[0] == 0) {
                dp[0] = 0;
            } else {
                dp[0] = 1;
            }
            for (int j = 1; j < n; j++) {
                int blocked = obstacleGrid[i][j];
                if (blocked) {
                    dp[j] = 0;
                } else {
                    dp[j] = dp[j] + dp[j-1];
                }
            }
        }
        return dp[n-1];
    }
};

int main() {
    Solution s;
    printf("result %d\n", s.uniquePaths(2,3));
    vector<vector<int>> grid = {
            {0,0,0},
            {1,0,1},
            {0,0,0},

//            {0,1},
//            {0,0},
    };
    printf("obstacle result %d\n", s.uniquePathsWithObstacles(grid));
}