//
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/
// return the shortest subarray with at least sum k
// sliding window? simple sliding window would not handle cases of negative values well, as it cannot distinguish if a segment including negative numbers is needed
// divide and conquer? would work
// queue?

#include <vector>
#include <cstdio>
#include <climits>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        return shortestRecur(nums, 0, nums.size(), k);
    }

    int shortestRecur(vector<int> & nums, int l, int r, int k) {
        if (r-l ==1) {
            if (nums[l] <k)
                return -1;
            else
                return 1;
        }

        int mid = ((r-l) >> 1) + l;
        int ls = shortestRecur(nums, l, mid, k);
        int rs = shortestRecur(nums, mid, r, k);
        int cur_min = INT_MAX;
        if (ls > -1) {
            if (ls == 1)
                return 1;
            cur_min = min(cur_min, ls);
        }
        if (rs > -1) {
            if (rs == 1)
                return 1;
            cur_min = min(cur_min, rs);
        }
        int lp = mid-1, rp = mid, cur_sum = nums[lp] + nums[rp];
        while (cur_sum < k && rp - lp +1 < cur_min) {
            if (lp <= l && rp >=r-1)
                break;
            if (rp >=r-1 || lp > l && nums[lp-1] > nums[rp+1]) {
                lp--;
                cur_sum += nums[lp];
            } else if(lp <= l || rp <r-1  &&nums[rp+1] > nums[lp-1]) {
                rp++;
                cur_sum += nums[rp];
            }
        }
        if (cur_sum >=k)
            cur_min = min(cur_min, rp-lp+1);
        if (cur_min == INT_MAX)
            return -1;
        return cur_min;
    }
};

int main() {
    Solution s;
    vector<int> in  = {-37,0,-1};
    printf("result %d\n", s.shortestSubarray(in, -1));

}
