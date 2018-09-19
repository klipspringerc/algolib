//
// segment tree for maximum sub-sequence sum
// Created by KevinCui on 28/8/18.
//

#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
using namespace std;

#define L(S) (S*2+1)
#define R(S) (S*2+2)

typedef long long ll;
typedef tuple<ll,ll,ll,ll> llll;
typedef vector<ll> vll;


// suf for maximum suffix sum
// pre for maximum prefix sum
// tot for total sum
// mss for maximum subsequence sum
struct segment_tree {
public:
    segment_tree(vector<ll> & _source) {
        source = _source;
        n = _source.size();
        tot.resize(n << 2);
        mss.resize(n << 2);
        pre.resize(n << 2);
        suf.resize(n << 2);
        _build(0, 0, n-1);
    }

    void update(int at, ll val) {
        _update(0, 0, n-1, at, val);

    }

    ll get_mss(int l, int r) {
        llll res = _get_mss(0, 0, n-1, l, r);
        return max(get<0>(res), max(get<1>(res), max(get<2>(res), get<3>(res))));
    }
private:
    vll tot, suf, pre, mss, source;
    int n;

    void _build(int p, int l, int r) {
        if (l == r) {
            tot[p] = source[r];
            pre[p] = max(0LL, source[r]);
            suf[p] = max(0LL, source[r]);
            mss[p] = max(0LL, source[r]);
        } else {
            int mid = (l + r) >> 1;
            _build(L(p), l, mid);
            _build(R(p), mid+1, r);
            _combine(p);
        }
    }

    void _combine(int p) {
        tot[p] = tot[L(p)] + tot[R(p)];
        pre[p] = max(tot[L(p)] + pre[R(p)], pre[L(p)]);
        suf[p] = max(tot[R(p)] + suf[L(p)], suf[R(p)]);
        mss[p] = max(suf[L(p)] + pre[R(p)], max(mss[L(p)], mss[R(p)]));
    }

    void _update(int p, int l, int r, int at, ll val) {
        if (l == r) {
            tot[p] = val;
            pre[p] = max(0LL, val);
            suf[p] = max(0LL, val);
            mss[p] = max(0LL, val);
        } else {
            int mid = (l+r) >> 1;
            if (at < mid+1)
                _update(L(p), l, mid, at, val);
            else
                _update(R(p), mid+1, r, at, val);
            _combine(p);
        }
    }

    // return tuple (max_subsequence_sum, total, prefix, suffix)
    llll _get_mss(int p, int l, int r, int ll, int rr) {
        if (l > rr || r < ll)
            return llll(0LL,0LL,0LL,0LL);
        if (ll <= l && r <= rr)
            return llll(mss[p], tot[p], pre[p], suf[p]);
        int mid = (l+r) >> 1;
        llll r_l = _get_mss(L(p), l, mid, ll, rr);
        llll r_r = _get_mss(R(p), mid+1, r, ll, rr);
        long long cur_mss = max(get<0>(r_l), max(get<0>(r_r), get<3>(r_l) + get<2>(r_r)));
        long long cur_tot = get<1>(r_l) + get<1>(r_r);
        long long cur_pre = max(get<2>(r_l), get<1>(r_l)+get<2>(r_r));
        long long cur_suf = max(get<3>(r_r), get<1>(r_r)+get<3>(r_l));
        return llll(cur_mss, cur_tot, cur_pre, cur_suf);
    }

};

int main() {
    vll test;
    test.push_back(1);
    test.push_back(24);
    test.push_back(4);
    test.push_back(-9);
    test.push_back(13);
    segment_tree seg(test);
    int l, r, t;
//    seg.update(2, -10);
    // test: t=0, query range; t=1, update value, t=2, quit
    while (scanf("%d %d %d", &t, &l, &r) && t!=2) {
        if (t == 0)
            printf("mss=%lld\n", seg.get_mss(l, r));
        else if (t == 1) {
            test[l] = r;
            seg.update(l, r);
            printf("updated as:");
            for (auto &n: test)
                printf(" %lld", n);
            puts("");
        }
    }
}

