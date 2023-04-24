//
// https://leetcode.com/problems/longest-common-subsequence/description/
// longest common subsequence
// use DP 2d-array. dp[i][j] denote the current longest subsequence ending with text1[i] and text2[j]
//
//

#include <vector>
#include <string>
using namespace std;

typedef struct Trace {
    int x;
    int y;
    char v;
} Trace ;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();

        vector<vector<Trace>> tr = vector<vector<Trace>>(m, vector<Trace>(n, {0}));
        vector<vector<int>> dp = vector<vector<int>>(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cur_max = 0;
                if (i > 0 & j > 0) {
                    cur_max = dp[i-1][j-1];
                }
                if (text1[i] == text2[j]) {
                    cur_max++;
                    tr[i][j] = {i-1,j-1,text1[i]};
                }
                // if not equal , could simply take the larger between left and upper neighbors
//                cur_max = max(dp[i-1][j], dp[i][j-1]);
                if (i > 0 && dp[i-1][j] > cur_max) {
                    cur_max = dp[i-1][j];
                    tr[i][j] = {i-1, j, '\0'};
                }
                if (j > 0 && dp[i][j-1] > cur_max) {
                    cur_max = dp[i][j-1];
                    tr[i][j] = {i, j-1, '\0'};
                }
                dp[i][j] = cur_max;
            }
        }

        // trace back to print the substring
        char* rs = (char*) malloc(sizeof (char) * dp[m-1][n-1]);
        int idx = dp[m-1][n-1]-1;
        int i = m-1;
        int j = n-1;
        while (i >= 0 && j >= 0) {
            if (tr[i][j].v != '\0') {
                printf("%c ", tr[i][j].v);
                rs[idx] = tr[i][j].v;
                idx--;
            } else {
                printf("<s %c %d %d> ", tr[i][j].v, i, j);
            }
            int new_i = tr[i][j].x;
            j = tr[i][j].y;
            i = new_i;
        }
        printf("\n %s \n", rs);
        return dp[m-1][n-1];
    }
};

int main() {
    Solution s;
    printf("result: %d\n" , s.longestCommonSubsequence("abcdefgd", "acfgda"));
}