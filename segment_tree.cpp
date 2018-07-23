//
// Created by KevinCui on 17/7/18.
//

#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct Node {
    int lb;
    int rb;
    int data;
    Node* left;
    Node* right;
} Tree;

Tree* build_tree(int l, int r) {
    Tree* tree_node = (Tree*) malloc(sizeof(Tree));
    tree_node->data = 0;
    tree_node->lb = l;
    tree_node->rb = r;
    if (l == r) return tree_node;
    int mid = (l + r) >> 1;
    tree_node->left = build_tree(l, mid);
    tree_node->right = build_tree(mid, r);
    return tree_node;
}

Tree* build_tree_with_array(int num[], int l, int r) {
    Tree* tree_node = (Tree*) malloc(sizeof(Tree));
    tree_node->lb = l;
    tree_node->rb = r;
    if (l == r) {
        tree_node->data=num[l];
        return tree_node;
    }
    int mid = (l + r) >> 1;
    tree_node->left = build_tree_with_array(num, l, mid);
    tree_node->right = build_tree_with_array(num, mid+1, r);
    tree_node->data = tree_node->left->data + tree_node->right->data;
    return tree_node;
}

int get_range_sum(Tree* node, int l, int r) {
    if (node->lb == l && node->rb == r)
        return node->data;
    int mid = (node->lb + node->rb) >> 1;
    if (l > mid)
        return get_range_sum(node->right, l, r);
    else if (r <= mid)
        return get_range_sum(node->left, l, r);
    else
        return get_range_sum(node->left, l, mid) + get_range_sum(node->right, mid+1, r);
}

void update_range(Tree* node, int l, int r, int adjust) {
    if (l == r)
        node->data += adjust;
    else {
        int mid = (node->lb + node->rb) >> 1;
        if (l > mid) {
            update_range(node->right, l, r, adjust);
        } else if (r <= mid) {
            update_range(node->left, l, r, adjust);
        } else {
            update_range(node->left, l, mid, adjust);
            update_range(node->right, mid+1, r, adjust);
        }
        node->data = node->left->data + node->right->data;
    }
}

int main() {
    int num[] = {1,53,22,5,63,42,9,11,16};
    printf("original array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", num[i]);
    printf("\n");
    Tree* s_tree = build_tree_with_array(num, 0, 8);
    printf("query range sum %d-%d: %d\n", 3, 5, get_range_sum(s_tree, 3,5));
    printf("query range sum %d-%d: %d\n", 2, 8, get_range_sum(s_tree, 2,8));
    printf("query range sum %d-%d: %d\n", 0, 4, get_range_sum(s_tree, 0,4));
    update_range(s_tree, 0, 2, 10);
    printf("---adjust 0-2 by 10---\n");
    printf("query range sum %d-%d: %d\n", 3, 5, get_range_sum(s_tree, 3,5));
    printf("query range sum %d-%d: %d\n", 2, 8, get_range_sum(s_tree, 2,8));
    printf("query range sum %d-%d: %d\n", 0, 4, get_range_sum(s_tree, 0,4));
    update_range(s_tree, 5, 8, -10);
    printf("---adjust 5-8 by -10---\n");
    printf("query range sum %d-%d: %d\n", 3, 5, get_range_sum(s_tree, 3,5));
    printf("query range sum %d-%d: %d\n", 2, 8, get_range_sum(s_tree, 2,8));
    printf("query range sum %d-%d: %d\n", 0, 4, get_range_sum(s_tree, 0,4));
    printf("query range sum %d-%d: %d\n", 1, 1, get_range_sum(s_tree, 1,1));
    printf("query range sum %d-%d: %d\n", 3, 3, get_range_sum(s_tree, 3,3));
    printf("query range sum %d-%d: %d\n", 8, 8, get_range_sum(s_tree, 8,8));

}