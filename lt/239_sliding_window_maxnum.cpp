//
// https://leetcode.com/problems/sliding-window-maximum/
// Return the maximum number of a sliding window

#include <set>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <vector>
using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindowPQ(vector<int>& nums, int k) {
        int n = nums.size();
        multiset<int, greater<int>> window ;
        vector<int> results;
        int l = 0;
        int r = l+k;
        for (int i = l; i <r; i++)
            window.insert(nums[i]);
        results.push_back(*(window.begin()));
        while (r < n) {
            window.erase(window.find(nums[l]));
            window.insert(nums[r]);
            results.push_back(*window.begin());
            l++; r++;
        }
        return results;

    }

    // alternative Deque solution
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q ; // put the index of elements in window
        vector<int> results;
        int l = 0;
        int r = l+k;
        q.push_back(0);
        // we keep the current largest index at front of the queue, only when l > front queue index we pop the largest value
        // each time insert a new value v, pop all values from the back that are smaller than v, they are of no use : value smaller than v, index smaller than v, so all windows containing v would not need these values
        // when the new value is larger than current largest value at the front, we add this value to the front, all values after it could be removed
        // so the queue looks like this:
        // {largest_value_idx, idx_smaller_than_largest_but_with_larger_index, ... }
        for (int i = 1; i <r; i++) {
            int newv = nums[i];
            // keep the index of largest value at the front
            if (nums[q.front()] < newv) {
                q.push_front(i);
                while (nums[q.back()] < newv)
                    q.pop_back();
            } else {
                while (nums[q.back()] < newv)
                    q.pop_back();
                q.push_back(i);
            }
        }
        results.push_back(nums[q.front()]);
        while (r < n) {
            if (l >= q.front()) {
                q.pop_front();
            }
            int newv = nums[r];
            if (q.empty()) {
                q.push_back(r);

            } else {
                // keep the index of largest value at the front
                if (nums[q.front()] < newv) {
                    q.push_front(r);
                    while (nums[q.back()] < newv)
                        q.pop_back();
                } else {
                    while (nums[q.back()] < newv)
                        q.pop_back();
                    q.push_back(r);
                }
            }
            results.push_back(nums[q.front()]);
            l++; r++;
        }
        return results;

    }
};


int main() {
    Solution s;
    vector<int> input = {1,-1};
    vector<int> result = s.maxSlidingWindow(input, 2);
    for (int num : result)
        printf("%d, ",num);
    printf("\n");
}