//
// Created by KevinCui on 13/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>

int cuts[51];
int dp[60][60];

int L, N;

int min(int a, int b) {
    return (a < b)? a: b;
}

int cut_rod(int l, int r) {
    if (dp[l][r] != -1)
        return dp[l][r];
    int min_cost = 1e9;
    if (l == r)
        min_cost = 0;
    else {
        min_cost = min(min_cost, cut_rod(l + 1, r));
        min_cost = min(min_cost, cut_rod(l, r-1));
        for (int i = l+1; i < r; i++) {
            min_cost = min(min_cost, cut_rod(l, i-1) + cut_rod(i+1, r));
        }
    }
    int lb = (l == 0)? 0 : cuts[l-1];
    int rb = (r == N-1)? L : cuts[r+1];
    return (dp[l][r] = min_cost + rb-lb);
}

int main() {
    while (scanf("%d", &L) && L) {
        scanf("%d", &N);
        memset(dp, -1, sizeof dp);
        for (int n = 0; n < N; n++) {
            scanf("%d", &cuts[n]);
        }
        printf("The minimum cutting is %d.\n", cut_rod(0,N-1));
    }
}