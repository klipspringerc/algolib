//
// Created by Cui Shengping on 2020/3/29.
// https://leetcode.com/problems/generate-parentheses/
//


#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string tmp;
        backtrack(ans, n, 0, 0, tmp);
        return ans;
    }
    void backtrack(vector<string> &ans, int n, int open, int close, string &tmp) {
        if (open == n & close ==n) {
            ans.push_back(tmp);
            return;
        }
        if (open < n) {
            tmp.push_back('(');
            backtrack(ans, n, open+1, close, tmp);
            tmp.pop_back();
        }
        if (open > close) {
            tmp.push_back(')');
            backtrack(ans, n, open, close+1, tmp);
            tmp.pop_back();
        }
    }
};


int main() {
    Solution s;
    vector<string> ans = s.generateParenthesis(3);
    for (vector<string>::iterator it = ans.begin(); it != ans.end(); it++) {
        printf("%s\n", it->c_str());
    }
    return 0;
}