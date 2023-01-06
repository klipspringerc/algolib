//
// https://leetcode.com/problems/spiral-matrix-ii/description/
//

#include <vector>
#include <cstdio>
using  namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix;
        for (int i = 0; i < n; i++) {
            vector<int> row(n);
            matrix.push_back(row);
        }
        int row_length = n;
        int col_length = n;
        int count = 1;
        // pick n to be the smaller edge
        int shorter_length = row_length < col_length? row_length : col_length;
        for (int step = 0; shorter_length-step - step > 0; step++) {
            // special handling for when loop height / width == 1
            if (row_length-step - step == 1) { // this also covers the case when both height and width == 1
                for (int c = step; c < col_length-step; c++) {
                    matrix[step][c] = count++;
                }
                break;
            }
            if (col_length-step - step == 1) {
                for (int r = step; r < row_length-step; r++) {
                    matrix[r][step] = count++;
                }
                break;
            }
            // normal sequence
            // top edge left to right: row = step, col = [step, col_length-step]
            for (int c = step; c < col_length-1 - step; c++) {
                matrix[step][c] = count++;
            }
            // right edge up to down: col = col_length-step, row = [step, row_length-step]
            for (int r = step; r < row_length-1 - step; r++) {
                matrix[r][col_length-1 - step] = count++;
            }
            // bottom edge right to left: row = row_length-step, col = [step, col_length-step]
            for (int c = col_length-1 - step; c > step; c--) {
                matrix[row_length-1 - step][c] = count++;
            }
            // left edge down to up: col = step, row = [step, row_length-step]
            for (int r = row_length-1 - step; r > step ; r--) {
                matrix[r][step] = count++;
            }
        }
        return matrix;
    }
};

int main() {
    Solution s;
    vector<vector<int>> results = s.generateMatrix(4);
    printf("results:");
    for (int i = 0; i < results.size(); i++) {
        printf("\n    ");
        for (int j = 0; j < results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
    }
}