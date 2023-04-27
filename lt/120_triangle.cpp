//
// https://leetcode.com/problems/triangle/
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> s (n);
        for (int i = 0; i < n; i++) {
            s[i] = triangle[n-1][i];
        }
        for (int i = n-2; i  > -1; i--) {
            for (int j = 0; j < i+1; j++) {
                int val = triangle[i][j];
                int sum = min(s[j], s[j+1]);
                sum += val;
                s[j] = sum;
            }
        }
        return s[0];
    }
};

int main() {
    Solution s;
    vector<vector<int>> in = {
            {-10},
//            {2},
//            {3,4},
//            {6,5,7},
//            {4,1,8,3},
    };
    printf("result: %d\n" , s.minimumTotal(in));
}