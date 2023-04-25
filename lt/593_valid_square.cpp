//
// https://leetcode.com/problems/valid-square/
//

#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

typedef vector<int> vi;

class Solution {
public:
    bool validSquare(vector<int>& pa, vector<int>& pb, vector<int>& pc, vector<int>& pd) {
        vector<vector<int>> points = {pa, pb, pc, pd};
        sort(points.begin(), points.end(), compare2d); // default comparator would behave the same
        for (int i = 0; i < 4; i++) {
            printf("{%d, %d} ", points[i][0], points[i][1]);
        }
        printf("\n");
        vector<int> p1 = points[0];
        vector<int> p2 = points[1];
        vector<int> p3 = points[2];
        vector<int> p4 = points[3];
        // parallelogram check, the x, y distance should be the same between point 1,3 ; 2,4 and 1,2 ; 3,4.
        if (p2[0] - p1[0] != p4[0] - p3[0] || p2[1] - p1[1] != p4[1] - p3[1])
            return false;
        if (p3[0] - p1[0] != p4[0] - p2[0] || p3[1] - p1[1] != p4[1] - p2[1])
            return false;
        // rectangle check
        // if vertical edge, then the other edge must be horizontal
        if (p2[0] - p1[0] == 0 && (p1[1] != p3[1]))
            return false;
        // definitely not rectangle
        if (p1[1] - p2[1] == 0 || p3[0] - p1[0] == 0)
            return false;
        // 90 degree => two rectangle must be similar
        float ratio1 = float(p2[0] - p1[0]) / float(p1[1] - p2[1]);
        float ratio2 = float(p3[1] - p1[1]) / float(p3[0] - p1[0]);
        if (abs(ratio1 - ratio2) > 0.001)
            return false;
        // square check
        if (p2[0] - p1[0] != abs(p3[1] - p1[1]) || p3[0] - p1[0] != abs(p1[1] - p2[1]))
            return false;
        return true;
    }
private:
    static bool compare2d(vector<int> p1, vector<int> p2) {
        if (p1[0]<p2[0])
            return true;
        else if (p1[0] == p2[0]) {
            return (p1[1] < p2[1]);
        } else {
            return false;
        }
    }
};

int main() {
    Solution s;
    vector<int> p1 = {0,2};
    vector<int> p2 = {3,0};
    vector<int> p3 = {3,2};
    vector<int> p4 = {0,0};
    printf("is valid: %s", s.validSquare(p1,p2,p3,p4)? "true" : "false");
}