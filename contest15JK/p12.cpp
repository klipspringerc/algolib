//
// Created by KevinCui on 1/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long int ll;
int T, N, M;
ll cur_array[60][60];
ll fsum = 0;
ll cur_gcd = 0;
int m[60];

ll gcd(ll a, ll b) {
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

ll get_gcd(ll a, ll b) {
    ll r = (a > b)? gcd(a,b): gcd(b,a);
    return r;
}



int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        fsum = 0;
        cur_gcd = 0;
        scanf("%d", &N);
        for (int n = 0; n < N; n++) {
            scanf("%d", &M);
            m[n] = M;
            for (int i = 0; i < M; i++) {
                scanf("%lld", &cur_array[n][i]);
            }
            fsum += cur_array[n][0];
        }
        cur_gcd = fsum;
        for (int n = 0; n < N; n++) {
//            sort(cur_array[n], cur_array[n]+m[n]);
            for (int i = 1; i < m[n]; i++) {
                if (cur_array[n][i] - cur_array[n][0] != 0)
                    cur_gcd = get_gcd(abs(cur_array[n][i] - cur_array[n][0]), cur_gcd);
            }
        }
        printf("Case #%d: %lld\n", t+1, cur_gcd);
    }
    return 0;
}