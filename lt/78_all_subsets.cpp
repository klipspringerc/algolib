//
// https://leetcode.com/problems/subsets/description/
// Return all subsets (power set) of all sizes, including zero
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> stack;
        solve(0, nums, stack, results);
//        vector<int> empty;
//        results.push_back(empty);
//        for (int i = 1; i <= nums.size(); i++) {
//            recur(0, 0, i, nums, stack, results);
//        }
        return results;
    }

    // need step to record next index, while count record how many number in stack
    void recur(int step, int count, int k, vector<int>& nums, vector<int>& stack, vector<vector<int>>& results) {
        if (count == k) {
            vector<int> result(stack);
            results.push_back(result);
        }
        for (int i = step; i < nums.size(); i++) {
            if (k - count > nums.size() - i) return;
            stack[count] = nums[i];
            recur(i+1, count+1, k, nums, stack, results);
        }
    }

    void solve(int step, vector<int> & nums, vector<int> & stack, vector<vector<int>>& results) {
        results.push_back(stack); // push_back pass by reference, but perform copy internally, so directly append would work.
        for (int i = step; i < nums.size(); i++) {
            stack.push_back(nums[i]);
            solve(i+1, nums, stack, results);
            stack.pop_back();
        }
    }
};

int main() {
    Solution s;
    vector<int> in=  {1,2,3};
    vector<vector<int>> result = s.subsets(in);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            printf(" %d", result[i][j]);
        }
        printf(" | \n");
    }
}