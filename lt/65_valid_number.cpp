//
// https://leetcode.com/problems/valid-number/description/
// Solution: pure if else, need to check every enforced rules
//

#include <string>
#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        bool seenNumber = false;
        bool afterE = false;
        bool seenDecimal = false;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                seenNumber = true;
                continue;
            } else if (c == 'e' || c == 'E') {
                //
                if (!seenNumber || afterE || i == s.length()-1) {
                    return false;
                }
                s[i] = 'e';
                afterE = true;
            } else if (c == '.') {
                // could appear at the end or start of number, but not repetitively or after e
                if (seenDecimal || afterE) {
                    return false;
                }
                seenDecimal = true;
            } else if (c == '+' || c == '-') {
                // +- sign could be at the start , or follows `e`
               if (i != 0 && s[i-1] != 'e') {
                   return false;
               }
               if (i == s.length()-1) {
                   return false;
               }
            } else {
                return false;
            }
        }
        return seenNumber;
    }
};

int main() {
    Solution s;
    vector<string> input = {
//            "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"
            "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", "4e+"
    };
    for (int i = 0; i < input.size(); i++) {
        string str = input[i];
        printf("%s is number: %s\n", str.c_str(), s.isNumber(str)? "true" : "false");
    }
}