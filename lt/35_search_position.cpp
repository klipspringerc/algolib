//
// https://leetcode.com/problems/search-insert-position/
// Created by KSC on 25/9/22.
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, j = nums.size();
        while (l < j) {
            int d = (l + j) / 2;
            if (nums[d] < target) {
                l = d + 1;
            } else if (nums[d] > target) {
                j = d;
            } else {
                return d;
            }
        }
        return l;
    }
};

int main() {
    Solution s;
    vector<int> input = vector<int>{1,2,4,5,6,7};
    printf("found at: %d", s.searchInsert(input, -1));
}