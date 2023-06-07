//
// https://leetcode.com/problems/remove-invalid-parentheses/description/
// find all unique ways to fix invalid parentheses sequences, return all unique valid fixed strings

// Solution: backtracking, starts removing right parenthesis when right count exceed left count
// remove right parentheses at consecutive positions would result in the same result string
// try all different position, pass the last delete location to avoid duplicates


#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> results;
        recur(s, results, 0, 0, '(', ')');
        return results;
    }

    // either called at start or after a fix, so
    // when recur is called, both lp and rp count would be equal
    // which means we can start counting from groud zero
    void recur(string s, vector<string> & results, int pos, int lastfix, char lp, char rp) {
        int lcount = 0, rcount = 0;
        int i = pos;
        for (; i < s.length(); i++) {
            if (s[i] == lp)
                lcount++;
            else if (s[i] == rp)
                rcount++;
            if (lcount < rcount)
                break;
        }
        if (lcount >= rcount) {
            // when left to right check completes, run reverse check on current string
            // each time we arrive at this line, s should be a different string
            // so restart reverse check from beginning.
            reverse(s.begin(), s.end());
            if (lp == '(') // if forward check alright, reverse string and look for invalid extra '('
                recur(s, results, 0, 0, ')', '(');
            else
                results.push_back(s); // reverse check complete, store the result
        } else {
            int idx = i; // new position
            for (int i = lastfix; i <= idx; i++) {
                if (s[i] == rp && (i == lastfix || s[i-1] != rp)) {
                    // because s length is reduced by 1, so pass idx and i instead of idx+1 and i+1.
                    // i stores this fix position, idx stores parse progress location.
                    recur(s.substr(0, i) + s.substr(i+1, s.length()-i), results, idx, i, lp, rp);
                }
            }
        }
    }
};

int main() {
    Solution s;
    vector<string> rs = s.removeInvalidParentheses("()())()");
    for (auto s : rs)
        cout << s << endl;
}
