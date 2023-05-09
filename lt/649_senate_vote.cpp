
//
// https://leetcode.com/problems/dota2-senate/
// RDRDRDR / seems to be a greedy game, where each senate would ban the first subsequent opponent
// use ordered set as data structure for efficient retrieval of first R/D position after a given index
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.length();
        set<int> rq, dq; // index queue
        for (int i= 0; i < n; i++) {
            switch (senate[i]) {
                case 'R':
                    rq.insert(i);
                    break;
                case 'D':
                    dq.insert(i);
                    break;
            }
        }
        int idx = 0;
        while (!rq.empty() && !dq.empty()) {
            set<int>::iterator pos;
                switch (senate[idx]) {
                    case 'R':
                        pos = dq.upper_bound(idx);
                        if (pos == dq.end())
                            pos = dq.begin();
                        dq.erase(pos);
                        break;
                    case 'D':
                        pos = rq.upper_bound(idx);
                        if (pos == rq.end())
                            pos = rq.begin();
                        rq.erase(pos);
                        break;
                }
            if (rq.empty() || dq.empty())
                break;
            auto ritr = rq.upper_bound(idx);
            auto ditr = dq.upper_bound(idx);
            // if reach end, start from the begining again
            if (ritr == rq.end() && ditr == dq.end())
                idx = min(*rq.begin(), *dq.begin());
            else if (ritr != rq.end() && ditr != dq.end())
                idx = min(*ritr, *ditr);
            else if (ritr == rq.end())
                idx = *ditr;
            else
                idx = *ritr;
        }

        if (rq.empty())
            return "Dire";
        else
            return "Radiant";
    }
};

int main() {
    Solution s;
    string input = "RDDDRRRD";
    cout << s.predictPartyVictory(input) << endl;
}