//
// https://leetcode.com/problems/roman-to-integer/
// Created by KSC on 4/10/22.
//

#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            switch (s[i]) {
                case 'I':
                    if (i + 1 == s.size()) {
                        num++;
                    } else if (s[i+1] == 'V' || s[i+1] == 'X') {
                        num--;
                    } else {
                        num++;
                    }
                    break;
                case 'X':
                    if (i+1 == s.size()) {
                        num += 10;
                    } else if (s[i+1] == 'L' || s[i+1] == 'C') {
                        num -= 10;
                    } else {
                        num += 10;
                    }
                    break;
                case 'C':
                    if (i+1 == s.size()) {
                        num += 100;
                    } else if (s[i+1] == 'D' || s[i+1] == 'M') {
                        num -= 100;
                    } else {
                        num += 100;
                    }
                    break;
                case 'M':
                    num += 1000;
                    break;
                case 'L':
                    num += 50;
                    break;
                case 'V':
                    num += 5;
                    break;
                case 'D':
                    num += 500;
            }
        }
        return num;
    }
};

int main() {
    Solution s;
    int r = s.romanToInt("DCXXI");
    printf("result: %d\n", r);
}
