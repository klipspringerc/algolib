//
// https://leetcode.com/problems/wildcard-matching/
// wildcard matching support ? and * symbols

// room for optimization? DP not useful since its tail recursion
// worst case scenario: one recursion for each charactor in p

// an interesting greedy solution http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        string np(p.length(), ' ');
        int ptr = 0;
        int rs = s.length()-1;
        int rp = p.length()-1;
        if (s.length() > 0 && p.length() > 0) {
            while (rs >= 0 && rp >= 0 && p[rp] != '*') {
                if (p[rp] == '?' || p[rp] == s[rs]) {
                    rp--;
                    rs--;
                } else {
                    return false;
                }
            }
        }
        if (rs == -1 && rp == -1)
            return true;
        for (int i = 0; i < p.length(); i++) {
            if (p[i]!='*') {
                np[ptr++] = p[i];
            } else {
                if (ptr > 0 && np[ptr-1] == '*')
                    continue;
                else {
                    np[ptr++] = p[i];
                }
            }
        }
        cout << "parsed pattern " << np.substr(0, ptr) << endl;
        np = np.substr(0, ptr);
        vector<vector<int>> dp (s.length()+1, vector<int>(np.length()+1, -1));
        vector<int> concrete_count(np.size(), 0);
        // record the min number of characters after each * for early termination
        int count = 0;
        for (int i = np.length()-1; i >= 0; i--) {
            if (np[i] != '*')
                count ++;
            else
                concrete_count[i] = count;
        }
        return matchRecur(s, np, 0, 0, concrete_count, dp);
    }

    bool matchRecur(string s, string p, int is, int ip, vector<int> & concrete_count, vector<vector<int>> & dp) {
        if (is == s.length() && ip == p.length())
            return true;
        if (ip == p.length())
            return false;
        if (is == s.length() && ip != p.length()-1 && p[ip] != '*')
            return false;
        if (dp[is][ip] != -1)
            return (dp[is][ip] > 0);
        if (p[ip] != '*' && p[ip] != '?') {
            if (p[ip] == s[is]) {
                dp[is][ip] = matchRecur(s, p, is+1, ip+1, concrete_count, dp);
                return (dp[is][ip] > 0);
            } else  {
                dp[is][ip] = 0;
                return false;
            }
        }
        if (p[ip] == '?') {
            dp[is][ip] = matchRecur(s, p, is+1, ip+1, concrete_count, dp);
            return (dp[is][ip] > 0);
        }
        if (p[ip] == '*') {
            if (ip == p.length()-1)
                return true;
            // * could match empty sequence
            for (int idx = is; idx <= s.length(); idx++) {
                if (s.length() - idx < concrete_count[ip])
                    continue;
//                cout << "testing at " << idx << " " << ip+1  << endl;
                if (matchRecur(s, p, idx, ip+1, concrete_count, dp)) {
//                    cout << "match recur at " << idx << " " << ip+1 << " returns true" << endl;
                    return true;
                } else {
                    dp[idx][ip+1] = 0;
                }
            }
        }
        dp[is][ip] = 0;
        return false;
    }
};

int main () {
    Solution s;
    cout << s.isMatch("2", "") << endl;
}