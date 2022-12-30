//
// https://leetcode.com/problems/permutations/
//  Solution: backtrack, at each position, swap with all values after that position
// 1 2 3 4
// 1 2 4 3
// 1 3 2 4
// 1 3 4 2
// 1 4 2 3
// 1 4 3 2
// https://leetcode.com/problems/permutations-ii/
//  permutation II forbids duplicate results when input numbers contain duplicates
//  Solution: use hashmap to record unique swap values at each position
//  As long as values at each position is unique, the whole results would be unique
//  1 1 2 2
//  1 2 1 2
//  1 2 2 1
//  2 1 1 2
//  2 1 2 1
//  2 2 1 1

#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> results;
        perm_recur(nums, results, 0, false);
        return results;
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> results;
//        sort(nums.begin(), nums.end());
        perm_recur(nums, results, 0, true);
        return results;
    }



    void perm_recur(vector<int>& nums, vector<vector<int>> & results, int step, bool check_duplicate) {
        if (step == nums.size()-1) {
            vector<int> result(nums);
            results.push_back(result);
            return;
        }
        unordered_map<int, int> swap_values; // check duplicate swap values at each position, same swap value produce duplicate permutations
        // note that i start from step, so the first swap is always self-swap, which covers all results with the same prefix as input
        for (int i = step; i < nums.size(); i++) {
            if (check_duplicate) {
                if (swap_values.count(nums[i]) > 0) {
                    continue;
                }
            }
            swap_values[nums[i]]++;
            int tmp = nums[step]; // tmp stores original value at index step
            nums[step] = nums[i];
            nums[i] = tmp;
            perm_recur(nums, results, step+1, check_duplicate);
            nums[i] = nums[step];
            nums[step] = tmp;
        }
    }
};

int main() {
    Solution s;
    vector<int> input = {1,1,2,2};
    vector<vector<int>> results = s.permuteUnique(input);
    printf("results: ");
    for (int i = 0; i < results.size(); i++) {
        printf("\n  ");
        for (int j = 0; j < results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
    }
}