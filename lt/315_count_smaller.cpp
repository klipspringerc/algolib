//
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// count no. of element smaller than current element on the right.
// Solution: from right to left, build a ds, at each element, query the no. of values smaller than cur

// could use set lower_bound and std::distance function, but distance could have linear complexity
/*
 *  set<int> s;
    int countSmaller[len];
    for (int i = len - 1; i >= 0; i--) {
        s.insert(A[i]);
        auto it = s.lower_bound(A[i]);
        countSmaller[i] = distance(s.begin(), it);
 */
// if we use our own BST, if no self balancing when worst case is still n^2

// novel approach: use merge sort (descending order), in merging, add count to each element position!
// [___left___][___right___], when an element on left array is being merged to dest array
//  the remaining number on the right side would be added to the count of this element
// because when merging, all elements in right array were originally on the RHS of any element in left array.

#include <vector>
#include <cstdio>
using namespace std;


class Solution {
public:
    void merge_sort(vector<pair<int,int>> & nums, vector<int> &count, vector<pair<int,int>> &tmp, int l, int r) {
        if (l >=r-1)
            return;
        int mid  = ((r-l) >> 1) + l;
        merge_sort(nums, count, tmp, l, mid);
        merge_sort(nums, count, tmp, mid, r);

        int i = l, j = mid;
        int k = l;
        while (i < mid  && j < r) {
            // let equal numbers on right array pass through first
            if (nums[i].first <= nums[j].first) {
                tmp[k++] = nums[j++];
            } else {
                // now this num on left array is larger than all remaining elements in right array
                count[nums[i].second] += r - j;
                tmp[k++] = nums[i++];
            }
        }
        while (i < mid) {
            tmp[k++] = nums[i++];
        }
        while (j < r) {
            tmp[k++] = nums[j++];
        }
        for (int i = l; i < r; i++) {
            nums[i] = tmp[i];
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        vector<int>count(nums.size(), 0);
        vector<pair<int, int>> tmp(nums.size());
        vector<pair<int, int>> num_pairs;
        for (int i = 0; i < nums.size(); i++) {
            num_pairs.push_back(make_pair(nums[i], i));
        }
        merge_sort(num_pairs, count, tmp, 0, nums.size());
        return count;
    }
};


int main() {
    Solution s;
    vector<int> nums = {1,2,3,4,5};
    vector<int> count = s.countSmaller(nums);
    for (auto v : count) {
        printf("%d, ", v);
    }
    printf("\n");
}
