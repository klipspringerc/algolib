//
// Created by Cui Shengping on 24/3/18.
//

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node * left;
    Node * right;
    int height;
};

int max(int a, int b) {
    return (a > b)? a : b;
}

int height(Node * node) {
    if (node == nullptr)
        return -1;
    return node->height;
}

int get_balance(Node * node) {
    if (node == nullptr)
        return 0;
    return height(node->right) - height(node->left);
}

Node * new_node(int key) {
    auto node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;
    return node;
}

Node * right_rotate(Node * y) {
    Node * x = y->left;
    Node * xr = x->right;
    x->right = y;
    y->left = xr;
    y->height = max(height(xr), height(y->right)) + 1;
    x->height = max(height(x->left), height(y)) + 1;
    return x;
}

Node * left_rotate(Node * y) {
    Node * x = y->right;
    Node * xl = x->left;
    x->left = y;
    y->right = xl;
    y->height = max(height(xl), height(y->left)) + 1;
    x->height = max(height(x->right), height(y)) + 1;
    return x;
}

Node * min_value_node(Node * node) {
    Node * cur = node;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

Node * insert(Node * node, int key) {
    if (node == nullptr)
        return new_node(key);
    if (node->key > key)
        node->left = insert(node->left, key);
    if (node->key < key)
        node->right = insert(node->right, key);
    if (node->key == key)
        return node;
    node->height = max(height(node->left), height(node->right)) + 1;
    int b = get_balance(node);
    if (b < -1) {
        if (key < node->left->key)
            return right_rotate(node);
        if (key > node->left->key) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    } else if (b > 1) {
        if (key < node->right->key) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
        if (key > node->right->key) {
            return left_rotate(node);
        }
    }
    return node;
}

Node * delete_node(Node * node, int key) {
    if (node == nullptr)
        return nullptr;
    if (node->key > key)
        node->left = delete_node(node->left, key);
    if (node->key < key)
        node->right = delete_node(node->right, key);
    if (node->key == key) {
        if (node->right == nullptr) {
            free(node);
            node = node->left;
        } else if (node->left == nullptr) {
            free(node);
            node = node->right;
        } else {
            Node * replace = min_value_node(node->right);
            node->key = replace->key;
            node->right = delete_node(node->right, node->key);
        }
    }
    if (node == nullptr)
        return node;
    node->height = max(height(node->left), height(node->right)) + 1;
    int b = get_balance(node);
    if (b < -1) {
        if (get_balance(node->left) <= 0)
            return right_rotate(node);
        if (get_balance(node->left) > 0) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    } else if (b > 1) {
        if (get_balance(node->right) < 0) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
        if (get_balance(node->right) >= 0)
            return left_rotate(node);
    }
    return node;
}

void flat_tree_recur(Node * node, int* arr, int i) {
    if (node != nullptr) {
        arr[i] = node->key;
        flat_tree_recur(node->left, arr, 2*i+1);
        flat_tree_recur(node->right, arr, 2*i+2);
    }
}

void print_tree(Node * node) {
    int h = height(node);
    int length = int(pow(2, h+1))-1;
    auto arr = (int *) malloc (length * sizeof(int));
    memset(arr, -1, length*sizeof(int));
    flat_tree_recur(node, arr, 0);
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout <<endl;
}

int main() {
    Node * root = new_node(5);
//    root = insert(root, 1);
//    root = insert(root, 3);
//    print_tree(root);
//    root = insert(root, 2);
//    root = insert(root, 4);
//    print_tree(root);
//    root = insert(root, 10);
//    root = insert(root, 11);
//    print_tree(root);
//    root = insert(root, 13);
//    root = insert(root, 0);
//    print_tree(root);
//    root = delete_node(root, 11);
    root = insert(root, 1);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 2);
    print_tree(root);
    root = delete_node(root, 10);
    print_tree(root);
//    cout << root->left->key << endl;
    return 0;
}




