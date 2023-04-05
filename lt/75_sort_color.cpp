//
// https://leetcode.com/problems/sort-colors/description/
// Sort 0,1,2 in place in given array
// use 1 to partition 0 and 2?
// l points to leftmost 1, or rightmost 0 if there is no 1
// r points to leftmost 2
// i points to current position
// 000111222
//    l  r

#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = -1 ,r = -1, i = 0;
        for (;i < nums.size(); i++) {
            // if new number is 2, just advance i
            if (nums[i] == 2) {
                if (r == -1) r = i; // init r at first encounter
                continue;
            }
            bool isOne = nums[i] == 1;
            bool newOne = false;
            if (isOne && (l == -1 || nums[l] == 0)) {
                newOne = true;
            }
            int next_swap = i;
            // if encountered 2 before, swap current with leftmost 2
            if (r > -1) {
                int tmp = nums[i];
                nums[i] = nums[r];
                nums[r] = tmp;
                next_swap = r; // prepare for next swap if new value is 0 (need another swap with 1)
                r++;
                // if new 1, init l ptr to left of r;
                if (newOne)
                    l = r-1;
            } else {
                // not encounter 2 yet, and first encounter 1, just record l and advance i
                if (newOne) {
                    l = i;
                }
            }
            // swapped new value is 1, not need to continue checking for 0
            if (isOne)
                continue;

            if (nums[next_swap] == 0) {
                if (l == -1) {
                    l = next_swap; // init l to rightmost zero when not encountered any 1 or 0 before
                } else {
                    // if encountered zero or 1 before, swap when nums[l] is not zero
                    if (nums[l] == 1) {
                        int tmp = nums[next_swap];
                        nums[next_swap] = nums[l];
                        nums[l] = tmp;
                    }
                    // then advance l
                    l++;
                }
            }
            printf("==> position %d, current layout: ", i);
            for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
                printf("%d ", *it);
            }
            printf("\n");
        }
    }

    void threeWayPartition(vector<int>& nums) {
        int high = nums.size()-1, low=0, index = 0;
        while (index < high) {
            if (nums[index] == 0 ) {
                nums[index] = nums[low];
                nums[low] = 0;
                low++;
                index++; // increment index here, because whatever coming from low are smaller than 2
            } else if (nums[index] == 2) {
                nums[index] = nums[high];
                nums[high] = 2;
                high--;
                // when moving from high, do not increment index. as it may need to be moved to low.
            } else {
                index++;
            }
        }
    }
};

int main() {
    Solution s;
//    vector<int> in = {2,0,0,1,2,0};
//    vector<int> in = {0,1,0,1,0,1,0,0,1};
//    vector<int> in = {2,1,2,1,2,1,2,2,1};
//    vector<int> in = {2,1,0,2,1,0,2,1,0,2,2,1,0};
    vector<int> in = {2,2,1,1,1,1,0,0};
//    vector<int> in = {2,0};
//    s.sortColors(in);
    s.threeWayPartition(in);
    for (vector<int>::iterator it = in.begin(); it != in.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
}
