//
// https://leetcode.com/problems/house-robber-iii/
//

#include <vector>
#include <iostream>
#include <algorithm>
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
    int rob(TreeNode *root) {
        auto rp = recur(root);
        return max(rp.first, rp.second);
    }

    // return (profit w/ cur, profit w/o cur)
    pair<int, int> recur(TreeNode * cur) {
        if (!cur->left && !cur->right)
            return make_pair(cur->val, 0);
        int max_i = cur->val, max_e = 0;
        if (cur->left) {
            auto rp = recur(cur->left);
            max_i += rp.second;
            max_e += max(rp.first, rp.second);
        }
        if (cur->right) {
            auto rp = recur(cur->right);
            max_i += rp.second;
            max_e += max(rp.first, rp.second);
        }
        return make_pair(max_i, max_e);
    }
};