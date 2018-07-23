//
// current WA, no idea why LOL
// Created by KevinCui on 21/7/18.
//

#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

int h[110]; // converted number
char seq[110]; // input sequence
int n, pos; // str length, irregular position
char a, b;

// hash value specially for this problem
int get_hash(int k) {
    int hash = 0;
    for (int i = 0; i < k; i++) {
        hash = (hash << 1) + h[i];
    }
    return hash;
}

int update_hash(int hash, int i, int k) {
    if (i >= k && h[i-k])
        hash -= 1 << (k-1);
    return (hash << 1) + h[i];
}

int main() {
    while (gets(seq) != NULL) {
        n = strlen(seq);
        if (n <= 2) {
            printf("YES\n");
            continue;
        }
        pos = n;
        a = seq[0];
        b = seq[1];
        for (int i = 0; i < n; i++) {
            if (seq[i] == a)
                h[i] = 0;
            else if (a == b) {
                b = seq[i];
                h[i] = 1;
            }
            else if (seq[i] == b)
                h[i] = 1;
            else {
                pos = min(pos, i);
                h[i] = 1;  // assign it to 1, as now we are only concerned with any other violation before i, we can mess up the original pattern at i
            }
        }
        for (int k = 2; k < n/2+2; k++) {
            set<int> s;
            int hash = get_hash(k);
            s.insert(hash);
            for (int i = k; i < n; i++) {
                hash = update_hash(hash, i, k);
                s.insert(hash);
                if (s.size() > k+1) {
                    pos = min(pos, i);
                    break;
                }
            }
        }
        if (pos < n) {
            printf("NO:%d\n", pos+1);
        } else {
            printf("YES\n");
        }
    }
}