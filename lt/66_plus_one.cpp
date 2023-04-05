//
// https://leetcode.com/problems/plus-one/description/
// Solution: big int addition. mind the possible carry digits before most significant digits
// https://leetcode.com/problems/add-binary/description/
// Solution:
//

#include <vector>
#include <cstdio>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool carry = false;
        for (int i = digits.size()-1; i >= 0; i--) {
            if (digits[i] < 9) {
                digits[i]++;
                carry = false;
                return digits;
            } else {
                digits[i] = 0;
                carry = true;
                continue;
            }
        }
        if (carry) {
            digits.insert(digits.begin(), 1);
        }
        return digits;

    }
    string addBinary(string a, string b) {
        if (a.length() < b.length()) {
            a.swap(b);
        }
        bool carry = false;
        for (int i = b.length()-1; i >= 0; i--) {
            int j = i + a.length()-b.length();
            if (a[j] == '0' && b[i] == '0') {
                if (carry) {
                    a[j] = '1';
                    carry = false;
                }
            } else if (a[j] == '0' && b[i] == '1' || a[j] == '1' && b[i] == '0') {
                if (carry) {
                    a[j] = '0';
                } else {
                    a[j] = '1';
                }
            } else if (a[j] == '1' && b[i] == '1' ) {
                if (carry) {
                    a[j] = '1';
                } else {
                    a[j] = '0';
                }
                carry = true;
            }
        }
        if (!carry) {
            return a;
        }
        for (int i = a.length()-b.length()-1; i >=0; i--) {
            if (a[i] == '0') {
                a[i] = '1';
                carry = false;
                break;
            } else {
                a[i] = '0';
                carry = true;
            }
        }
        if (carry) {
            a.insert(a.begin(), '1');
        }
        return a;
    }
};

int main() {
    Solution s;
    vector<int> in = {0,9,9,9};
    vector<int> result = s.plusOne(in);
//    for (int i = 0; i < result.size(); i++) {
//        printf("%d", result[i]);
//    }

    string rstr = s.addBinary("111", "110");
    printf("addition result: %s", rstr.c_str());
    printf("\n");
}