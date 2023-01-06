//
// https://leetcode.com/problems/permutation-sequence/description/
// during recursion, the number of permutation in each sub tree is known
// only follow through branches that contains k-th permutation, skip over branches that does not.
// note: permutation are required to be in string order
//       so sort suffix string at each step

#include <string>
#include <cstdio>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        unordered_map<char, int> char_set;
        unordered_map<int, int> perm_count;
        int perm_total = 1;
        for (int i = 1; i < n; i++) {
            perm_total *= i;
            perm_count[i] = perm_total;
//            printf("perm map %d!=%d\n", i, perm_total);
        }
        string result;
        for (int i = 0; i < n; i++) {
            result.push_back('1' + i);
        }
        return solve(perm_count, char_set, result, 0, k, 0);
    }

    string solve(unordered_map<int, int> & perm_count, unordered_map<char, int> & char_set, string base, int step, int target, int total) {
        if (step == base.length()-1) {
            return base;
        }
        int replace_count = 0;
        if (step > 0 ) {
            // re-arrange string order at each step
            for(int i = 0; i < base.length(); i++) {
                char tmp = '1' + i;
                if (char_set.count(tmp) == 0) {
                    base[step+replace_count] = tmp;
                    replace_count++;
                }
            }
        }
        int cur_count = perm_count[base.length() - step - 1];
        int step_total = total;
//        printf("at step %d with step_total %d, cur_count is %d, cur str %s\n", step, step_total, cur_count, base.c_str());
        for (int i = step; i < base.length(); i++) {
            if (cur_count + step_total >= target) {
                char tmp = base[i];
                base[i] = base[step];
                base[step] = tmp;
                char_set[tmp] = 1;
//                printf("  swap between location %d and %d, current str %s \n", step,i, base.c_str());
                return solve(perm_count, char_set, base, step+1, target, step_total);
            } else {
                step_total += cur_count;
//                printf("  skip between location %d and %d, total increased to %d\n", step,i, step_total);
                continue;
            }
        }
        return "";
    }
};

int main() {
    Solution s;
    printf("%s\n", s.getPermutation(1, 1).c_str());
}