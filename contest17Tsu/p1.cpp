//
// Created by KevinCui on 22/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>

typedef long long int ll;
ll dp[110];
//ll disks[5];

int L, K;

// l should be a black starting point
ll prop(int l) {
    if (l == L)
        return 1;
    if (dp[l] != -1)
        return dp[l];
    ll curCount = 0L;
    for (int i = l+2; i <= L; i++) {
        curCount += prop(i);
    }
    return (dp[l] = curCount);
}

int main() {

    scanf("%d %d", &L, &K);

    ll result = 0L;
    for (int i = 1; i <= L; i++) {
        memset(dp, -1, sizeof dp);
        dp[L] = 1;
        result += prop(i);
        printf("i %d prop %d\n", i, prop(i));
    }
//    for (int i = 1; i <= L; i++)
//        printf("%lld ", dp[i]);
    printf("%lld\n", result);

}