//
// https://leetcode.com/problems/interleaving-string/
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();
        if (n == 0 && m == 0 && s3.length() == 0)
            return true;
        if (n+m != s3.length())
            return false;
        vector <vector<bool>> dp(n+1, vector<bool>(m+1, false));
        bool match = true;
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] != s3[i]) {
                match = false;
            }
            dp[i+1][0] = match;
        }
        match = true;
        for (int i = 0; i < s2.length(); i++) {
            if (s2[i] != s3[i]) {
                match = false;
            }
            dp[0][i+1] = match;
        }
        for (int i = 1; i <=n; i++) {
            for (int j = 1; j <= m; j++) {
                if (dp[i][j-1] && s2[j-1] == s3[i+j-1] || dp[i-1][j] && s1[i-1] == s3[i+j-1]) {
                    dp[i][j] =true;
                }
            }
        }

        return dp[n][m];
    }
};

int main() {
    Solution s;
    cout << s.isInterleave("", "", "") << endl;
}