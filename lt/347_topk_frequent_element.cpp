//
// https://leetcode.com/problems/top-k-frequent-elements/
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        unordered_set<int> visit;
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;
        for (int n : nums) {
            freq[n]++;
            pq.push(make_pair(freq[n], n));
        }
        int count = 0;
        vector<int> results;
        while (count < k) {
            auto p = pq.top();
            pq.pop();
            if (visit.find(p.second) == visit.end()) {
                count++;
                results.push_back(p.second);
                visit.insert(p.second);
            }
        }
        return results;
    }
};

int main() {
    vector<int> input = {1,1,1,2,2,3};
    Solution s;
    vector<int> r = s.topKFrequent(input, 3);
    for (int v : r)
        cout << v << ", ";
    cout <<endl;
}
