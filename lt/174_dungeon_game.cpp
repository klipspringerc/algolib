//
// https://leetcode.com/problems/dungeon-game/
//


#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<int> dp(n); // store current hp.
        vector<int> minH(n); // store minimum hp occurred through the path.
        dp[0] = dungeon[0][0];
        minH[0] = dp[0];
        for (int i = 1; i < n; i++) {
            dp[i] = dungeon[0][i] + dp[i-1];
            minH[i] = min(dp[i], minH[i-1]);
        }
        for (int i = 1; i < m; i++) {
            dp[0] = dp[0] + dungeon[i][0];
            minH[0] = min(minH[0], dp[0]);
            for (int j = 1; j < n; j++) {
                if (minH[j] > minH[j-1]) {
                    // choose the path with larger minimum health through the whole path
                    dp[j] = dp[j] + dungeon[i][j];
                    minH[j] = min(minH[j], dp[j]);
                } else {
                    dp[j] = dp[j-1] + dungeon[i][j];
                    minH[j] = min(minH[j-1], dp[j]);
                }
            }
        }
        if (minH[n-1] > 0)
            return 1;
        return 1 - minH[n-1];
    }
};

int main() {
    Solution s;
    vector<vector<int>> input = {
//            {0},
//            {-2,-3,3},
//            {-5,-10,1},
//            {10,30,-5},
            {1, -3, 3},
            {0, -2, 0},
            {-3, -3, -3},
    };
    int r = s.calculateMinimumHP(input);
    printf("result: %d\n", r);
}