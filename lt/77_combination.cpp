//
// https://leetcode.com/problems/combinations/description/
// Return all possible combination
// Simple backtrack
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> cur(k);
        recur(0, 1, n, cur, result);
        return result;
    }

    // cur: current result stack
    // next: next value in [1,n] to be filled in cur
    // step: which index in cur to fill next value
    void recur(int step, int next, int n, vector<int> & cur, vector<vector<int>> & results) {
        if (step == cur.size()) {
            vector<int> r(cur);
            results.push_back(r);
            return;
        }
        for (int i = next; i < n+1; i++) {
            // if slot to be filled is more than remaining number in [next, n], return
            if (cur.size() - step > n-i+1) {
                return;
            }
            cur[step] = i;
            recur(step+1, i+1, n, cur, results);
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> result = s.combine(10,10);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            printf(" %d", result[i][j]);
        }
        printf("\n");
    }
}