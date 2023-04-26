//
// https://leetcode.com/problems/valid-square/
//

#include <vector>
#include <cstdio>
#include <unordered_map>
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
    bool solution2(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = {p1,p2,p3,p4};
        vector<bool> v(4, false);
        fill(v.begin(), v.begin() +2, true);
        unordered_map<int, int> dist_map;
        do {
            vector<int> s(2);
            int idx = 0;
            for (int i = 0; i < 4; i++) {
                if (v[i])
                    s[idx++] = i;
            }
            vector<int> & pa = points[s[0]];
            vector<int> & pb = points[s[1]];
            int dist = pow(pa[0] - pb[0],2) + pow(pa[1] - pb[1], 2);
            dist_map[dist]++;
        } while (prev_permutation(v.begin(), v.end()));
        if (dist_map.size() != 2)
            return false;
        bool found4 = false, found2 = false;
        int val4, val2;
        for (const pair<int, int> & p : dist_map) {
            printf("dist %d, freq %d\n", p.first, p.second);
            if (p.second == 4) {
                if (found4) {
                    return false;
                }
                found4 = true;
                val4 = p.first;
            }
            if (p.second == 2) {
                if (found2) {
                    return false;
                }
                found2 = true;
                val2 = p.first;
            }
        }
        return found2 && found4 && (val4 * 2 == val2);
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
    vector<int> p2 = {2,0};
    vector<int> p3 = {2,2};
    vector<int> p4 = {0,0};
//    printf("is valid: %s", s.validSquare(p1,p2,p3,p4)? "true" : "false");
    printf("is valid: %s", s.solution2(p1,p2,p3,p4)? "true" : "false");
}