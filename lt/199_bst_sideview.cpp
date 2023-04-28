//
// https://leetcode.com/problems/binary-tree-right-side-view/
//
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

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
    vector<int> rightSideView(TreeNode* root) {
        TreeNode * ptr = root;
        vector<int> result;
        vector<int> curidx;
        sideViewRecur(root, 0, 0, result, curidx);
        return result;
    }

    void sideViewRecur(TreeNode* ptr, int level, int idx, vector<int> & result, vector<int> & curidx) {
        if (ptr == nullptr)
            return;
        if (level + 1 > result.size()) {
            result.push_back(ptr->val);
            curidx.push_back(idx);
        } else {
            if (curidx[level] < idx) {
                result[level] = ptr->val;
                curidx[level] = idx;
            }
        }
        sideViewRecur(ptr->left, level+1, idx * 2 + 1, result, curidx);
        sideViewRecur(ptr->right, level+1, idx * 2 + 2, result, curidx);
    }
};