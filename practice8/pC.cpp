//
// Created by KevinCui on 16/10/18.
//

#include <cstdio>
#include <cstring>

int n, v;
bool d[380];

int main() {
    int cur_d = 0;
    int cur_ost = 0;
    memset(d, 0, sizeof d);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        d[v] = true;
    }
    int count = 0;
    for (int i = 1; i < 366; i++) {
        cur_d += cur_ost;
        if (d[i])
            cur_ost++;
        if (cur_d + cur_ost >= 20) {
            count++;
            cur_ost = 0;
            cur_d = 0;
        }
    }
    if (cur_ost > 0)
        count++;
    printf("%d\n", count);
}