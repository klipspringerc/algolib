//
// https://leetcode.com/problems/jump-game/
// Solution: maintain current maximum distance maxd
//     stop when reach end, or index with zero is encountered while maxd == cur
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxd = 0;
        if (nums.size() == 1) {
            return true;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0 && maxd <= i) {
                return false;
            }
            if (nums[i] + i > maxd) {
                maxd = nums[i] + i;
                if (maxd >= nums.size()-1) {
                    return true;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;
//    vector<int> in = {4,0,1,0,2,0,3,0,0};
    vector<int> in = {0};
    printf("output: %s\n", s.canJump(in)? "true":"false");
}