//
// https://leetcode.com/problems/dungeon-game/
//


#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    // this is an example of why top-down approach would not work:
    // at each local decision, there is no way to know what chosen path would cost
    // instead, we do bottom up so at each decision, the minimum hp required to go right/down is known
    int calculateMinimumHPTopDownWA(vector<vector<int>>& dungeon) {
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

    // bottom up approach
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<int> dp(n); // stores minimum health required;
        dp[n-1] = 1-dungeon[m-1][n-1]; // require at least 1 health at the end.
        // the key is here, even if there are large positive in the path that allows negative health
        // we still need to keep health positive all the time!
        if (dp[n-1] <= 0)
            dp[n-1] = 1;
        for (int i = n-2; i>=0; i--) {
            dp[i] = dp[i+1] - dungeon[m-1][i];
            if (dp[i] <=0 )
                dp[i] = 1; // the repetitive checking could be avoided by setting boundary to INT_MAX, we repeatedly do this to save memory
        }
        for (int i = m-2; i>= 0; i--) {
            dp[n-1] = dp[n-1] - dungeon[i][n-1];
            if (dp[n-1] <= 0) {
                dp[n-1] = 1;
            }
            for (int j = n-2; j >= 0; j--) {
                dp[j] = min(dp[j+1], dp[j]) - dungeon[i][j];
                if (dp[j]<= 0)
                    dp[j] = 1;
            }
        }
        return dp[0];
    }
};

int main() {
    Solution s;
    vector<vector<int>> input = {
//            {-10},
            {2},
            {-11}
//            {-2,-3,3},
//            {-5,-10,1},
//            {10,30,-5},
//            {1, -3, 3},
//            {0, -2, 0},
//            {-3, -3, -3},
    };
    int r = s.calculateMinimumHP(input);
    printf("result: %d\n", r);
}