//
// Created by KevinCui on 13/8/18.
//

#include <cstdio>
#include <cstring>

int mem[110][110]; // dp on N, K

int N,K;

int main() {

    memset(mem, 0, sizeof mem);

    // only one way when k=1
    for (int n = 0; n <= 100; n++)
        mem[n][1] = 1;

    // bottom-up
    for (int k = 2; k <= 100; k++)
        for (int n = 0; n <= 100; n++)
            for (int addon=0; addon <= 100-n; addon++) {
                mem[n + addon][k] += mem[n][k - 1];
                mem[n + addon][k] %= 1000000;
            }

    while (scanf("%d %d", &N, &K) && (N+K)) {
        printf("%d\n", mem[N][K]);
    }
    return 0;
}