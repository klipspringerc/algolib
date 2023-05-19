//
// https://leetcode.com/problems/network-delay-time/
// minimum delay for signal from k to reach all nodes.
// dijsktra single source dist table

#include <vector>
#include <cstdio>
#include <queue>
#include <limits>
using namespace std;


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<int> dist(n,INT_MAX);
//        vector<double> t(n, numeric_limits<double>::max());
        vector<vector<pair<int, int>>> adjList(n); // node, distance pairs.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // distance, node pairs
        vector<bool> visited(n, false);
        for (auto p: times) {
            int s= p[0], t = p[1], d = p[2];
            adjList[s].push_back(make_pair(t,d));
        }
        // now run dijsktra
        dist[k] = 0;
        pq.push(make_pair(0, k));
        while(!pq.empty()) {
            auto cur_p = pq.top();
            pq.pop();
            int cur = cur_p.second;
            int cur_d = cur_p.first;
            if (dist[cur] < cur_d)
                continue;
            if (visited[cur])
                continue;
            visited[cur] = true;
            for (auto n_p : adjList[cur]) {
                int nb = n_p.first;
                int ndist = n_p.second + cur_d;
                if (ndist < dist[nb]) {
                    dist[nb] = ndist;
                    pq.push(make_pair(ndist, nb));
                }
            }
        }
        int max_d = 0;
        for (auto d : dist) {
            if (d == INT_MAX)
                return -1;
            max_d = max(max_d, d);
        }
        return max_d;
    }
};

int main() {
    Solution s;
    vector<vector<int>> input = {
            {2,1,1}, // s, t, dist
            {2,3,1},
            {3,4,1},
    };
    printf("result: %d\n", s.networkDelayTime(input, 4, 2));
}