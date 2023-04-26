//
// https://leetcode.com/problems/unique-binary-search-trees-ii/.
//
#include <cstdio>
#include <iostream>
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
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<vector<TreeNode*>>> dp(n+1, vector<vector<TreeNode*>>(n+1));
        return buildTrees(1, n, dp);
    }

    vector<TreeNode*> buildTrees(int l, int r, vector<vector<vector<TreeNode*>>> & dp) {
        vector<TreeNode*> results;
        if (l > r) {
            results.push_back(nullptr);
            return results;
        }
        if (dp[l][r].size() > 0)
            return dp[l][r];
        if (r == l) {
            TreeNode *newNode = new TreeNode(l);
            results.push_back(newNode);
            dp[l][r] = results;
            return results;
        }
        for (int i = l; i <= r; i++) {
            vector<TreeNode*> l_nodes = buildTrees(l, i-1, dp);
            vector<TreeNode*> r_nodes = buildTrees(i+1, r, dp);
            for (int il = 0; il < l_nodes.size(); il++) {
                for (int ir = 0; ir < r_nodes.size(); ir++) {
                    TreeNode * newNode  = new TreeNode(i, l_nodes[il], r_nodes[ir]);
                    results.push_back(newNode);
                }
            }
        }
        dp[l][r] = results;
        return results;
    }
};

void printTree(TreeNode* node) {
    if (node == nullptr) {
        printf("null,");
        return;
    }
    printf("%d,", node->val);
    if (node->left == nullptr && node->right == nullptr) {
        return;
    }
    printTree(node->left);
    if (node->right != nullptr)
        printTree(node->right);
}

int main() {
//    vector<int> a = {1,1,2,3};
//    vector<int> b = {4,5,6,7};
//    a.insert(a.end(), b.begin(), b.end());
//    for (int i = 0; i < a.size(); i++) {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
    Solution s;
    vector<TreeNode*> results = s.generateTrees(4);
    for (int i = 0; i < results.size(); i++) {
        printTree(results[i]);
        printf("\n");
    }
}