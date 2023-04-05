//
// https://leetcode.com/problems/search-a-2d-matrix/description/
// Solution: 2-step binary search,
//   first step: search for <=
//   second step: search for ==


#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int l = 0;
        int r = matrix.size();
        while (r-l > 1) {
            int mid = l + ((r-l) >> 1);
            if (matrix[mid][0] > target) {
                r = mid - 1;
            } else if (matrix[mid][0] == target) {
                return true;
            } else {
                l = mid;
            }
        }
        int row;
        if (r < matrix.size() && matrix[r][0] < target) {
            row = r;
        } else {
            row = l;
        }
        l = 0;
        r = matrix[row].size();
        while (l < r) {
            int mid = l + ((r-l) >> 1);
            if (matrix[row][mid] > target) {
                r = mid - 1;
            } else if (matrix[row][mid] == target) {
                return true;
            } else {
                l = mid+1;
            }
        }
        if (l >= matrix[row].size()) return false;
        return matrix[row][l] == target;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
            {1},
//            {0,2,3},
//            {4,5,6},
//            {7,8,9},
    };
    printf("search: %s\n", s.searchMatrix(grid, 2)? "found": "miss");
}
