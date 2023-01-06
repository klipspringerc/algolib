//
// https://leetcode.com/problems/merge-intervals/
//

#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    static bool comp(vector<int> a, vector<int> b) {
        return(a[0] < b[0]);
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> results;
        sort(intervals.begin(), intervals.end(), comp);
        results.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            vector<int> ptr = intervals[i];
            vector<int> cur = results[results.size()-1];
            if (cur[1] >= ptr[0]) {
//                printf(">>>extending current interval end to %d\n", max(cur[1], ptr[1]));
                results[results.size()-1][1] = max(cur[1], ptr[1]);
            } else {

                vector<int> new_interval(intervals[i]);
                results.push_back(new_interval);
            }
        }
        return results;
    }

};

int main() {
    Solution s;
    vector<vector<int>> in = {{3,4}, {2,6},{9,10}};
    vector<vector<int>> results = s.merge(in);
    printf("results:");
    for (int i = 0; i < results.size(); i++) {
        printf("\n    ");
        for (int j = 0; j < results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
    }
}


