//
// https://leetcode.com/problems/maximum-sum-circular-subarray/
// Solution: find the max sum subarray and the min sum subarray
// the max sum subarray around the circular array is just total sum - min_sum_subarray

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int cur_sum = 0;
        int cur_min = 0;
        size_t n = nums.size();
        int max_sum = nums[0];
        int min_sum = nums[0];
        int total = 0;

        for (int i = 0 ; i < n; i++) {
            total += nums[i];
            cur_sum += nums[i];
            if (cur_sum > max_sum) {
                max_sum = cur_sum;
            }
            if (cur_sum < 0) {
                cur_sum = 0;
            }
            cur_min += nums[i];
            if (cur_min < min_sum)
                min_sum = cur_min;
            if (cur_min > 0) {
                cur_min = 0;
            }
        }
        if (min_sum == total)
            return max_sum
        return max(max_sum, total-min_sum);
    }
};

int main() {
    vector<int> in = {-4,-2,3,2,-1};
    Solution s;
    printf("%d\n", s.maxSubarraySumCircular(in));
}