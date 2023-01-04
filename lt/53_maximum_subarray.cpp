//
// Created by SG0014000445M on 2023/1/4.
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max = INT_MIN;
        int cur = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (cur < 0) {
                cur = 0;
            }
            cur += nums[i];
            if (cur > max) {
                max = cur;
            }
        }
        return max;
    }
};

int main() {
    Solution s;
    vector<int> in = {-4};
    printf("output: %d\n", s.maxSubArray(in));
}