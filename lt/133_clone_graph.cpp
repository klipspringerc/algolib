//
// https://leetcode.com/problems/clone-graph/
//

#include <vector>
#include <unordered_map>
using namespace std;


class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    unordered_map<int, Node*> visited;
    Node* cloneGraph(Node* node) {
        Node * n = new Node(node.val);
        visited[n->val] = n;
        for (auto nb : node->neighbors) {
            if (visited.find(nb->val) != visited.end()) {
                n->neighbors.push_back(visited[nb->val]);
            } else {
                n->neighbors.push_back(cloneGraph(nb));
            }
        }
        return n;
    }
};