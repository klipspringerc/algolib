//
// https://leetcode.com/problems/palindrome-partitioning/description/
//

#include <vector>
#include <cstdio>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<vector<vector<string>>> dp(s.length());  // record sub sequences ending at position i
        for (int i = 0; i < s.length(); i++) {
            for (int j = i+1; j < s.length(); j++) {
                int l = i, r = j-1;
                bool isPal = true;
                while (l < r) {
                    if (s[l]!=s[r]) {
                        isPal=false;
                        break;
                    }
                    l++;
                    r--;
                }
                if (isPal) {
                    if (i == 0) {
                        vector<string> seq = {s.substr(i, j-i)};
                        dp[j-1].push_back(seq);
                    } else {
                        vector<vector<int>> cached = dp[i-1];
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
};

int main() {
    Solution s;
    vector<vector<string>> r =  s.partition("aab");
    for (int i = 0; i < r.size(); i++) {
        printf("[");
        for (int j = 0 ; j < r[i].size(); j++) {
            printf("%s, ", r[i][j].c_str());
        }
        printf("]\n");
    }
}