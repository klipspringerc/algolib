//
// https://leetcode.com/problems/the-skyline-problem/description/
// Input is list of segments with height, return list of segments representing the highest outline
// Introducing multiset, which is ordered and allows duplicate, essentially a priority queue with random removal capability
//

#include <set>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<int, greater<int>> pq;  // stores height from largest to smallest
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> points; // use greater for min heap
        for (auto & b : buildings) {
            points.push(make_pair(b[0], -b[2])); // negative height to represent start
            points.push(make_pair(b[1], b[2]));
        }
        vector<vector<int>> results;

        int cur_height = -1;
        while (!points.empty()) {
            pair<int, int> p = points.top();
            points.pop();
            int h = p.second;
            if (cur_height == -1) {
                // initialization
                cur_height = -h;
                pq.insert(cur_height);
                results.push_back({p.first, cur_height});
                continue;
            }
            if (h < 0) {
                pq.insert(-h);
            } else {
                //  end of segment
                pq.erase(pq.find(h));
            }
            int max_h;
            if (pq.size() ==0) {
                max_h = 0;
            } else {
                max_h = *pq.begin();
            }
            if (max_h != cur_height) {
                results.push_back({p.first, max_h});
                cur_height = max_h;
            }
        }
        return results;
    }
};

int main() {
    Solution s;
    vector<vector<int>> input  = {
//            {2,9,10},
//            {3,7,15},
//            {5,12,12},
//            {15,20,10},
//            {19,24,8},
//            {0,2,3},
//            {2,5,3},
            {0,10,2},
            {1,9,3},
            {2,8,5},
            {3,7,4},
            {4,6,3},
    };
    vector<vector<int>> r = s.getSkyline(input);
    for (auto & s : r) {
        printf("%d %d\n", s[0],s[1]);
    }
}