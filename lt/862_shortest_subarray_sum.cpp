//
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/
// return the shortest subarray with at least sum k
// sliding window? simple sliding window would not handle cases of negative values well, as it cannot distinguish if a segment including negative numbers is needed
// divide and conquer? seems to work, but when expanding from the middle, how to determine grow left or grow right first?

// Queue? actually work!  Need to locate positive value positions, use a queue to remember all index where prefix sum is increasing : note as `d`.
// - because the min subarray must start at a positive value
// at each position, update the current prefix sum, minus the last increasing position to get the current segment sum
// If segment sum smaller than k, look for one previous location `d`.
// If larger tha k, pop `d` from the queue because this position is of no use. All prefix after current prefix minus `d` would be of longer subarray length.

// Key insights:
// 1. If already found a subarray >= k starting from i, then no need to keep comparing subarray starting from [0 ... i],
//  since they would definitely have larger length
// 2. If current prefix sum at i is smaller than prefix sum of index smaller than i, no need to keep those index before i
//  since subarray starting at i would have larger sum with shorter length

#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> ps(n+1); ps[0] = 0; // ps[i] represents prefix sum until num[i-1]
        deque<int> dq;
        int min_len = INT_MAX;
        // at each iteration, calculate prefix sum
        for (int i = 0; i < n; i++) {
            ps[i+1] = ps[i] + nums[i];
            if (ps[i+1] >=k)
                min_len = min(min_len, i+1 - 0);
            // remove all previous larger sums
            // e.g. [9, -100, 2,3,10], this would help remove prefix 9 and [9,-100]
            while (!dq.empty() && ps[i] < ps[dq.back()]) {
                // if current prefix is smaller with larger idx,
                // then when compared with subarray starting at dq.back(), subarray starting from i would be larger with shorter subarray length
                // so no need to keep dq.back() index
                dq.pop_back();
            }
            dq.push_back(i);
            while (!dq.empty() && ps[i+1] - ps[dq.front()] >= k) {
                if (i+1 - dq.front() < min_len)
                    min_len  = i+1 - dq.front();
                dq.pop_front();
            }
        }
        if (min_len==INT_MAX)
            return -1;
        return min_len;
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
    vector<int> in  = {4,-3,0,4};
    printf("result %d\n", s.shortestSubarray(in, 5));

}
