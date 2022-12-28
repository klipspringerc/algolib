//
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
//
// Solution: variation of sliding window
// - all words are in same length, but the substring may start at any position
// - so we start our slide window from index 0, 1, 2, ... word_length-1
// - if we encounter the same word more than desired times inside window, shrink the window until the extra occurrence of this word is removed.
//   - note that all words are off the same length, and there's no way the result contains more than desired occurrence.

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <cstdio>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> results;
        if (words.size() == 0) {
            return results;
        }
        int word_length = words[0].length();
        if (s.length() < word_length) {
            return results;
        }
        unordered_map<string, int> occurs;
        for (int i = 0; i < words.size(); i++) {
            occurs[words[i]]++;
        }

        // debug
//        printf("occurrence size %ld, count:\n", occurs.size());
//        for (const pair<string, int>& kv : occurs) {
//            printf("    %s: %d\n", kv.first.c_str(), kv.second);
//        }
        //

        // sliding window, try grids offset from 0 to word-length-1
        for (int offset = 0; offset < word_length; offset++) {
            int l = offset; // window would shrink from LHS one word_length a time, so separate variable
            unordered_map<string, int> tmp;
            int match_count = 0;
            for (int j = l; j < s.length(); j += word_length) {
                if (l + word_length * words.size() > s.length()) {
                    break;
                }

                // debug
//                printf("position l: %d r: %d + word_length, occurs size %ld\n", l, j, occurs.size());
//                printf("tmp status:\n");
//                for (const pair<string, int>& kv : tmp) {
//                    printf("    %s: %d\n", kv.first.c_str(), kv.second);
//                }
//                printf("occurs status:\n");
//                for (const pair<string, int>& kv : occurs) {
//                    printf("    %s: %d\n", kv.first.c_str(), kv.second);
//                }
//                printf("current match count: %d\n", match_count);
                //

                string cur = s.substr(j, word_length);
                // if use occurs[cur], this would automatically creates an entry <cur:0> !
                if (occurs.count(cur) > 0) {
                    tmp[cur]++;
                    if (tmp[cur] == occurs[cur]) {
                        match_count++;
                        // printf("found match at %d, word %s, occurrence %d, match_count %d, equals %s\n", j, cur.c_str(), tmp[cur], match_count, (match_count == int(occurs.size()))? "true":"false");
                        // found result, move l by word_length and look for the next match
                        if (match_count == int(occurs.size())) {
                            // printf("found result at %d: %s\n", l, s.substr(l, word_length * words.size()).c_str());
                            results.push_back(l);
                            tmp[s.substr(l, word_length)]--;
                            match_count--;
                            l += word_length;
                        }
                    } else if (tmp[cur] > occurs[cur]) {
                        printf("repetitive word %s, start shrinking\n", cur.c_str());
                        // since result cannot contain extra occurrence,
                        // pop left until extra occurrence is removed, then continue RHS matching
                        while(true) {
                            string leftmost_word = s.substr(l, word_length);
                            tmp[leftmost_word]--;
                            if (tmp[leftmost_word] == occurs[leftmost_word]-1) {
                                match_count--; // no longer satisfy occurrence, reduce match count.
                            }
                            l += word_length;
                            if (leftmost_word == cur) {
                                break;
                            }
                        }
                        printf("left boundary shrunk to position %d\n", l);
                    }
                } else {
                    // no matching on RHS, restart window, reset l to next position of j
                    l = j+word_length;
                    tmp.clear();
                    match_count = 0;
                }
            }
        }
        return results;
    }
};


int main() {
    Solution s;
    vector<string> words = {"abc", "def", "abd"};
    vector<int> results = s.findSubstring("defabdabcdefabdabc", words);
    for (vector<int>::iterator it = results.begin(); it != results.end(); it++) {
        printf("%d\n", *it);
    }
}