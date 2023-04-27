//
// https://leetcode.com/problems/different-ways-to-add-parentheses/description/.
// Split into tokens, then recursively collect sum results

#include <string>
#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> results;
        int n = expression.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));
        results = computeRecur(expression, 0, expression.length()-1, dp);
        return results;
    }
    vector<int> computeRecur(string expression, int l, int r, vector<vector<vector<int>>>& dp) {
        vector<int> results;
        if (dp[l][r].size() > 0) {
            return dp[l][r];
        }
        // if substring is a number
        if (r - l <= 1) {
            bool is_num = true;
            int num = 0;
            for (int i = l; i <= r; i++) {
                if (expression[i] < 48 || expression[i] > 57) {
                    is_num = false;
                    break;
                }
                num += int(expression[i]) - 48;
                if (r > i)
                    num *= 10;
            }
            if (is_num) {
                results.push_back(num);
                dp[l][r] = results;
                return results;
            }
        }
        // if substring is still an expression, recursively choose operators as semantic tree root
        for (int i = l+1; i < r; i++) {
            if (expression[i] != '+' && expression[i] != '-' && expression[i] != '*')
                continue;
            vector<int> lft = computeRecur(expression, l, i-1, dp);
            vector<int> right = computeRecur(expression, i+1, r, dp);
            for (int il = 0; il < lft.size(); il++) {
                for (int j = 0; j < right.size(); j++) {
                    int r;
                    switch (expression[i]) {
                        case '+':{
                            r = lft[il] + right[j];
                            break;
                        }
                        case '-': {
                            r = lft[il] - right[j];
                            break;
                        }
                        case '*': {
                            r = lft[il] * right[j];
                            break;
                        }
                    }
                    results.push_back(r);
                }
            }
        }
        dp[l][r] = results;
        return results;
    }
};

int main() {
    Solution s;
    //
    vector<int> r = s.diffWaysToCompute("2-1-1");
    // vector<int> r = s.diffWaysToCompute("2*3-4*5");
    for (vector<int>::iterator itr = r.begin(); itr != r.end(); itr++) {
        printf("%d, ", *itr);
    }
    printf("\n");
}