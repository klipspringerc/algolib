//
// Created by KevinCui on 10/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

bool hit[1000];
int hof[15];
int stamp[15];
int N, S, M;
int max_cover, max_n, max_last, max_second_last;

// stamp index, stamp used, and current value
void prop(int pos, int s, int v) {
    if (s > S)
        return;
    hit[v] = true;
    for (int i = pos; i < M; i++) {
        prop(i, s+1, v+stamp[i]);
    }
}

void update_max(int new_max) {
    max_cover = new_max;
    max_n = M;
    max_last = stamp[M-1];
    if (M>1)
        max_second_last = stamp[M-2];
    for (int i = 0; i < M; i++)
        hof[i] = stamp[i];
}


int main() {
    while(scanf("%d", &S) && S) {
        scanf("%d", &N);
        max_cover = -1;
        max_second_last = 20000;
//        memset(high, -1, sizeof high);
        for (int n = 0; n < N; n++) {
            memset(hit, 0, sizeof hit);
            scanf("%d", &M);
            for (int i = 0; i < M; i++)
                scanf("%d", stamp + i);
            prop(0, 0, 0);
            int j = 1;
            while (hit[j]) j++;
            j--;
            if (j > max_cover) {
                update_max(j);
            } else if (j == max_cover) {
                if (M < max_n)
                    update_max(j);
                else if (M == max_n) {
                    if (stamp[M - 1] < max_last)
                        update_max(j);
                    else if (stamp[M - 1] == max_last && M > 1 && stamp[M - 1] < max_second_last)
                        update_max(j);
                }
            }
        }
        printf("max coverage =%4d :", max_cover);
        for (int i = 0; i < max_n; i++)
            printf("%3d", hof[i]);
        printf("\n");
    }
}