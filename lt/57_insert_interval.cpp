//
// https://leetcode.com/problems/insert-interval/description/
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // using binary search would not improve worst case complexity, since inset in vector has linear complexity
        if (intervals.size() == 0) {
            intervals.push_back(newInterval);
            return intervals;
        }
        // if new interval is larger than the last interval, merge/append at the end then return
        if (newInterval[0] > intervals[intervals.size() - 1][0]) {
            vector<int> cur = intervals[intervals.size() - 1];
            if (cur[1] >= newInterval[0]) {
                intervals[intervals.size() - 1][1] = max(newInterval[1], cur[1]);
            } else {
                intervals.push_back(newInterval);
            }
            return intervals;
        }
        bool merging = false;
        bool completed = false;
        vector<vector<int>> results;
        for (int i = 0; i < intervals.size(); i++) {
            vector<int> ptr = intervals[i];
            if (completed) {
                results.push_back(ptr);
                continue;
            }
            if (!merging) {
                // if current interval start is already larger than newInterval, or if already at interval end,
                // push_back newInterval to results end, merge if overlap
                if (newInterval[0] <= ptr[0]) {
                    merging = true;
                    if (results.size() && results[results.size()-1][1] >= newInterval[0]) {
                        results[results.size()-1][1] = max(newInterval[1], results[results.size()-1][1]);
                    } else {
                        results.push_back(newInterval);
                    }
                } else {
                    results.push_back(ptr);
                    continue;
                }
            }
            // then go through normal merge logic
            if (merging) {
                vector<int> cur = results[results.size()-1];
                if (cur[1] >= ptr[0]) {
                    results[results.size()-1][1] = max(cur[1], ptr[1]);
                } else {
                    results.push_back(ptr);
                    completed = true; // completed newInterval insertion, no need to check for merge for subsequent intervals
                }
            }
        }
        return results;
    }
};

int main() {
    Solution s;

//    vector<vector<int>> in = {{1,3}, {6,9}};
//    vector<int> new_in = {2,5};
//    vector<vector<int>> in = {{1,3}, {4,5}, {6,7}, {8,10}, {12,16}};
//    vector<int> new_in = {17,18};
    vector<vector<int>> in = {{-3, 2}};
    vector<int> new_in = {2,5};
    vector<vector<int>> results = s.insert(in, new_in);
    printf("results:");
    for (int i = 0; i < results.size(); i++) {
        printf("\n    ");
        for (int j = 0; j < results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
    }
}