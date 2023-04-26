//
// https://leetcode.com/problems/decode-ways/description/
// normal backtrack + dp to remember computed partial results
// if no dp -> tle
//

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int valMin = 1;
    int valMax = 26;
    int numDecodings(string s) {
        vector<int> dp = vector<int>(s.length()+1, -1);
        return findWaysRecur(s, dp, 0);
    }
    int findWaysRecur(string s, vector<int> & dp, int step) {
        if (step == s.length())
            return 1;
        if (s[step] == '0')
            return 0;
        if (dp[step] != -1)
            return dp[step];
        int total = 0;
        int cur = 0;
        for (int i = step; i < s.length(); i++) {
            cur += int(s[i]) - 48;
            if (cur < valMin || cur > valMax)
                break;
            total += findWaysRecur(s, dp, i+1);
            if (cur > 2) // no need to *10 if larger than 2
                break;
            cur *= 10;
        }
        dp[step] = total;
        return total;
    }
};

int main() {
    Solution s;
    printf("total ways: %d" , s.numDecodings("111111111111111111111111111111111111111111111"));
}