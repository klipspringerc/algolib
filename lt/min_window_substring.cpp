#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


/*
76. Minimum Window Substring

https://leetcode.com/problems/minimum-window-substring/

Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.


Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.


Follow up: Could you find an algorithm that runs in O(m + n) time?
 */

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> ds;
        unordered_map<char, int> ss;
        for (int i = 0; i < t.size(); i++) {
            ds[t[i]]++;
        }
        int count = 0;
        int minL = 0;
        int minR = s.size()-1;
        int l = 0;
        int r = 0;
        bool found = false;
        for (; r < s.size(); r++) {
            char rightChar = s[r];
            if (ds.find(rightChar) == ds.end()) {
                continue;
            }
            int num = ds[rightChar];
            if (num > 0) {
                if (++ss[rightChar] == num) {
                    count++;
                }
            } else {
                continue;
            }
            for (; count == ds.size(); l++) {
                found = true;
                if (r - l < minR - minL) {
                    minR = r;
                    minL = l;
                }
                char leftChar = s[l];
                if (ds.find(leftChar) == ds.end()) {
                    continue;
                }
                int num = ds[leftChar];
                if (num > 0) {
                    if (--ss[leftChar] < num) {
                        count--;
                    }
                }
            }
        }
        if (!found) {
            return "";
        }
        return s.substr(minL, minR-minL+1);
    }
};

int main() {
    Solution s;
    string result = s.minWindow("adbefggcaaabaac", "aaabc");
    printf("the result is: %s\n", result.c_str());
}

