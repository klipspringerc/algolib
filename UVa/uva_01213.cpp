//
// Created by KevinCui on 1/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <bitset>
using namespace std;

typedef long long int ll;

ll dp[220][1130][16]; // dp for prime index, remaining sum, and remaining numbers

vector<int> primes;
bitset<1130> sieve;
int num_p = 0;
int N = 1121;

ll count_sum(int idx, int n, int k) {
    if (k == 0 && n == 0)
        return 1;
    if (k <= 0)
        return 0;
    if (dp[idx][n][k] != -1)
        return dp[idx][n][k];
    ll count = 0l;
    for (int i = idx; i < num_p; i++) {
        if (n-primes[i] < 0)
            break;
        count += count_sum(i+1, n-primes[i], k-1);
    }
    dp[idx][n][k] = count;
    return count;
}

int main() {
    int n, k;
    memset(dp, -1, sizeof dp);
    sieve.set();
    sieve[0] = sieve[1] = 0;
    for (int i = 2; i < N; i++)
        if (sieve[i]) {
            primes.push_back(i);
            num_p++;
            for (int j = i * i; j < N; j += i) {
                sieve[j] = 0;
            }
        }

    while (scanf("%d %d", &n, &k) && n) {
        printf("%lld\n", count_sum(0, n, k));
    }
}