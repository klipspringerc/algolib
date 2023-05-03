//
// Created by SG0014000445M on 2023/5/3.
//

#include <vector>
#include <cstdio>
#include <unordered_map>
using namespace std;


/**
 * Definition for a binary tree node.
 * */
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> v_to_idx;
        for (int i = 0 ; i < inorder.size(); i++) {
            v_to_idx[inorder[i]] = i;
        }
        return buildRecur(inorder, postorder, v_to_idx, 0, postorder.size()-1, 0, inorder.size()-1);
    }

    // return the subtree built from post order and inorder range [l,r]
    // inorder range left: il, right: rl
    // postorder range left: pl, right: pr
    // subtree root always at the last element of post order traversal.
    TreeNode * buildRecur(vector<int>& inorder, vector<int>& postorder, unordered_map<int, int> & v_to_idx, int pl, int pr, int il, int ir) {
        int root_val = postorder[pr];
        TreeNode * root = new TreeNode(root_val);
        if (pl == pr)
            return root;
        int pos = v_to_idx[root_val];
        int num_left = pos - il;
        int num_right = ir - pos;
        if (num_right > 0) {
            int right_subtree_pr = pr-1;
            int right_subtree_pl = pr - num_right;
            root->right = buildRecur(inorder, postorder, v_to_idx, right_subtree_pl, right_subtree_pr, pos+1, ir);
        } else {
            root->right = nullptr;
        }
        if (num_left > 0) {
            int left_subtree_pr = pr - num_right - 1;
            int left_subtree_pl = pr - num_right - num_left;
            root->left =  buildRecur(inorder, postorder, v_to_idx, left_subtree_pl, left_subtree_pr, il, pos-1);
        } else {
            root->left = nullptr;
        }
        return root;
    }
};

int main() {
    Solution s;

}