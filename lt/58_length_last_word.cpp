//
// https://leetcode.com/problems/length-of-last-word/
//

#include <string>
#include <cstdio>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int start = s.length();
        while (start > 0 && s[start-1] == ' ') {
            start--;
        }
        if (start == 0) {
            return 0;
        }
        int end = start-1;
        while (end > 0 && s[end-1] != ' ') {
            end--;
        }
        return start - end;
    }
};

int main() {
    Solution s;
    printf("result: %d", s.lengthOfLastWord("ba"));
}