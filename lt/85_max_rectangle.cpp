//
// https://leetcode.com/problems/maximal-rectangle/
// adj_h/v[i][j] stores the closest zero horizontally on right or vertically on the bottom
// the largest rectangle must start at a certain position, for each `1`, find its adj zero at right and bottom, then traverse each row to determine max possible width.
// when iterating, stop early when potential width * height is smaller than current max
//

#include <vector>
#include <cstdio>
using namespace std;


class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int max_area = 0;
        int n = matrix.size();
        if (n == 0)
            return 0;
        int m = matrix[0].size();
        if (m == 0)
            return 0;
        vector<vector<int>> adj_h = vector<vector<int>>(n, vector<int>(m)); // horizontally
        vector<vector<int>> adj_v = vector<vector<int>>(n, vector<int>(m)); // vertically
        // for each 1, record horizontally adjacent 0 position on the right
        for (int i = 0; i < n; i++) {
            int adj_zero_pos = m;
            for (int j = m-1; j >-1; j--) {
                if (matrix[i][j] == '0')
                    adj_zero_pos = j;
                else
                    adj_h[i][j] = adj_zero_pos;
            }
        }
        for (int j = 0; j < m; j++) {
            int adj_zero_pos = n; // vertically adjacent zero position from bottom
            for (int i = n-1; i > -1; i--) {
                if (matrix[i][j] == '0')
                    adj_zero_pos = i;
                else
                    adj_v[i][j] = adj_zero_pos;
            }
        }
        // then iterate all possible position of top left corner of max rectangle.
        // skip those 1s with no room for larger rectangle
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '0')
                    continue;
                int potential_width = adj_h[i][j] - j;
                int potential_height = adj_v[i][j] - i;
                if (potential_height * potential_width < max_area)
                    continue;
                // if could potentially be larger than current max, iterate vertically to find actual possible width
                for (int k = i; k < adj_v[i][j]; k++) {
                    // at each step, we increase current rectangle height by one, max possible width is min(all horizontal room from row i to row k)
                    int cur_width = adj_h[k][j] - j;
                    int cur_h = k-i + 1;
                    // all following rectangle width could not be larger than current row width
                    if (cur_width < potential_width)
                        potential_width = cur_width;
                    // rectangle have top-left corner at (i,j) and bottom-right corner at (k, potential_width)
                    int cur_area = potential_width * cur_h;
                    if (cur_area > max_area)
                        max_area = cur_area;
                    // if maximum possible area already smaller than max, no need to continue
                    if (potential_width * potential_height < max_area)
                        break;
                }
            }
        }
        return max_area;
    }
};

int main() {
    Solution s;
    vector<vector<char>> in = {
            {'0', '1', '0'},
            {'0', '1', '1'},
            {'0', '1', '1'},
            {'0', '0', '1'},
            {'0', '0', '1'},
            {'0', '0', '1'},
    };
    int r = s.maximalRectangle(in);
    printf("max rectangle area: %d\n", r);
}