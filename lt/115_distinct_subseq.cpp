//
// https://leetcode.com/problems/distinct-subsequences/
//

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        if (s == t)
            return 1;
        int n = s.length();
        int m = t.length();
        vector<vector<unsigned long long>> dp(m, vector<unsigned long long>(n, 0));
        for (int i = 0; i < n; i++) {
            if (s[i] == t[0])
                dp[0][i] = 1;
        }
        for (int k = 1; k < m; k++) {
            unsigned long long cur_sum = 0;
            for (int i = 0; i < n; i++) {
                if (s[i] == t[k]) {
                    dp[k][i] = cur_sum;
                }
                cur_sum += dp[k-1][i];
                if (n-i < m-k)
                    break;
            }
        }
        unsigned long long r = 0;
        for (auto c : dp[m-1])
            r += c;
        return int(r);
    }
};

int main() {
    Solution s;
    cout << s.numDistinct("rabbbit", "rabit") << endl;

}