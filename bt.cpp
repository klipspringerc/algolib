//
// Determine a legitimate binary tree using its post-order traversal
// Created by Cui Shengping on 19/3/18.
//

#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

// find the split point i where arr[i] < target and arr[i+1] > target
int split_search(int arr[], int target, int lb, int rb) {
    int l = lb;
    int r = rb;
    int mid;
    while(true) {
        if (l == r) {
            return l;
        }
        mid = (l + r) / 2;
        if ((arr[mid] < target) && (arr[mid+1] > target)) {
            return mid;
        } else if (arr[mid] > target) {
            r = mid;
        } else if (arr[mid+1] < target) {
            l = mid+1;
        }
    }
}

int check_tree(int pot[], int l, int r, int upper, int lower) {
    int root = pot[r];
    // check root first
    if (root > upper || root < lower)
        return -1;
    if (l == r)
        return 1;
    if (l == r-1 && pot[l] < upper && pot[l] > lower) {
        return 2;
    } else {
        if (pot[l] > root) {
            int h = check_tree(pot, l, r-1, upper, root);
            return (h == -1)? -1 : h + 1;
        } else if (pot[r-1] < root) {
            int h = check_tree(pot, l, r-1, root, lower);
            return (h == -1)? -1 : h + 1;
        }
        int split_i = split_search(pot, root, l, r-1);
        int lh = check_tree(pot, l ,split_i, root, lower);
        int rh = check_tree(pot, split_i+1 ,r-1, upper, root);
        if (min(rh, lh) == -1)
            return -1;
        else
            return max(rh, lh)+1;
    }
}

int main() {
    int pot[] = {-1, 3,5,2,1};
    int height = check_tree(pot, 0, 4, INT32_MAX, INT32_MIN);
    if (height > 0)
        cout << "legit binary tree with height " << height << endl;
    else
        cout << "just a tree" << endl;
}

