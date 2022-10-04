//
// Created by KSC on 4/10/22.
//

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        for (int idx = 0; idx < nums.size()-1; ) {
            int cur = nums[idx];
            if (cur > 0) {
                break;
            }
            int i = idx+1; // with this line, checking on line 15 need to be stricter to size - 1
            int j = nums.size()-1;
            while (i < j) {
                int sum = cur + nums[i] + nums[j];
                int ptr;
                bool skip_l = false, skip_r = false;
                if (sum > 0) {
                    skip_l = true;
                } else if (sum < 0) {
                    skip_r = true;
                } else {
                    vector<int> r = {cur, nums[i], nums[j]};
                    results.push_back(r);
                }
                if (!skip_l) {
                    ptr = nums[i];
                    // index range check must come before value check
                    while (i < nums.size() && nums[i] == ptr) {
                        i++;
                    }
                }
                if (!skip_r) {
                    ptr = nums[j];
                    while (j > idx && nums[j] == ptr) {
                        j--;
                    }
                }
            }
            while (idx < nums.size() && nums[idx] == cur) {
                idx++;
            }
        }
        return results;
    }
};

int main() {
    Solution s;
//    vector<int> input = {-2,-1,-1,0,0,0,0,0,1,2};
//    vector<int> input = {-1,0,1,2,-1,-4};
//    vector<int> input = {0,1,1};
    vector<int> input = {0,0,0,0};
    vector<vector<int>> results = s.threeSum(input);
    for (int i = 0; i < results.size(); i++) {
        for (int j = 0; j < results[i].size(); j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", results[i][j]);
        }
        printf("\n");
    }
}