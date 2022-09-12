//
// https://leetcode.com/problems/reaching-points/
// Created by Shengping Cui on 2022/9/11.
//

#import <cstdio>
#include <cstdlib>
using namespace std;

// since only operation are x+y,y and x,x+y, so thinking backwards from tx ty, the last operation has to be
// the smaller one added to get the larger one. If tx > ty, then last operation must be (x+y, y).
// So we go back by subtract from the larger one.
// Can subtract multiple one for shortcut.
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx > 0 && ty > 0) {
            if (tx == sx && ty == sy) {
                return true;
            }
            if (tx > ty) {
                if (tx - ty < sx) {
                    return false;
                }
                tx -= ((tx - sx) / ty) * ty;
            } else if (tx < ty) {
                if (ty - tx < sy) {
                    return false;
                }
                ty -= ((ty - sy) / tx)  * tx;

            } else {
                return false; // x, y cannot be zero, so false
            }
        }
        return false;
    }
};


int main() {
    Solution s;
    printf("result is %d\n", s.reachingPoints(1,3,1,3));
}