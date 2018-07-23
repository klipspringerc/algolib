//
// Created by KevinCui on 21/7/18.
//

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <set>
using namespace std;
typedef unsigned long long ull;
const int maxn = 100 + 5;
const ull hashBase = 100007;
char str[maxn]; ull powers[maxn], h[maxn]; int n;

void process() {
    h[n] = 0;
    for(int i = n - 1; i >= 0; --i) h[i] = h[i + 1] * hashBase + str[i];
}

inline ull getHash(int l, int r) {
    return h[l] - h[r] * powers[r - l];
}

int main() {
    powers[0] = 1;
    for(int i = 1; i < maxn; ++i) powers[i] = powers[i - 1] * hashBase;
    while(gets(str) != NULL) {
        int pos = maxn + 1;
        n = strlen(str);
        if (n <= 2) {
            puts("YES");
            continue;
        }
        process();
        for(int k = 1; k <= n/2+1; ++k) {
            set<ull> s;
            for(int i = 0; i + k - 1 < n; ++i) {
                s.insert(getHash(i, i + k));
                if(s.size() > k + 1) {
                    pos = min(pos, i + k);
                    n=pos; // update array length, this lead to 0ms solution
                    break;
                }
            }
        }
        if(pos == maxn + 1) puts("YES");
        else printf("NO:%d\n", pos);
    }
    return 0;
}