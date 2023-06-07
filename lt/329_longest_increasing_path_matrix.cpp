//
// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
//
// can use DP to record longest path length at each position
// because the path is strictly increasing, so the DP stored path would not intersect with current path
// , which contains only smaller elements.

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (!m)
            return 0;
        int n = matrix[0].size();
        vector<vector<int>> dp (m, vector<int>(n, -1));
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, recur(matrix, dp, i, j));
            }
        }
        return ans;
    }

    int recur(vector<vector<int>>& matrix, vector<vector<int>>& dp, int x, int y) {
        if (dp[x][y] != -1)
            return dp[x][y];
        int m = matrix.size();
        int n = matrix[0].size();
        int ans = 0;
        for (auto d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || matrix[nx][ny] <= matrix[x][y])
                continue;
            ans = max(ans, recur(matrix, dp, nx, ny));
        }
        return dp[x][y] = ans+1;
    }

};

int main() {
    vector<vector<int>> input = {
//            {9,9,9},{6,6,6},
            {3,4,5},{3,2,6},{2,2,1},
//            {1,1,1},{1,1,1},
    };

    Solution s;
    cout << s.longestIncreasingPath(input) << endl;
}