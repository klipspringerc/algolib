//
// Created by KevinCui on 17/10/18.
//

//#include <bits/stdc++.h>
#include <vector>
#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define REP(i, n) FOR(i, 0, (n) - 1)
#define ROF(i, a, b) for (int i = (a); i >= (b); i--)
#define pb push_back
using namespace std;

const int maxn = 213;
vector<int> ans;
int n, a[maxn], tmp[maxn];

int pos(int now) {
    REP(i, n) if (now == a[i]) return i;
}

void mv(int v) {
    int j = 0;
    FOR(i, v, n - 1) tmp[j++] = a[i];
    ROF(i, v - 1, 0) tmp[j++] = a[i];
    memcpy(a, tmp, sizeof(a));
    ans.pb(v);
}

int main() {
    scanf("%d", &n);
    REP(i, n) scanf("%d", a + i);
    while (true) {
        int i = pos(1), e = 1;
        // REP(i, n) cout << a[i] << ' ';
        // cout << endl;
        while (i + 1 < n && a[i + 1] == e + 1)
            i++, e++;
        if (e == n) break;
        mv(n);
        if (pos(e)) mv(pos(e));
        mv(pos(1) + 1);
        mv(pos(e + 1) + 1);
    }
    printf("%d\n", int(ans.size()));
    for (int it : ans) printf("%d\n", it);
    return 0;
}