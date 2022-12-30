//
// https://leetcode.com/problems/rotate-image/
//

#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int N = matrix.size();
        // only need to traverse first N/2 rows, center value would remain the same in rotation
        for (int y = 0; y < N/2; y++) {
            // for each row, only traverse small square of N-2y
            for (int x = y; x < N-1-y; x++) {
               // now we perform 4 rotations
               int tmp = matrix[y][x];
               matrix[y][x] = matrix[N-1-x][y];  // assign bottom-left to top-left, bottom-left x' is controlled by y, while y' is controlled by x
               matrix[N-1-x][y] = matrix[N-1-y][N-1-x]; // assign opposite to bottom-left, opposite x' controlled by x, y' controlled by y
               matrix[N-1-y][N-1-x] = matrix[x][N-1-y]; // assign top right to opposite
               matrix[x][N-1-y] = tmp;
            }
        }
    }
};

int main() {
    Solution s;
//    vector<vector<int>> matrix = {
//            {1,2,3},
//            {4,5,6},
//            {7,8,9}
//    };
    vector<vector<int>> matrix = {
            {5,1,9,11},
            {2,4,8,10},
            {13,3,6,7},
            {15,14,12,16}
    };
    s.rotate(matrix);
    printf("result:");
    for (int i = 0; i < matrix.size(); i++) {
        printf("\n  ");
        for (int j = 0; j < matrix[i].size(); j++) {
            printf("%d ", matrix[i][j]);
        }
    }
}