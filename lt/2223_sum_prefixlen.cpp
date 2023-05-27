//
// https://leetcode.com/problems/sum-of-scores-of-built-strings/description/
// An application of z-function
// useful visualization of z-function: https://personal.utdallas.edu/~besp/demo/John2010/z-algorithm.html
// the main idea is to reuse common prefix length result from z[l] and z[i-l] to jump start comparison at `i`.
// z[l] gives a range [l-r] where s[l:r] is a replay of s[0:r-l], where z[i-l] could be reused at z[i]

#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long sumScores(string s) {
        // first construct z-array
        int n = s.length();
        vector<int> z(n, 0);  // z[i] stores lcp length between s and suffix starting at s[i]
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i < r) {
                // the segment between s[l: r] is exactly the same with s[0: r-l]
                // so when computing prefix length at s[i], if i < r, could init from z[i-l],
                // which is the common prefix length starting from s[i-l]. computed in previous iteration
                // e.g. the segment s[0: z[i-l]]  was already known to match s[i-l: i-l + z[i-l]]
                // so segment s[i: min(i+z[i-l],  r)] is known to match s[0: min(z[i-l], r-i)]
                // note the z[i] could not init beyond r-i, because only s[l:r] is guaranteed to be the same with s[0:r-l].
                z[i] = min(z[i-l], r-i);
            }
            while (s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            int nr = i + z[i];
            if (nr > r) {
                l = i;
                r = nr;
            }
        }
        // then sum z array value for result score
        long long sum = n;
//        printf("z values: ");
        for (int v : z) {
//            printf(" %d, ", v);
            sum += (long long)(v);
        }
//        printf("\n");
        return sum;
    }
};

int main() {
    Solution s;
    string in = "a";
    for (int i = 0; i < 100000; i++)
        in += "a";
    printf("sum score: %lld\n",s.sumScores(in));
}
