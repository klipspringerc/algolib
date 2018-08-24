//
// Created by KevinCui on 22/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int lis[2010];
int lds[2010];
int cars[2010];
int lis_size;
int lds_size;

int T, N;
int pos, max_size;

bool comp_less(int a, int b) {
    return a > b;
}

int main() {
    scanf("%d", &T);

    for (int t=0; t < T; t++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%d", cars+i);
        max_size = 0;
        for (int i = 0; i < N; i++) {
            memset(lis, 0, sizeof lis);
            memset(lds, 0, sizeof lds);
            lis_size = 0;
            lds_size = 0;
            for (int j = i+1; j < N; j++) {
                if (cars[j] > cars[i]) {
                    pos = upper_bound(lis, lis+lis_size, cars[j]) - lis;
                    lis[pos] = cars[j];
                    if (pos == lis_size)
                        lis_size++;
                }
                if (cars[j] < cars[i]) {
                pos = upper_bound(lds, lds+lds_size, cars[j], comp_less) - lds;
                lds[pos] = cars[j];
                if (pos == lds_size)
                    lds_size++;
                }
            }
            max_size = max(max_size, (lis_size+lds_size+1));
        }
        printf("%d\n", max_size);
    }
    return 0;
}