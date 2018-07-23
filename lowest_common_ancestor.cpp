//
// Created by KevinCui on 20/7/18.
//


#include <cstdio>
#include <cstdlib>
#include <tuple>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

typedef tuple<TreeNode*, bool, bool> tbb;

// the returned tuple: 0: lca found , 1: p found , 2: q found
// can handle cases including p, q not present, duplicated nodes
tbb lca_recur(TreeNode *node, TreeNode* p, TreeNode* q) {
    if (node == NULL) {
        return tbb(NULL, false, false);
    }
    tbb result_l = lca_recur(node->left, p, q);
    tbb result_r = lca_recur(node->right, p, q);
    if (get<0>(result_l) != NULL)
        return result_l;
    if (get<0>(result_r) != NULL)
        return result_r;
    bool find_p = get<1>(result_l) || get<1>(result_r);
    bool find_q = get<2>(result_l) || get<2>(result_r);
    if ((find_p && find_q) || (node->val == p->val && find_q) || (node->val == q->val && find_p)) {
        return tbb(node, true, true);
    } else {
        return tbb(NULL, node->val == p->val || find_p, node->val == q->val || find_q);
    }
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    tbb result = lca_recur(root, p, q);
    return get<0>(result);
}

int main() {
    tbb t = tbb(NULL, false, false);
}


