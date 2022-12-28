//
// https://leetcode.com/problems/median-of-two-sorted-arrays/
// 4. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
// Created by KevinCui on 16/10/18.
//

// Solution:
// tries to find the index, where max(prefix array of both) < min(suffix array of both)
// if even, (max + min) / 2
// if odd, min(suffix array)

// l = 0, r = length
// med = l + (r-l) / 2
// if med > target, r = med; if med < target, l = med+1

// 1 3, 5     2, 4 6
// median: (3 + 4) / 2
// 1 3, 5   ,2 4 => 3 > min(2, 5)
// => 1, 3 5   2, 4
// median = min (3, 4) = 3

// 1 ,2    3 ,4 5 => 3 > min(2, 5)
// => 1 2 ,   ,3 4 5  => 2 < min (3)
// median = min(3) = 3

// 4 ,5   1 ,2 3 => max(4, 1) > min(5, 2)
// => ,4 5    1 2 ,3 => max(2) < min(4, 3)
// median = min(4,3 ) = 3

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // always binary search on the smaller array
        // otherwise the ptr2 on the other array may exceed array limit
        if (nums1.size() > nums2.size())
            nums1.swap(nums2);
        int m = nums1.size();
        int n = nums2.size();
        bool even = ((m+n) % 2 == 0);
        if (m == 0) {
            if (even)
                return 0.5L * (nums2[n/2]+nums2[n/2-1]);
            else
                return 1.0L * nums2[n/2];
        }
        int l = 0, r = m;
        int ptr1 = 0, ptr2 = 0;
        while (l < r) {
            int mid = l + ((r-l) >> 1);
            ptr1 = mid; // points to first element of suffix in nums1
            ptr2 = (m+n)/2 - ptr1; // points to first element of suffix in nums2
            // if ptr1-1 larger than max(suffix), binary search move left;
                // if ptr == 0,
            // if prt2-1 larger than max(suffix), binary search move right
            // it can be mathematically deduced that
            // ptr1 > 0 ==> ptr2 < n
            // ptr1 < m ==> ptr2 > 0
            if (ptr1 > 0 && ptr1 < m && nums1[ptr1-1] <= nums2[ptr2] && nums2[ptr2-1] <= nums1[ptr1])
                break;
            else if (ptr1 > 0 && nums1[ptr1-1] > nums2[ptr2]) {
                r = mid;
                continue;
            } else if (ptr1 < m && nums2[ptr2-1] > nums1[ptr1]) {
                l = mid+1;
                continue;
            }
            if (ptr1 == 0 || ptr2 == 0 || ptr1 == m || ptr2 == n)
                break;
        }
        if (l == r) {
            ptr1 = l;
            ptr2 = (m+n)/2 - ptr1;
        }
//        printf("ptr1:%d  ptr2:%d\n", ptr1, ptr2);
        int max_left, min_right;
        if (ptr1 == m)
            min_right = nums2[ptr2];
        else if (ptr2 == n) //    ,4 5 6  1 2 3,
            min_right = nums1[ptr1];
        else
            min_right = min(nums1[ptr1], nums2[ptr2]);
        if (!even)
            return min_right;
        if (ptr1 == 0)
            max_left = nums2[ptr2-1];
        else if (ptr2 == 0)
            max_left = nums1[ptr1-1];
        else
            max_left = max(nums1[ptr1-1], nums2[ptr2-1]);
        return 0.5L * (max_left + min_right);
    }
};

int main() {
    Solution s;
    vector<int> v1 = {1,2,4,5,6,7};
    vector<int> v2 = {-3,-2,-1};
    printf("%lf\n", s.findMedianSortedArrays(v1, v2));
}