//
// Created by KevinCui on 22/8/18.
//


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <tuple>
//#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500010
#define LS_ONE(S) (S & (-S))

typedef long long int ll;
ll bit[MAX_N];

ll h[MAX_N];
int N, Q, T, X;
ll K;
int UPPER_LOG, UPPER_POW;
int adj_i;
ll new_h;

#define ii pair<long long, long long>
#define iii tuple<long long, long long, long long, long long>

struct segtree {
public:
    segtree(vector<long long> _num) {
        source = _num;
        n = source.size();
        tot.resize(n << 2);  // sum of current range
        pl.resize(n << 2);  // maximum prefix
        pr.resize(n << 2);  // maximum suffix
        all.resize(n << 2);  // maximum sub-sequence sum in current range
        build(1, 1, n);
    }
    void update(int at, long long val) {
        _update(1, 1, n, at, val);
    }
    long long get_lef(int l, int r) {
        if(r < l || r < 1 || n < l) {
            return 0;
        }
        ii ret = _get_lef(1, 1, n, l, r);
        return max(ret.first, ret.second);
    }
    long long get_rig(int l, int r) {
        if(r < l || r < 1 || n < l) {
            return 0;
        }
        ii ret = _get_rig(1, 1, n, l, r);
        return max(ret.first, ret.second);
    }
    long long get_all(int l, int r) {
        if(r < l || r < 1 || n < l) {
            return 0;
        }
        iii ret = _get_all(1, 1, n, l, r);
        return max(get<0>(ret), max(get<1>(ret), max(get<2>(ret), get<3>(ret))));
    }
private:
    void combine(int p, int l, int r) {
        tot[p] = tot[p + p] + tot[p + p + 1];
        pl[p] = max(pl[p + p], tot[p + p] + pl[p + p + 1]);
        pr[p] = max(pr[p + p + 1], tot[p + p + 1] + pr[p + p]);
        all[p] = max(pr[p + p] + pl[p + p + 1], max(all[p + p], all[p + p + 1]));
    }
    void build(int p, int l, int r) {
        if(l == r) {
            tot[p] = source[l - 1];
            pl[p] = max(0LL, source[l - 1]);
            pr[p] = max(0LL, source[l - 1]);
            all[p] = max(0LL, source[l - 1]);
            return;
        }
        int mid = (l + r) >> 1;
        build(p + p, l, mid);
        build(p + p + 1, mid + 1, r);
        combine(p, l, r);
    }
    void _update(int p, int l, int r, int at, long long val) {
        if(l == r) {
            tot[p] = val;
            pl[p] = max(0LL, val);
            pr[p] = max(0LL, val);
            all[p] = max(0LL, val);
            return;
        }
        int mid = (l + r) >> 1;
        if(at <= mid) {
            _update(p + p, l, mid, at, val);
        } else {
            _update(p + p + 1, mid + 1, r, at, val);
        }
        combine(p, l, r);
    }
    ii _get_lef(int p, int l, int r, int ll, int rr) {
        if(r < ll || rr < l) {
            return make_pair(0, 0);
        }
        if(ll <= l && r <= rr) {
            return make_pair(pl[p], tot[p]);
        }
        int mid = (l + r) >> 1;
        ii lef = _get_lef(p + p, l, mid, ll, rr);
        ii rig = _get_lef(p + p + 1, mid + 1, r, ll, rr);
        return make_pair(max(lef.first, lef.second + rig.first), lef.second + rig.second);
    }
    ii _get_rig(int p, int l, int r, int ll, int rr) {
        if(r < ll || rr < l) {
            return make_pair(0, 0);
        }
        if(ll <= l && r <= rr) {
            return make_pair(pr[p], tot[p]);
        }
        int mid = (l + r) >> 1;
        ii lef = _get_rig(p + p, l, mid, ll, rr);
        ii rig = _get_rig(p + p + 1, mid + 1, r, ll, rr);
        return make_pair(max(rig.first, rig.second + lef.first), lef.second + rig.second);
    }
    iii _get_all(int p, int l, int r, int ll, int rr) {
        if(r < ll || rr < l) {
            return make_tuple(0LL, 0LL, 0LL, 0LL);
        }
        if(ll <= l && r <= rr) {
            return make_tuple(pl[p], pr[p], all[p], tot[p]);
        }
        int mid = (l + r) >> 1;
        iii lef = _get_all(p + p, l, mid, ll, rr);
        iii rig = _get_all(p + p + 1, mid + 1, r, ll, rr);
        long long r1 = max(get<0>(lef), get<3>(lef) + get<0>(rig));
        long long r2 = max(get<1>(rig), get<3>(rig) + get<1>(lef));
        long long r3 = max(get<1>(lef) + get<0>(rig), max(get<2>(lef), get<2>(rig)));
        //printf("%d %d : %lld %lld %lld\n", l, r, r1, r2, r3);
        return iii(r1, r2, r3, get<3>(lef) + get<3>(rig));
    }
    int n;
    vector<long long> tot, pl, pr, all;
    vector<long long> source;
};

// change the element frequency of the tree
// adjust(n, 1), add number n into tree
// adjust(n, -1), remove number n from tree
void adjust(int n, ll op) {
    for (; n < MAX_N; n+=LS_ONE(n)) {
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
        vector<ll> funs;
        ll cur_fun;
        memset(bit, 0, sizeof bit);
        for (int i = 0; i < N+1; i++)
            scanf("%lld", h+i);
        for (int i = 0; i < N; i++) {
            if (h[i] >= h[i+1])
                cur_fun = (h[i] - h[i+1]) * (h[i] - h[i+1]);
            else
                cur_fun = 0 - (h[i] - h[i+1]) * (h[i] - h[i+1]);
            funs.push_back(cur_fun);
            adjust(i+1, h[i] + h[i+1]);
        }
        segtree seg(funs);
        for (int t = 0; t < Q; t++) {
            scanf("%d", &T);
            if (T) {
                scanf("%d %lld", &X, &K);
                ll covered = 0;
                if (X > 0)
                    covered = rsq(X);
                int l = X,r = N;
                ll v = K+covered;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (rsq(mid) <= v)
                        l = mid;
                    else
                        r = mid-1;
                }
                int east_bound = l;
//                if (rsq(east_bound) != K+covered)
//                    east_bound--;
                ll max_fun = 0;
                ll cur_sum = 0;
                max_fun = seg.get_all(1, east_bound);
                printf("%lld\n", max_fun);
            } else {
                // adjusted indexed position and new height value
                scanf("%d %lld", &adj_i, &new_h);
                if (adj_i < N) {
                    if (new_h >= h[adj_i+1])
                        seg.update(adj_i+1, (new_h - h[adj_i+1]) * (new_h - h[adj_i+1]));
                    else
                        seg.update(adj_i+1, 0-(new_h - h[adj_i+1]) * (new_h - h[adj_i+1]));
                    adjust(adj_i+1, new_h - h[adj_i]);
                }
                if (adj_i > 0) {
                    if (h[adj_i-1] >= new_h)
                        seg.update(adj_i, (new_h - h[adj_i-1]) * (new_h - h[adj_i-1]));
                    else
                        seg.update(adj_i, 0-(new_h - h[adj_i-1]) * (new_h - h[adj_i-1]));
                    adjust(adj_i, new_h - h[adj_i]);
                }
                h[adj_i] = new_h;
            }
        }

    }

}