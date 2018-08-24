//
// Created by KevinCui on 16/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef long long int ll;

ll box[22][22][22]; // the rectangular garbage heap
ll zsum[22][22][22];
ll yzsum[22][22][22];

int T, X, Y, Z;
ll max_sum;

ll max(ll a, ll b) {
    return (a > b)? a : b;
}

int main() {
    scanf("%d", &T);
    ll p_sum;
    for (int t = 0; t < T; t++) {
        scanf("%d %d %d", &X, &Y, &Z);
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                p_sum = 0;
                for (int k = 0; k < Z; k++) {
                    scanf("%lld", &box[i][j][k]);
                    p_sum += box[i][j][k];
                    zsum[i][j][k] = p_sum;
                }
            }
            for (int k = 0; k < Z; k++) {
                yzsum[i][0][k] = zsum[i][0][k];
                for (int j = 1; j < Y; j++) {
                    yzsum[i][j][k] = yzsum[i][j-1][k] + zsum[i][j][k];
                }
            }
        }
        ll cur_sum = 0;
        max_sum = -4294967296ll;
        for (int j1 = 0; j1 < Y; j1++) {
            for (int k1 = 0; k1 < Z; k1++) {
                for (int j2 = j1; j2 < Y; j2++) {
                    for (int k2 = k1; k2 < Z; k2++) {
                        cur_sum = 0;
                        for (int i = 0; i < X; i++) {
                            ll curSlice = yzsum[i][j2][k2];
                            if (j1 != 0)
                                curSlice -= yzsum[i][j1-1][k2];
                            if (k1 != 0)
                                curSlice -= yzsum[i][j2][k1-1];
                            if (j1 != 0 && k1 != 0)
                                curSlice += yzsum[i][j1-1][k1-1];

                            if (cur_sum > 0)
                                cur_sum += curSlice;
                            else
                                cur_sum = curSlice;

                            max_sum = max(max_sum, cur_sum);
                        }
                    }
                }
            }
        }
        printf("%lld\n", max_sum);
        if (t != T-1)
            printf("\n");
    }

}