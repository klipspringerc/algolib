//
// Longest increasing sub sequence
// Created by Cui Shengping on 10/4/18.
//

#include <cstdlib>
#include <algorithm>
#include <stack>

using namespace std;

#define MAX_N 100

void reconstruct_print(int end, int a[], int p[]) {
    int i = end;
    stack<int> s;
    for (; p[i] >= 0; i = p[i]) s.push(a[i]);
    printf("%d ", a[i]);
    for (; !s.empty(); s.pop())
        printf("%d ", s.top());
    printf("\n");
}


void lis(int A[], int n) {
    int lis = 0, lis_end = 0;
    int P[MAX_N], L[MAX_N], L_id[MAX_N];
    for (int i = 0 ; i < n; i++) {
        int pos = lower_bound(L, L+lis, A[i]) - L;
        L[pos] = A[i];
        P[i] = pos? L_id[pos-1] : -1;
        L_id[pos] = i;
        if (pos + 1 > lis) {
            lis = pos+1;
            lis_end = i;
        }
    }
    // print array
    stack<int> s;
    int x = lis_end;
    for (; x >= 0; x = P[x]) s.push(A[x]);
    printf("LIS (length %d): ", lis);
    for (; !s.empty(); s.pop()) printf("%d ", s.top());
    printf("\n");
}


int main() {
    // LIS
    int n = 11;
    int a[] = {-7, 10,1, 9, 3, 8, 8, 1, 2, 3, 4};
    lis(a, n);
    int P[MAX_N]; // track the original index of the previous element in an increasing subsequence
    int L[MAX_N]; // aux array to place sub sequence
    int L_Pos[MAX_N]; // translate L index to original array index.
    int lis = 0; // tracks length of current LIS
    int lis_end = 0; // current LIS ending position

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(L, L+lis, a[i]) - L; // find the insertion position
        L[pos] = a[i];
        L_Pos[pos] = i;
        P[i] = pos? L_Pos[pos-1] : -1;
        if (pos + 1 > lis) {
            lis = pos + 1;
            lis_end = i;
        }
    }
    printf("Longest Increasing Subsequence: \n");
    reconstruct_print(lis_end, a, P);
    return 0;
}

