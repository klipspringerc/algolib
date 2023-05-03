//
// https://leetcode.com/problems/word-ladder/
// construct graph with modification distance 1 as connected word
// then perform shortest path on graph

#include <vector>
#include  <string>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord == endWord)
            return 1;
        int n = wordList.size();
        vector<vector<int>> adjList(n+1);
        int dst = -1;
        for (int i = 0; i < n; i++) {
            if (endWord == wordList[i])
                dst = i;
            for (int j = i+1; j < n; j++) {
                if (cmpstr(wordList[i], wordList[j]) == 1) {
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
            if (cmpstr(beginWord, wordList[i]) == 1) {
                adjList[n].push_back(i);
            }
        }
        if (dst == -1)
            return 0;
        int begin = n; // n as begin word id

        // now run normal shortest path
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(1, begin));
        vector<bool>visited(n+1, false);
        while (!pq.empty()) {
            pair<int, int> cur = pq.top();
            pq.pop();
            int node = cur.second;
            int d = cur.first;
            if (node == dst)
                return d;
            if (visited[node])
                continue;
            visited[node] = true;
            for (int neighbor : adjList[node]) {
                if (visited[neighbor])
                    continue;
                pq.push(make_pair(d+1, neighbor));
            }
        }
        return 0;

    }
    int cmpstr(string a, string b) {
        int n = a.length();
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                count++;
                if (count > 1)
                    return count;
            }
        }
        return count;
    }


    int ladderLengthRefBFS(string beginWord, string endWord, vector<string>& wordList) {
        // note the initialization trick here
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> todo; // all distance 1, no need for priority queue,normal queue for BFS
        todo.push(beginWord);
        int ladder = 1;
        while (!todo.empty()) {
            int n = todo.size();
            for (int i = 0; i < n; i++) {
                string word = todo.front();
                todo.pop();
                if (word == endWord) {
                    return ladder;
                }
                dict.erase(word);
                // this search here is 26 * wordLen
                // better with wordlist length is much larger than word length
                for (int j = 0; j < word.size(); j++) {
                    char c = word[j];
                    for (int k = 0; k < 26; k++) {
                        word[j] = 'a' + k;
                        if (dict.find(word) != dict.end()) {
                            todo.push(word);
                        }
                    }
                    word[j] = c;
                }
            }
            ladder++;
        }
        return 0;
    }
    int ladderLengthBidirectionBFS(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end()), head, tail, *phead, *ptail;
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }
        head.insert(beginWord);
        tail.insert(endWord);
        int ladder = 2;
        // head and tail set contains the search boundary of BFS from begin / end word
        while (!head.empty() && !tail.empty()) {
            if (head.size() < tail.size()) {
                phead = &head;
                ptail = &tail;
            } else {
                phead = &tail;
                ptail = &head;
            }
            unordered_set<string> temp;
            for (auto it = phead -> begin(); it != phead -> end(); it++) {
                string word = *it;
                for (int i = 0; i < word.size(); i++) {
                    char t = word[i];
                    for (int j = 0; j < 26; j++) {
                        word[i] = 'a' + j;
                        // if head's search boundary overlap with tail's boundary, then a path is found,
                        if (ptail -> find(word) != ptail -> end()) {
                            return ladder;
                        }
                        if (dict.find(word) != dict.end()) {
                            temp.insert(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = t;
                }
            }
            ladder++;
            phead -> swap(temp);
        }
        return 0;
    }
};

int main() {
    Solution s;
    vector<string> wl = {"hot","dot","dog","lot","log","cog"};
    printf("min distance: %d\n", s.ladderLength("cog", "cog", wl));
}