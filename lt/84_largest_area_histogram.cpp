//
//https://leetcode.com/problems/largest-rectangle-in-histogram/
// TLE Solution1: DP matrix storing max possible height from i-th to j-th position.
//  Max pool on DB matrix.
// TLE Solution2: carries active height rectangles and remove active heights that are lower than current height.
// Solution:
// because the largest rectangle would be marked to the height of at least one block.
// for each block, we find the next shorter block on the left and on the right.
// then max area is between (rhs - lhs) * current_height
// because one shorter block would block all higher block in between, so we can
// efficiently calculate LHS next shorter blocks for all blocks in one pass! same for RHS
// if height is 2 5 5 4 3
// when at 3, 5 5 4 all do not matter because only the rectangle with height 3 could go through 3
// so an efficient data structure would omit height blocks then a shorter block is in the way
// therefore stack is used
// stack record all candidate next shorter positions,
// at each block, stack would pop all position with larger heights.


#include <vector>
#include <cstdio>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> lhs, rhs;
        stack<int> s;
        // find the first block on LHS that is lower than current height
        // the largest rectangle of current height would have left edge of the first lower block.
        for (int i = 0; i < n; i++) {
            int cur = heights[i];
            if (s.size() == 0) {
                lhs.emplace_back(-1);
            } else {
                if (heights[s.top()] < cur) {
                    lhs.emplace_back(s.top());
                } else if (heights[s.top()] >= cur) {
                    // remove all taller block because for all other blocks on the right,
                    // the current block would be the highest they can get on LHS.
                    while (s.size() > 0 && heights[s.top()] >= cur) s.pop();
                    if (s.size() == 0)
                        lhs.emplace_back(-1);
                    else
                        lhs.emplace_back(s.top());
                }
            }
            s.push(i);
        }

        while (!s.empty())
            s.pop();

        for (int i = n-1; i > -1; i--) {
            int cur = heights[i];
            if (s.size() == 0)
                rhs.emplace_back(n);
            else {
                if (heights[s.top()] < cur) {
                    rhs.emplace_back(s.top());
                } else if (heights[s.top()] >= cur) {
                    // remove all taller block because for all other blocks on the left,
                    // the current block would be the highest they can get on RHS.
                    while (s.size() > 0 && heights[s.top()] >= cur) s.pop();
                    if (s.size() == 0)
                        rhs.emplace_back(n);
                    else
                        rhs.emplace_back(s.top());
                }
            }
            s.push(i);
        }
        reverse(rhs.begin(), rhs.end());
//        for (int v : lhs)
//            printf("%d ", v);
//        printf("\n");
//        for (int v : rhs)
//            printf("%d ", v);
        printf("\n");
        int max_area = -1;
        for (int i = 0; i < n; i++) {
            int h = heights[i];
            int cur_area = h * (rhs[i] - lhs[i] -1);
            if (cur_area > max_area)
                max_area = cur_area;
        }
        return max_area;
    }

    int largestRectangleAreaTLE(vector<int>& heights) {
        int n = heights.size();
        vector<vector<int>> dp(n, vector<int> (n,0));
        // dp[i][j] stores max possible height from i to j;
        int max_area = -1;
        for (int i = 0; i < n; i++) {
            dp[i][i] = heights[i];
            if (heights[i] > max_area ) {
                max_area = heights[i];
            }
        }
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < j; i++) {
                int max_h = dp[i][j-1] < heights[j]? dp[i][j-1] : heights[j];
                dp[i][j] = max_h;
                int cur_area = max_h * (j-i+1);
                if (cur_area > max_area)
                    max_area = cur_area;
            }
        }
        return max_area;
    }
    int largestRectangleAreaTLE2(vector<int>& heights) {
        unordered_map<int, int> active; // map still lasting height h -> starting_position pos, for a position to remain in map, all following hist should have height >= h
        int n = heights.size();
        int max_area = -1;
        for (int i = 0; i < n; i++) {
            int cur = heights[i];
            vector<int> to_remove;
            int min_pos_to_cur = i;
            for (const pair<int, int> &p : active) {
                int h = p.first;
                int pos = p.second;
                if (cur < h) {
                    to_remove.push_back(h);
                    // the min position where area of cur height could start from
                    if (pos < min_pos_to_cur)
                        min_pos_to_cur = pos;
                    // calculate to_delete height's max area
                    int cur_area = h * (i - pos);
                    if (cur_area > max_area)
                        max_area = cur_area;
                }
            }
            for (int v : to_remove) {
                active.erase(v);
            }
            if (active.count(cur) == 0) {
                active.insert({cur, min_pos_to_cur});
                int cur_area = cur * (i - min_pos_to_cur+1);
                if (max_area < cur_area) {
                    max_area = cur_area;
                }
            }
        }
        for (const pair<int, int> &p : active) {
            int h = p.first;
            int pos = p.second;
            // calculate to_delete height's max area
            int cur_area = h * (n - pos);
            if (cur_area > max_area)
                max_area = cur_area;
        }
        return max_area;
    }
};

int main() {
    vector<int> hist = {2,3};
    Solution s;
    int r = s.largestRectangleArea(hist);
    printf("largest area: %d\n", r);

}



