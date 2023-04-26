//
// https://leetcode.com/problems/unique-binary-search-trees/
//

#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        vector <int> dp(n+1, -1);
        dp[0] = 1;
        dp[1] = 1;
        return countRecur(n, dp);
    }

    int countRecur(int n, vector<int> & dp) {
        int total = 0;
        if (dp[n] != -1)
            return dp[n];
        for (int i = 0; i < n; i++) {
            int left = i-0;
            int right = n-1-i;
            total += countRecur(left, dp) * countRecur(right, dp);
        }
        dp[n] = total;
        return total;
    }
};

int main() {
    Solution s;
    printf("unique bst count: %d\n", s.numTrees(3));
}