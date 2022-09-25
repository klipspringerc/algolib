//
// https://leetcode.com/problems/combination-sum-ii/
// Created by KSC on 25/9/22.
//

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        bool *in = (bool *)malloc(sizeof(bool) * candidates.size());
        for (int i = 0; i < candidates.size(); i++) {
            in[i] = false;
        }
        vector<vector<int>> results;
        sort(candidates.begin(), candidates.end()); // necessary to filter duplicates
        search(candidates, target, 0, 0, in, results);
        return results;
    }

    // simple backtrack
    void search(vector<int>& c, int target, int sum, int pos, bool * in, vector<vector<int>> &results) {
        if (pos >= c.size())
            return;
        in[pos] = true;
        int cur = sum + c[pos];
        if (cur == target) {
            vector<int> r;
            for (int i = 0; i < pos+1; i++) {
                if (in[i]) {
                    r.push_back(c[i]);
                }
            }
            results.push_back(r);
        }
        if (cur < target) {
            search(c, target, cur, pos+1, in, results);
        }
        in[pos] = false;
        int i = 1;
        // At each position, guarantee all duplicate values after a non-inclusive would not be included in result as well.
        // this step, together with initial sort, is crucial for skipping duplicate cases.
        // if we have 3 2s in candidates, e.g. [2,2,2], we would only get 4 unique cases:
        // [include, include, include] 2,2,2
        // [include, include, 0] 2,2
        // [include, 0, 0] 2
        // [0, 0, 0]
        // this avoids duplicates like
        // [0, include, 0] and [include, 0, 0]
        for (; pos + i < c.size(); i++) {
            if (c[pos] != c[pos+i]) {
                break;
            }
            in[pos+i] = false;
        }
        search(c, target, sum, pos+i, in, results);
    }
};

int main() {
    Solution s;
    vector<int> in = {1,1,2,1,3};
//    vector<int> in = {2,5,2,1,2};
//    vector<int> in = {10,1,2,7,6,1,5};
    vector<vector<int>> results = s.combinationSum2(in, 13);
    for (int i = 0; i < results.size(); i++) {
        for (int j = 0; j < results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }
}