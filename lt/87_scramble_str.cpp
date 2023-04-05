//
// https://leetcode.com/problems/scramble-string/
//

#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    unordered_map<string, bool> dup;
    bool isScramble(string s1, string s2) {
        if (s1 == s2)
            return true;
        if (s1.size() != s2.size())
            return false;
        if (s1.size() == 1)
            return false;
        string key = s1 + " " + s2;
        if (dup.count(key) > 0)
            return dup[key];
        // iteratively try each cut-off points
        // either swapped or no swap at this stage.
        // then recursively check each substring.
        for (int i = 1; i < s1.length(); i++) {
            bool noSwapScramble = isScramble(s1.substr(0, i), s2.substr(0,i))
                    && isScramble(s1.substr(i, s1.length()-i), s2.substr(i, s2.length()-i));
            if (noSwapScramble) {
                dup[key] = true;
                return true;
            }
            bool swapScramble = isScramble(s1.substr(0,i), s2.substr(s2.length()-i, i))
                && isScramble(s1.substr(i, s1.length()-i), s2.substr(0, s2.length()-i));
//            printf("separation: %s %s -- %s %s, noswap: %s\n",
//                   s1.substr(0, i).c_str(), s1.substr(i, s1.length()-i).c_str(),
//                   s2.substr(0,i).c_str(), s2.substr(i, s2.length()-i).c_str(),
//                   noSwapScramble?"true":"false");
//            printf("separation: %s %s -- %s %s, swap: %s\n",
//                   s1.substr(0, i).c_str(), s1.substr(i, s1.length()-i).c_str(),
//                   s2.substr(0, s2.length()-i).c_str(), s2.substr(s2.length()-i,i).c_str(),
//                   swapScramble?"true":"false");
            if (swapScramble) {
                dup[key] = true;
                return true;
            }
        }
        dup[key] = false;
        return false;
    }

    bool isScrambleGeneration(string s1, string s2) {
        // lets first try to generate all scrambles of s1
        unordered_set<string> results;
        recur(s1, results);
        for (const string & v : results) {
            printf("%s\n", v.c_str());
        }
        return results.count(s2) > 0;
    }

    void recur(string s, unordered_set<string> & results) {
        results.insert(s);
        for (int i = 1; i < s.length(); i++) {
            unordered_set<string> sub1, sub2;
//            printf("split as %s %s\n", s.substr(0, i).c_str(), s.substr(i, s.length()-i).c_str());
            recur(s.substr(0, i), sub1);
            recur(s.substr(i, s.length()-i), sub2);
            for (const string & v1 : sub1) {
                for (const string & v2: sub2) {
                    results.insert(v1 + v2);
                    results.insert(v2 + v1);
                }
            }
        }
    }
};

int main() {
    Solution s;
    s.isScrambleGeneration("abcde", "abcde");
    printf("scrammable: %s\n",  s.isScramble("abcde", "caebd")? "true":"false");
}