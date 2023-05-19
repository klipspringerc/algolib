//
// https://leetcode.com/problems/evaluate-division/
//

#include <vector>
#include <string>
#include <unordered_set>
#include <cstdio>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, vector<pair<string, double>>> adjList;
        unordered_map<string, unordered_map<string, double>> dp;
        size_t n = equations.size();
        for (int i = 0; i < n; i++) {
            double ratio = values[i];
            string node1 = equations[i][0];
            string node2 = equations[i][1];
            adjList[node1].push_back(make_pair(node2, ratio));
            adjList[node2].push_back(make_pair(node1, 1.0/ratio));
        }
        vector<double> results;
        for (auto qr: queries) {
            string src = qr[0];
            string dst = qr[1];
            if (adjList.find(src) == adjList.end() || adjList.find(dst) == adjList.end()) {
                results.push_back(-1.0);
                continue;
            }
            // run bfs
            queue<pair<string, double>> q;
            q.push(make_pair(src, 1.0));
            unordered_set<string> visited;
            bool found = false;
            while(!q.empty()) {
                auto cur = q.front();
                double ratio = cur.second;
                q.pop();
                string node = cur.first;
                if (node == dst) {
                    found = true;
                    results.push_back(ratio);
                    break;
                }
                if (visited.count(node) > 0)
                    continue;
                visited.insert(node);
                if (adjList.find(node) == adjList.end()) {
                    continue;
                }
                auto adj = adjList[node];
                for (auto nb_p : adj) {
                    string nb = nb_p.first;
                    if (visited.count(nb) > 0)
                        continue;
                    q.push(make_pair(nb_p.first, ratio * nb_p.second));
                }
            }
            if (!found)
                results.push_back(-1.0);
        }
        return results;
    }
};

int main() {
    vector<vector<string>> input = {
            {"a","b"},
            {"b","c"},
            {"c","d"},

    };
    vector<vector<string>> queries = {
            {"a","d"},
            {"c","b"},
            {"d","b"},
            {"d","d"},
            {"f","d"},
            {"f","f"},
    };
    vector<double> values = {2.0,3.0, 4.0};
    Solution s;
    vector<double> r = s.calcEquation(input, values, queries);
    for (auto v : r) {
        printf("%lf, ", v);
    }
    puts("");
}