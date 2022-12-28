//
// https://leetcode.com/problems/multiply-strings/
//
// Solution: big integer + string parsing

#include<string>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
    string multiply(string num1, string num2) {
        vector<int> digits1(num1.length());
        vector<int> digits2(num2.length());
        for (int i = num1.length(); i > 0; i--) {
            digits1[i-1] = num1[num1.length() - i] - '0';
        }
        for (int i = num2.length(); i > 0; i--) {
            digits2[i-1] = num2[num2.length() - i] - '0';
        }
        // debug
//        printf("num1 big int :\n");
//        for (int i = 0; i < digits1.size(); i++) {
//            printf("%d ", digits1[digits1.size() - i - 1]);
//        }
//        puts("");
//        printf("num2 big int :\n");
//        for (int i = 0; i < digits2.size(); i++) {
//            printf("%d ", digits2[digits2.size() - i - 1]);
//        }
//        puts("");
        //

        vector<int> r_digits(num1.length() + num2.length());
        for (int i = 0; i < digits1.size(); i++) {
            for (int j = 0; j < digits2.size(); j++) {
                r_digits[i + j] += digits1[i] * digits2[j];
            }
        }
        // debug
//        printf("current big int result:\n");
//        for (int i = 0; i < r_digits.size(); i++) {
//            printf("%d ", r_digits[r_digits.size() - i - 1]);
//        }
//        puts("");
        //
        int carry = 0;
        for (int i = 0; i < r_digits.size(); i++) {
            int tmp = carry + r_digits[i];
            carry = tmp / 10;
            r_digits[i] = tmp % 10;
        }
        string result;
        bool first_non_zero = false; // boolean need explicit initialization in some env
        for (int i = r_digits.size()-1; i >= 0; i--) {
            printf("convert at position %d, first_none_zero: %s, result: %s\n", i, first_non_zero?"true":"false", result.c_str());
            if (!first_non_zero && r_digits[i] > 0) {
                first_non_zero = true;
            }
            if (first_non_zero) {
                result.push_back(char('0' + (r_digits[i])));
            }
        }
        if (!first_non_zero) {
            return "0";
        }
        return result;
    }
};

int main() {
    Solution s;
    printf("%s\n", s.multiply("9133", "12").c_str());
}