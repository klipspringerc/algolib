//
// https://leetcode.com/problems/palindrome-partitioning/description/
//

#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<int>> pl (n, vector<int>(n, 0)); // 0 unknown, 1 false, 2 true
        vector<vector<vector<string>>> dp(s.length());  // record sub sequences ending at position i
        for (int i = 0 ; i < n ; i++) {
            pl[i][i] = 2;
        }
        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && dp[i-1].size() == 0) {
                // if dp[i-1] is empty, then no valid sequence of palindromes ending at idx i-1, so no valid results from current i.
                continue;
            }
            for (int j = i+1; j < s.length()+1; j++) {
                bool isPal = true;
                //use pl to cache palindrome result
                if (pl[i][j-1] != 0) {
                    if (pl[i][j-1] == 1)
                        isPal = false;
                } else {
                    int l = i, r = j-1;
                    while (l < r) {
                        if (s[l]!=s[r]) {
                            isPal=false;
                            break;
                        }
                        l++;
                        r--;
                    }
                    if (isPal) {
                        pl[i][j-1] = 2;
                    } else {
                        pl[i][j-1] = 1;
                    }
                }
                if (isPal) {
                    if (i == 0) {
                        vector<string> seq = {s.substr(i, j-i)};
                        dp[j-1].push_back(seq);
                    } else {
                        vector<vector<string>> cached = dp[i-1];
                        for (int idx = 0; idx < cached.size(); idx++) {
                            vector<string> seq(cached[idx]);
                            seq.push_back(s.substr(i, j-i));
                            dp[j-1].push_back(seq);
                        }
                    }
                }
            }
        }
        return dp[s.length()-1];
    }



    int minCutDP(string s) {
        int n = s.length();
        vector<vector<int>> pl (n, vector<int>(n, 0)); // 0 unknown, 1 false, 2 true
        vector<int> dp(n, INT_MAX);  // record sub sequences ending at position i
        for (int i = 0 ; i < n ; i++) {
            pl[i][i] = 2;
        }
        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && dp[i-1] == INT_MAX) {
                // if dp[i-1] is empty, then no valid sequence of palindromes ending at idx i-1, so no valid results from current i.
                continue;
            }
            for (int j = i+1; j < s.length()+1; j++) {
                bool isPal = true;
                //use pl to cache palindrome result
                if (pl[i][j-1] != 0) {
                    if (pl[i][j-1] == 1)
                        isPal = false;
                } else {
                    int l = i, r = j-1;
                    while (l < r) {
                        if (s[l]!=s[r]) {
                            isPal=false;
                            break;
                        }
                        l++;
                        r--;
                    }
                    if (isPal) {
                        pl[i][j-1] = 2;
                    } else {
                        pl[i][j-1] = 1;
                    }
                }
                if (isPal) {
                    if (i == 0) {
                        dp[j-1] = 0;
                        if (j == n)
                            return 0;
                    } else {
                        // minimum cut of prefix sequence ending at position i-1
                        int prefix_min = dp[i-1];
                        if (prefix_min + 1 < dp[j-1]) {
                            dp[j-1] = prefix_min +1;
                        }
                    }
                }
            }
        }
        return dp[n-1];
    }

    int minCut(string s) {
        int n = s.length();
        if (n == 1)
            return 0;
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        vector<vector<bool>> pl (n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (i == j) {
                    pl[i][j] = true;
                } else if (i == j+1) {
                    pl[i][j] = (s[i] == s[j]);
                } else {
                    if (s[i] == s[j]) {
                        pl[i][j] = pl[i-1][j+1];
                    }
                }
            }
        }
        for (int i = 1; i < n; i++) {
            if (pl[i][0]) {
                dp[i] = min(dp[i], 0);
                continue;
            }
            for (int j = 1; j <= i; j++) {
                if (pl[i][j] && dp[j-1] < INT_MAX) {
                    dp[i] = min(dp[i], (dp[j-1] + 1));
                }
            }
        }
        return dp[n-1];
    }
};

int main() {
    Solution s;
//    vector<vector<string>> r =  s.partition("ababababa");
//    for (int i = 0; i < r.size(); i++) {
//        printf("[");
//        for (int j = 0 ; j < r[i].size(); j++) {
//            printf("%s, ", r[i][j].c_str());
//        }
//        printf("]\n");
//    }
    printf("min cut: %d\n", s.minCut("ababadaba"));
}