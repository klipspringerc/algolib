//
// segment tree for maximum sub-sequence sum
// Created by KevinCui on 28/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
using namespace std;

#define L(S) (S*2)
#define R(S) (S*2+1)

typedef long long int ll;
typedef tuple<ll,ll,ll,ll> tp4l;
typedef vector<ll> vll;

// suf for maximum suffix sum
// pre for maximum prefix sum
// tot for total sum
// mss for minimum sum
struct segment_tree {
public:
    void build() {
        _build(1, 1, n);
    }
private:
    vll tot, suf, pre, mss;
    int n;
    void _build(int p, int l, int r) {
    }

    void combine(int p) {
        tot[p] = tot[L(p)] + tot[R(p)];
        pre[p] = max(tot[L(p)] + pre[R(p)], pre[L(p)]);
        suf[p] = max(tot[R(p)] + suf[L(p)], suf[R(p)]);
        mss[p] = max(suf[R(p)] + pre[L(p)], max(mss[L(p)], mss[R(p)]));
    }

};

