
#include<cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define maxn 110
#define M(a) memset(a,0,sizeof(a))
typedef long long int ll;

int main() {
    ll l, k;
    while (scanf("%lld %lld", &l, &k) == 2) {
        ll ans = 0, dp[maxn][4];
        M(dp);
        dp[0][1] = 1;
        for (int i = 1; i <= l; i++) {
            dp[i][2] = dp[i - 1][1];
            dp[i][1] = dp[i - 1][2];
            if (i >= k) dp[i][2] += dp[i - k][1];
        }
        for (int i = 1; i <= l; i++) {
            ans += dp[i][2];
        }
        printf("%lld\n", ans);
    }
    return 0;
}