//
// https://leetcode.com/problems/set-matrix-zeroes/description/
// Requires in-place modification:
// has to be mark-delete, because if erase on the go,
// we wouldn't know which of the zeros are original and which are results of our modification
// Solution: store the row & column erase decision in the first encountered zero's row & column
// - because this row & column would be erased anyway, so the content does not matter
// - 0 marks erase, others mark preserve
//     matrix[recordR][x] stores column state
//     matrix[x][recordC] stores row state
// - preserve original zeros in record row & column
// Steps:
// - In the first run, we store erase decisions in the first encountered zero row & column
// - In the second run, we erase according to the stored state
// - Erase the record row & column last.
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int recordR = -1, recordC = -1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    if (recordR == -1) {
                        // init first encounter row & column as state storage.
                        // 0 marks erase, others mark preserve
                        // matrix[recordR][x] stores column state
                        // matrix[x][recordC] stores row state
                        recordR = i;
                        recordC = j;
                    } else {
                        matrix[recordR][j] = 0; // mark delete column
                        matrix[i][recordC] = 0; // mark delete row
                    }
                }
            }
        }
        if (recordR == -1) {
            // no zero encountered
            return;
        }
        for (int i = 0; i < m; i++) {
            if (i == recordR)
                continue;
            for (int j = 0; j < n; j++) {
                if (j == recordC) continue;
                if (matrix[recordR][j] == 0 || matrix[i][recordC] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int k = 0; k < n; k++) {
            matrix[recordR][k] = 0;
        }
        for (int k = 0; k < m; k++) {
            matrix[k][recordC] = 0;
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
            {0,2,3},
            {4,1,6},
            {5,2,0},
            {1,2,3}
//            {1},
//            {0}
    };
    s.setZeroes(grid);
    printf("results:");
    for (int i = 0; i < grid.size(); i++) {
        printf("\n    ");
        for (int j = 0; j < grid[i].size(); j++) {
            printf("%d ", grid[i][j]);
        }
    }
}