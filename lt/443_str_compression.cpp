//
// Created by KSC on 1/5/23.
//

#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int ptr = 0;
        char cur = chars[0];
        int count = 1;
        for (int i = 1; i < chars.size(); i++) {
            if (chars[i] == cur) {
                count++;
                if (count == 2) {
                    ptr++;
                }
            }
            if (chars[i] != cur || i+1 == chars.size()) {
                bool diff_char = false;
                if (chars[i] != cur)
                    diff_char = true;

                if (count > 1) {
                    int width = 1;
                    while (pow(10, width) <= count)
                        width++;
                    ptr += (width-1);
                    for (int r = 0; r < width; r++) {
                        chars[ptr-r] = 48 + count % 10;
                        count /= 10;
                    }
                }
                if (diff_char) {
                    ptr++;
                    chars[ptr] = (cur = chars[i]);
                    count = 1;
                }
            }
        }
        return ptr+1;
    }
};

int main() {
    vector<char> input = {'a', 'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'};
//    vector<char> input = {'a', 'a'};
    Solution s;
    int rl = s.compress(input);
    printf("result length: %d\n", rl);
    int count = 0;
    for (char c : input) {
        printf("%c ", c);
        if ((++count) == rl)
            break;
    }
    printf("\n");
}