//
// Created by KevinCui on 21/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

int T, X, Y;
typedef long long int ll;
ll K, min_cost;
int max_size;
ll p_sum[110][110];


int main() {
    scanf("%d", &T);
    ll p, cur_sum;
    for (int t = 0; t < T; t++) {
        scanf("%d %d %lld", &X, &Y, &K);
        for (int i = 0; i < X; i++) {
            cur_sum = 0;
            for (int j = 0; j < Y; j++) {
                scanf("%lld", &p);
                cur_sum += p;
                p_sum[i][j] = (i > 0) ? p_sum[i-1][j] + cur_sum : cur_sum;
            }
        }
        min_cost = 0;
        max_size = 0;
        for (int i1=0; i1<X; i1++)
            for (int j1=0; j1<Y; j1++)
                for (int i2=i1; i2<X; i2++)
                    for (int j2=j1; j2<Y; j2++) {
                        cur_sum = p_sum[i2][j2];
                        if (j1 > 0)
                            cur_sum -= p_sum[i2][j1-1];
                        if (i1 > 0)
                            cur_sum -= p_sum[i1-1][j2];
                        if (i1 > 0 && j1 > 0)
                            cur_sum += p_sum[i1-1][j1-1];
//                        if (cur_sum > K)
//                            break;
                        in  t cur_size = (i2-i1+1) * (j2-j1+1);
                        if (cur_size > max_size && cur_sum <= K) {
                            min_cost = cur_sum;
                            max_size = cur_size;
                        }
                        if (cur_size == max_size && cur_sum < min_cost) {
                            min_cost = cur_sum;
                            max_size = cur_size;
                        }
                    }
        printf("Case #%d: %d %lld\n", t+1, max_size, min_cost);
    }


}