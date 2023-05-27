//
// https://leetcode.com/problems/word-ladder-ii/
// Same word ladder, but requires to output all shortest transformation sequence.
// record shortest path: save min-dist prev points for each node, then backward create paths?
// or starts with end, find path toward beginword?

#include <vector>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        vector<vector<string>> results;
        vector<vector<int>> adjlist(n+1);
        int dst = -1;
        // dst is the endword index
        // n is the begin word index
        for (int i = 0; i < wordList.size(); i++){
            if (wordList[i] == endWord)
                dst = i;
            if (cmp(wordList[i], beginWord) == 1) {
                adjlist[n].push_back(i);
                adjlist[i].push_back(n);
            }
            for (int j = i+1; j < wordList.size(); j++) {
                if (cmp(wordList[i], wordList[j]) == 1) {
                    adjlist[i].push_back(j);
                    adjlist[j].push_back(i);
                }
            }
        }
        if (dst == -1)
            return results;
        queue<pair<int, int>> q; // node, dist, path vector
        vector<int> dists(n+1, INT_MAX); // store shortest distance to nodes
        vector<vector<int>> prev(n+1); // store previous node on shortest path to nodes
        q.push(make_pair(dst, 0));
        vector<bool> visited(n+1, false);
        while (!q.empty()) {
            auto cp = q.front();
            q.pop();
            int node = cp.first;
            int dist = cp.second;
            // target is beginword, so terminate when all paths with distance <= shorted dist has been checked
            if (dist > dists[n])
                break;
            if (dists[node] < dist)
                continue;
            if (visited[node])
                continue;
            visited[node] = true;
            for (auto nb : adjlist[node]) {
                // nb as neighbor node
                int nd = dist + 1; // new distance
                if (nd > dists[nb])
                    continue;
                q.push(make_pair(nb, nd));
                if (nd == dists[nb]) {
                    prev[nb].push_back(node);
                }
                if (nd < dists[nb]) {
                    prev[nb].clear(); // prev only record prev nodes with shortest path
                    dists[nb] = nd;
                    prev[nb].push_back(node);
                }
            }
        }
        if (dists[n] == INT_MAX)
            return results;
        vector<string> pth;
        pth.push_back(beginWord);
        recur_paths(results, prev, n, dst, pth, wordList);
        return results;
    }

    void recur_paths(vector<vector<string>> & results,  vector<vector<int>> & prevs, int cur, int dst, vector<string> & cur_path, vector<string> & wl) {
        if (cur == dst) {
            results.push_back(cur_path); // vector copy
            return;
        }
        for (auto n : prevs[cur]) {
            cur_path.push_back(wl[n]);
            recur_paths(results, prevs, n, dst, cur_path, wl);
            cur_path.pop_back();
        }
    }

    int cmp( string a , string b) {
        if (a.length() != b.length() )
            return -1;
        int count = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a[i]!=b[i]) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    Solution s;
    vector<string> wl = {"hot","dot","dog","lot","log","cog"};
    auto paths = s.findLadders("hit", "log", wl);
    for (auto pth : paths) {
        for (auto s : pth)
            cout << s << " ";
        cout << endl;
    }
    cout << endl;
}