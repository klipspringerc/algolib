//
// https://leetcode.com/problems/n-queens/
// https://leetcode.com/problems/n-queens-ii/
// Solution: backtrack along rows
// boolean array to record occupancy at column and diagonals (\-diagonal: 4-r + c -1, /-diagonal: r+c)
//

#include <vector>
#include <cstdio>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        // vector<bool> col(n), diag(2*n-1), anti_diag(2*n-1); or malloc also works
        bool* cols = new bool[10];
        for (int i = 0; i < n; i++) cols[i] = false;
        bool* down_diags = new bool[20];  //    \-diagonal
        bool* up_diags = new bool[20];  //    /-diagonal
        for (int i = 0; i < 2*n-1; i++) {
            down_diags[i] = false;
            up_diags[i] = false;
        }
        vector<int> pos(n);
        vector<vector<string>> results;
        solve(results, pos, n, 0, cols, down_diags, up_diags);
        return results;
    }

    int totalNQueens(int n) {
        bool* cols = new bool[10];
        for (int i = 0; i < n; i++) cols[i] = false;
        bool* down_diags = new bool[20];  //    \-diagonal
        bool* up_diags = new bool[20];  //    /-diagonal
        for (int i = 0; i < 2*n-1; i++) {
            down_diags[i] = false;
            up_diags[i] = false;
        }
        return count(n, 0, cols, down_diags, up_diags);
    }

    void solve(vector<vector<string>> & results, vector<int> pos, int n, int row, bool cols[10], bool down_diagonals[20], bool up_diagonals[20]) {
        if (row == n) {
            vector<string> result;
            for (int r = 0; r < n; r++) {
                string row_str;
                for (int c = 0; c < pos[r]; c++) {
                    row_str.push_back('.');
                }
                row_str.push_back('Q');
                for (int c = pos[r]+1; c < n; c++) {
                    row_str.push_back('.');
                }
                result.push_back(row_str);
            }
            results.push_back(result);
        }
        for (int c = 0; c < n; c++) {
            if (!cols[c] && !up_diagonals[row+c] && !down_diagonals[n-1-row + c]) {
                cols[c] = true;
                up_diagonals[row+c] = true;
                down_diagonals[n-1-row + c] = true;
                pos[row] = c;
                solve(results, pos, n, row+1, cols, down_diagonals, up_diagonals);
                cols[c] = false;
                up_diagonals[row+c] = false;
                down_diagonals[n-1-row + c] = false;
            }
        }

    }


    int count(int n, int row, bool cols[10], bool down_diagonals[20], bool up_diagonals[20]) {
        if (row == n) {
            return 1;
        }
        int total_subtracks = 0;
        for (int c = 0; c < n; c++) {
            if (!cols[c] && !up_diagonals[row+c] && !down_diagonals[n-1-row + c]) {
                cols[c] = true;
                up_diagonals[row+c] = true;
                down_diagonals[n-1-row + c] = true;
                total_subtracks += count(n, row+1, cols, down_diagonals, up_diagonals);
                cols[c] = false;
                up_diagonals[row+c] = false;
                down_diagonals[n-1-row + c] = false;
            }
        }
        return total_subtracks;
    }
};

int main() {
    Solution s;
    int n = 1;
    vector<vector<string>> results = s.solveNQueens(n);
    printf("total %ld output>>\n", results.size());
    printf("--count returns %d\n", s.totalNQueens(n));
    for (int i = 0; i < results.size(); i++) {
        printf("result %d:\n", i);
        for (int j = 0; j < results[i].size(); j++) {
            printf("    %s\n", results[i][j].c_str());
        }
    }
}