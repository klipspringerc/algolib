//
// Created by KSC on 12/9/22.
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
//

#include<cstdio>
#include<cstdlib>
#include<string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        // kmp preprocess to get the longest common prefix array
        // lcp for `abcab` at index 4 is `ab`, since it is both the suffix and the prefix.
        // so if pattern matching failed at index 5, it could fall back to compare index 3 instead of start from index 0 again
        int *lcp = (int*)malloc(sizeof(int) * needle.length());
//        int *lcp = new int(needle.length());
        int len = int(needle.length());
        // need explicit init to zero for leetcode
        for (int i = 0; i < len; i++) {
            lcp[i] = 0;
        }
        int i = 1;
        int j = 0;
        while (i < len) {
            if (needle[i] == needle[j]) {
                lcp[i] = j+1; // record the current least common prefix length
                i++;
                j++;
            } else {
                if (j > 0) {
                    j = lcp[j-1]; // when has matching prefix, fallback to the lcp of current matching prefix
                    // here we are using the same method as in actual pattern matching
                } else {
                    lcp[i] = 0; // if no matching, record current lcp to zero.
                    i++;
                }
            }
        }
//        printf("fallback lcp: ");
//        for (i = 0; i < len; i++) {
//            printf("%d ", lcp[i]);
//        }
//        printf("\n");
        i = 0;
        j = 0;
        len = int(haystack.length());
        while (i < len) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
                if (j == needle.length()) {
                    return int(i - needle.length());
                }
            } else {
                if (j > 0) {
                    while (needle[j] != haystack[i] && j > 0) {
                        j = lcp[j-1];
                    }
                } else {
                    i++;
                }
            }
        }
        return -1;
    }
};

int main(void) {
    Solution s;
    printf("result: %d\n", s.strStr("aaaaa", "bba"));
}
