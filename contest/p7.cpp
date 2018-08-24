//
// Created by KevinCui on 22/8/18.
//


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_N 500010
#define LS_ONE(S) (S & (-S))

typedef long long int ll;
ll bit[MAX_N];

ll h[MAX_N];
ll fun[MAX_N];
ll cost[MAX_N];
int N, Q, T, X;
ll K;
int UPPER_LOG, UPPER_POW;
int adj_i;
ll new_h, new_fun_l, new_fun_r;

// change the element frequency of the tree
// adjust(n, 1), add number n into tree
// adjust(n, -1), remove number n from tree
void adjust(int n, ll op) {
    for (; n < UPPER_POW; n+=LS_ONE(n)) {
        bit[n] += op;
    }
}

ll rsq(int b) {                                     // returns RSQ(1, b)
    ll sum = 0; for (; b; b -= LS_ONE(b)) sum += bit[b];
    return sum; }

ll rsq(int a, int b) {                              // returns RSQ(a, b)
    return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

// find the k-th element
// note the back-off when sum == k. this is because when sum==k,
// the ans may not be the actual k-th value due to property of BIT (bit[ans] might be some parent node of target)
// we go to find sum == k-1 instead, then return ans+1
// for example, if bit[4]=4 and bit[5]=bit[6]=1, bit[7]=0, bit[8]=5,then find(5) may encounter ans=8 and ans=6 when sum=k.
// so we back-off, find bit[4]=4 first, then return 4+1=5, which is the correct answer.
// or if bit[5]=0 bit[6]=1 and others unchanged, we would find bit[4]=4, then bit[5]=0, then return 5+1=6, which is the correct answer.
int find_kth(int k) {
    int ans = 0; ll sum = 0;
    for (int i = UPPER_LOG; i >= 0; i--) {
        ans += (1 << i);
        if (ans > N+1 || sum + bit[ans] >= k) {
            ans -= (1 << i);
        } else {
            sum += bit[ans];
        }
    }
    return ans+1;
}


int main() {
//    memset(bit, 0, sizeof bit);
//    adjust(1, 16);
//    adjust(2, 5);
//    adjust(3, 9);
//    adjust(4, 24);
//    adjust(5, 14);
//    puts("rsq");
//    for (int i = 1; i < 6; i++)
//        printf("%d\n", rsq(i));
//    puts("findkth");
//    printf("%d\n", find_kth(20));
//    printf("%d\n", find_kth(30));
    while (scanf("%d %d", &N, &Q) == 2) {
        UPPER_LOG = (int)((log((double)N) / log(2.0))) + 1;
        UPPER_POW = (int)(pow(2.0, UPPER_LOG));
        memset(bit, 0, sizeof bit);
        for (int i = 0; i < N+1; i++)
            scanf("%lld", h+i);
        for (int i = 0; i < N; i++) {
            if (h[i] >= h[i+1])
                fun[i] = (h[i] - h[i+1]) * (h[i] - h[i+1]);
            else
                fun[i] = 0 - (h[i] - h[i+1]) * (h[i] - h[i+1]);
            cost[i] = h[i] + h[i+1];
            adjust(i+1, cost[i]);
        }
        for (int t = 0; t < Q; t++) {
            scanf("%d", &T);
            if (T) {
                scanf("%d %lld", &X, &K);
                ll covered = 0;
                if (X > 0)
                    covered = rsq(X);
                int east_bound = find_kth(K+covered);
//                printf("range cost: %lld\n", rsq(east_bound));
                if (rsq(east_bound) != K+covered)
                    east_bound--;
//                printf("range cost: %lld\n", rsq(east_bound));
                ll max_fun = 0;
                ll cur_sum = 0;
                east_bound = min(N, east_bound);
//                printf("east bound: %d\n", east_bound);
                for (int i = 0; i < east_bound; i++) {
                    cur_sum += fun[i];
                    max_fun = max(max_fun, cur_sum);
                    if (cur_sum < 0)
                        cur_sum = 0;
                }
                printf("%lld\n", max_fun);
            } else {
                // adjusted indexed position and new height value
                scanf("%d %lld", &adj_i, &new_h);
                if (adj_i < N) {
                    cost[adj_i] += new_h - h[adj_i];
                    if (new_h >= h[adj_i+1])
                        fun[adj_i] = (new_h - h[adj_i+1]) * (new_h - h[adj_i+1]);
                    else
                        fun[adj_i] = 0-(new_h - h[adj_i+1]) * (new_h - h[adj_i+1]);
                }
                if (adj_i > 0) {
                    cost[adj_i - 1] += new_h - h[adj_i];
                    if (h[adj_i-1] >= new_h)
                        fun[adj_i-1] = (new_h - h[adj_i-1]) * (new_h - h[adj_i-1]);
                    else
                        fun[adj_i-1] = 0-(new_h - h[adj_i-1]) * (new_h - h[adj_i-1]);
                }
                adjust(adj_i, new_h - h[adj_i]);
                adjust(adj_i+1, new_h - h[adj_i]);
                h[adj_i] = new_h;
            }
        }

    }

}