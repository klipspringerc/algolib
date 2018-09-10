//
// Created by KevinCui on 6/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

// note that it is you and your N friend, so in total N+1 people
// dp for position, used quota and spent dollar
int dp[120][30][1110];

int p[110]; // price

int f[110]; //flavor

int N, x, T, K;
int quota, budget, tea;

// position, quota, dollar
int order(int pos,  int q, int d) {
    if (pos == K) {
        return 0;
    }
    if (dp[pos][q][d] != -1)
        return dp[pos][q][d];
    int maxf = order(pos+1, q, d);
    if (ceil(1.1L*(d + p[pos])) <= budget && q < quota) {
        maxf = max(maxf, f[pos] + order(pos+1, q+1, d+p[pos]));
        if (ceil(1.1L*(d + 2*p[pos])) <= budget && q < quota-1) {
            maxf = max(maxf, 2 * f[pos] + order(pos+1, q+2, d+2*p[pos]));
        }
    }
    return (dp[pos][q][d] = maxf);
}

int main() {
    int num, cur_sum;
    while (scanf("%d %d %d %d", &N, &x, &T, &K) && N) {
        memset(dp, -1, sizeof dp);
        for (int i = 0; i < K; i++) {
            scanf("%d", p+i);
            cur_sum = 0;
            for (int j = 0; j < N+1; j++) {
                scanf("%d", &num);
                cur_sum += num;
            }
            f[i] = cur_sum;
        }
        quota = 2 * (N+1);
        budget = x * (N+1);
        tea = T * (N+1);
        printf("%.2lf\n", double(order(0,0,tea))/double(N+1));

    }
}