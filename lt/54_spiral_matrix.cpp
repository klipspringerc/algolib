//
// https://leetcode.com/problems/spiral-matrix/
// Solution:
// iterate over each loop
// for each loop, go through 4 edges
// normal case
// AAAB
// D  B
// D  B
// DCCC
// special cases:
// loop height 1
// special handling
// AAA

// loop width 1
// special handling
// B
// B
// B

// loop height 2
// AAAB
// DCCC

// loop width 2
// AB
// DB
// DC

// loop 2*2
// AB
// DC


#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> results;
        int row_length = matrix.size();
        int col_length = matrix[0].size();
        // pick n to be the smaller edge
        int shorter_length = row_length < col_length? row_length : col_length;
        for (int step = 0; shorter_length-step - step > 0; step++) {
            // special handling for when loop height / width == 1
            if (row_length-step - step == 1) { // this also covers the case when both height and width == 1
                for (int c = step; c < col_length-step; c++) {
                    results.push_back(matrix[step][c]);
                }
                break;
            }
            if (col_length-step - step == 1) {
                for (int r = step; r < row_length-step; r++) {
                    results.push_back(matrix[r][step]);
                }
                break;
            }
            // normal sequence
            // top edge left to right: row = step, col = [step, col_length-step]
            for (int c = step; c < col_length-1 - step; c++) {
                results.push_back(matrix[step][c]);
            }
            // right edge up to down: col = col_length-step, row = [step, row_length-step]
            for (int r = step; r < row_length-1 - step; r++) {
                results.push_back(matrix[r][col_length-1 - step]);
            }
            // bottom edge right to left: row = row_length-step, col = [step, col_length-step]
            for (int c = col_length-1 - step; c > step; c--) {
                results.push_back(matrix[row_length-1 - step][c]);
            }
            // left edge down to up: col = step, row = [step, row_length-step]
            for (int r = row_length-1 - step; r > step ; r--) {
                results.push_back(matrix[r][step]);
            }
        }
        return results;
    }
};

int main() {
    Solution s;
//    vector<vector<int>> in = {{1,2,3}, {4, 5, 6}, {7, 8, 9}};
//    vector<vector<int>> in = {{1,2,3}, {4, 5, 6}, {7, 8, 9}, {10,11,12}};
//    vector<vector<int>> in = {{1,2,3}};
//    vector<vector<int>> in = {{1}};
        vector<vector<int>> in = {{1,2}};
//    vector<vector<int>> in = {{1,2,3,4}, {5, 6, 7, 8}, {9,10,11,12}};
    vector<int> results = s.spiralOrder(in);
    for (vector<int>::iterator it = results.begin(); it < results.end(); it++) {
        printf("%d ", *it);
    }
}