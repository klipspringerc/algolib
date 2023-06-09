//
// https://leetcode.com/problems/stone-game/description/
// easy solution is when pile count is even, who pick first would always win (can force to opponent to pick only odd or even tiles)
// dp is to bottom up: record the max score advantage achievable at each segment [i,j]
// dp[i, j] = (p[j] - dp[i,j-1], p[i] - dp[i+1,j]) // note the min max pattern here
// at the bottem level, e.g. dp[2,3] = min (p[2] - p[3], p[3] - p[2])

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n,INT_MIN));
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }
        // better way to calculate at one go.
        for (int d = 1; d < n; d++)
            for (int i = 0; i < n - d; i++)
                dp[i][i + d] = max(piles[i] - dp[i + 1][i + d], piles[i + d] - dp[i][i + d - 1]);
//        for (int i = 0; i < n ; i++) {
//            for (int j = i+1; j < n; j++) {
//                dp[i][j] = dp[i][j] == INT_MIN ? piles[j]-dp[i][j-1] :  max(dp[i][j], piles[j]-dp[i][j-1]);
//                for (int k = i-1; k >=0; k--) {
//                    dp[k][j] = dp[k][j] == INT_MIN ? piles[k]-dp[k+1][j] :  max(dp[k][j], piles[k]-dp[k+1][j]);
//                }
//            }
//        }
        return dp[0][n-1] > 0;
    }
};

int main() {
    Solution s;
    vector<int> in = {3,7,2,3};
    cout << s.stoneGame(in) << endl;
}