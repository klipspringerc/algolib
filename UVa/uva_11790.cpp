//
// Created by KevinCui on 22/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int wi[2000];
int wd[2000];

int w[2000];
int h[2000];

int T, N;
int maxI;
int maxD;

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &N);
        memset(wi, 0, sizeof wi);
        memset(wd, 0, sizeof wd);
        for (int i = 0; i < N; i++) {
            scanf("%d", h+i);
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", w+i);
        }
        maxI = 0;
        maxD = 0;
        for (int i = 0; i < N; i++) {
            wi[i] = wd[i] = w[i];
            for (int j = 0; j < i; j++) {
                if (h[j] < h[i])
                    wi[i] = max(wi[i], wi[j] + w[i]);
                if (h[j] > h[i])
                    wd[i] = max(wd[i], wd[j] + w[i]);
            }
            maxI = max(maxI, wi[i]);
            maxD = max(maxD, wd[i]);
        }
        if (maxI >= maxD)
            printf("Case %d. Increasing (%d). Decreasing (%d).\n", t+1, maxI, maxD);
        else
            printf("Case %d. Decreasing (%d). Increasing (%d).\n", t+1, maxD, maxI);
    }
}