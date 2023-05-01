//
// https://leetcode.com/problems/maximal-square/description/
//
// pre-compute distance to nearest 0 on the right and bottom
// iterate over all 1s in the matrix with early stop based on pre-computed distances

#include <vector>
#include <cstdio>
using namespace std;


class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dpr (m, vector<int>(n, 0));
        vector<vector<int>> dpb (m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            int rb = n;  // nearest 0 index on the right
            for (int j = n-1; j >=0; j--) {
                if (matrix[i][j] == '1')
                    dpr[i][j] = rb;
                else
                    rb = j; // update nearest zero position
            }
        }
        for (int j = 0; j < n; j++) {
            int bb = m;  // nearest 0 index on the bottom
            for (int i = m-1; i >=0; i--) {
                if (matrix[i][j] == '1')
                    dpb[i][j] = bb;
                else
                    bb = i; // update nearest zero position
            }
        }
        int max_a = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != '1')
                    continue;
                int width = dpr[i][j] - j;
                int height = dpb[i][j] - i;
                int edge = min(width, height);
                if (edge * edge < max_a)
                    continue;
                for (int k = 0; k < height; k++) {
                    width = min(width, dpr[i+k][j] - j);
                    if (k + 1 > width)
                        break;
                    int cur_a = (k+1) * (k+1);
                    if (cur_a > max_a)
                        max_a = cur_a;
                    edge = min(width, height);
                    if (edge * edge < max_a)
                        break;
                }
            }
        }
        return max_a;
    }
};

int main() {
    Solution s;
    vector<vector<char>> input  = {
//            {'1'},
//            {'1', '0'},
//            {'0', '1'},
            {'1', '1', '0', '1'},
            {'0', '1', '1', '1'},
            {'0', '1', '1', '1'},
    };
    printf("max area: %d\n", s.maximalSquare(input));

}