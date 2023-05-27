//
// https://leetcode.com/problems/restore-ip-addresses/
//

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.length();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1)); // store valid segments
        vector<string> results;
        vector<string> tmp;
        recur(results, tmp, s, 0, dp);
        return results;
    }

    void recur(vector<string> & results, vector<string> & tmp, string & s, int cur, vector<vector<int>> & dp) {
        if (cur == s.length()) {
            if (tmp.size() == 4) {
                string r;
                r.append(tmp[0]);
                for (int i = 1; i < 4; i++) {
                    r.append(".");
                    r.append(tmp[i]);
                }
                results.push_back(r);
            }
            return;
        }
        if (tmp.size() == 4)
            return;
        int l = cur;
        int r = l+1;
        if (tmp.size() == 3)
            r = s.length();
        for (; r <= s.length() && r-l <= 3; r++) {
            if (dp[l][r] == 0)
                continue;
            if (dp[l][r] == -1)
                dp[l][r] = validseg(s, l, r);
            if (dp[l][r] == 1) {
                tmp.push_back(s.substr(l, r-l));
                recur(results, tmp, s, r, dp);
                tmp.pop_back();
            }
        }
    }

    bool validseg(string & s, int l, int r) {
        if (r-l > 1 && s[l] == '0') // .011. not allowed but '.0.' is ok
            return false;
        int val =  s[l] - '0';
        for (int i = l+1; i < r; i++) {
            val *= 10;
            val += s[i] - '0';
            if (val > 255)
                return false;
        }
        if (val < 0 || val > 255)
            return false;
        return true;
    }
};

int main() {
    Solution s;
    vector<string> results = s.restoreIpAddresses("256101");
    for (auto s : results)
        cout << s << endl;
}