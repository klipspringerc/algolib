//
// https://leetcode.com/problems/minimum-window-substring/description/
// Sliding window, record occurrence of chars in string t, then maintain the same occurrence
// count in the window. Record minimum window length through the string
//

#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tMap;
        unordered_map<char, int> windowMap;
        for (int i = 0; i < t.length(); i++) {
            tMap[t[i]]++;
        }
        int count = tMap.size();
//        printf("tmap size %lu\n", tMap.size());
//        for (const pair<char, int> & kv : tMap) {
//            printf("    %c: %d\n", kv.first, kv.second);
//        }
        int l = 0;
        int min = s.size()+1;
        int minIdx = -1;
        for (int r=0; r < s.length(); r++) {
            if (tMap.count(s[r]) > 0) {
                windowMap[s[r]]++;
                if (windowMap[s[r]] == tMap[s[r]]) {
                    count--;
                }
//                printf("iterate to l-r: %d-%d, window map size %lu\n", l, r, windowMap.size());
//                for (const pair<char, int> & kv : windowMap) {
//                    printf("    %c: %d\n", kv.first, kv.second);
//                }
                while (count == 0) {
                    if (r-l < min) {
                        min = r-l+1;
                        minIdx = l;
                    }
                    if (windowMap.count(s[l]) > 0) {
                        windowMap[s[l]]--;
                        if (windowMap[s[l]] == tMap[s[l]]-1) {
                            count++;
                        }
                    }
                    l++;
                }
            }
        }
        if (minIdx == -1) {
            return "";
        }
        return s.substr(minIdx, min);
    }
};


int main() {
    Solution s;
    string result = s.minWindow("adbefggcaaabaac", "aaabc");
    printf("the result is: %s\n", result.c_str());
}