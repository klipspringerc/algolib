//
// https://leetcode.com/problems/binary-tree-maximum-path-sum/
// Recursively iterate BST
// At each node, return current max that is connectable to parent node and current max that is not connectable to parent node (l -> n -> r path)

#include <tuple>
#include <cstdio>
#include <vector>
using namespace std;

// Definition for a binary tree node.
  struct TreeNode {
      int val;
     TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };


class Solution {
public:
    int maxPathSum(TreeNode* root) {
        tuple<int, int> r = sumRecur(root);
        return max(get<0>(r), get<1>(r));
    }

    // returns {connectable max, non_connectable max}
    tuple<int, int> sumRecur(TreeNode *root) {
        if (root == nullptr)
            return tuple<int, int> {INT_MIN,INT_MIN};
        tuple<int, int> tl = sumRecur(root->left);
        tuple<int, int> tr = sumRecur(root->right);
        int val = root->val;
        int connectable_sum = max(get<0>(tl), get<0>(tr));
        // path connectable to parent must include the current node.
        connectable_sum = max(connectable_sum + val, val);
        int no_connection_max = max(get<1>(tl), get<1>(tr));
        // bridge left and right path to form a path, not connectable to parent node.
        int bridge_sum = val + get<0>(tl) + get<0>(tr);
        if (bridge_sum > no_connection_max)
            no_connection_max = bridge_sum;
        if (connectable_sum > no_connection_max)
            no_connection_max = connectable_sum;
        return tuple<int, int> {connectable_sum, no_connection_max};
    }
};

int main() {
    Solution s;
    s.maxPathSum();
}