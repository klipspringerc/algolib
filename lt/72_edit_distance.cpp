//
// https://leetcode.com/problems/edit-distance/description/
// Solution: DP - Distance of prefix substring as states
//   https://web.stanford.edu/class/cs124/lec/med.pdf
// Key to edit distance is alignment.
//   INTE*NTION
//   *EXECUTION
// Each state D(i,j) represents
// the minimum edit distance for prefix length i of string A and prefix length j of string B
// if char at i & j is the same, then D(i,j) == D(i-1,j-1)
// else, D(i,j) = 1 + min (D(i,j-1), D(i-1,j)) // 1 addition op on either
//              = 1 + D(i-1, j-1) // 1 replace op
//  Cost("pbs", "pes") = min of :
//      - Cost("pb", "pe")
//      - Cost("pbs", "pe") +1
//      - Cost("pb", "pes") +1
//  Cost("pbs", "pep") = min of :
//      - Cost("pb", "pe") + 1
//      - Cost("pbs", "pe") +1
//      - Cost("pb", "pep") +1
// key observation here is the D(i,j) would not be derived from D(i', j')
// where either i' or j' is larger than i or j.
// add op and remove op is symmetric

// Example
// Step1 D(1,0) = 1, equivalent to remove `I` from word1 or add `I` to word2
// I
// *
// Step2 D(4,3) = D(3,2) + 0 = 3  (same `E`)
// INTE
// *EXE
// Step3 D(4,4) = D(4,3) + 1 = 4, equivalent to add `C` to word 1 or delete 'C' from word2
// INTE*
// *EXEC
// Step4 D(5,5) = D(4,4) + 1 = 5 (replacement)
// INTE*N
// *EXECU
// Step2 D(9,9) = D(5,5) + 0  (same `TION`)
// INTE*NTION
// *EXECUTION

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp;
        int n = word1.size(), m = word2.size();
        // include empty string state, so size [n+1][m+1]
        for (int i = 0; i < n+1; i++) {
            vector<int> nl(m+1);
            dp.push_back(nl);
        }
        // initial dummy state at idx 0, where distance between whole word and empty is word length
        for (int i = 0; i < n+1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i < m+1; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i < n+1; i++) {
            for (int j = 1; j < m+1; j++) {
                int min = dp[i-1][j-1] + 1;  // replacement cost
                // same char, no replacement cost
                if (word1[i-1] == word2[j-1]) {
                    min = dp[i-1][j-1];
                }
                // subtract / addition cost
                if (dp[i-1][j] + 1 < min) {
                    min = dp[i-1][j] + 1;
                }
                if (dp[i][j-1] + 1 < min) {
                    min = dp[i][j-1] + 1;
                }
                dp[i][j] = min;
            }
        }
        return dp[n][m];
    }
};

int main() {
    Solution s;
    printf("result: %d\n", s.minDistance("intention", "execution"));
}
