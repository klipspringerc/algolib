//
// https://leetcode.com/problems/longest-increasing-subsequence/
// Return length of longest strictly increasing subsequence
// greedy insertion on a hot subsequence vector, as in CP3 book DP section

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector <int> hot;
        for (auto n : nums) {
//            for (auto v : hot)
//                cout << v << " ";
//            cout <<endl;
            if (hot.size() == 0) {
                hot.push_back(n);
                continue;
            }
            auto itr = lower_bound(hot.begin(), hot.end(), n);
            cout << "found lowerbound idx " << itr-hot.begin() << endl;
            size_t idx =  itr-hot.begin();
            if (idx == hot.size())
                hot.push_back(n);
            else
                hot[idx] = n;
        }
        return hot.size();
    }
};

int main() {
    Solution s;
    vector<int> in = {1,4,2,3,9,7,-2,5,6};
    cout << s.lengthOfLIS(in) << endl;

}
