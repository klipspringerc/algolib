//
// Created by Cui Shengping on 24/3/18.
//

#include <bitset>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;

ll sieve_size;
bitset <10000000> bs;
vi primes;

void sieve(ll upperbound) {
    sieve_size = upperbound+1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= sieve_size; i++) if (bs[i]) {
        for (ll j = i*i; j <= sieve_size; j += i) bs[j] = 0;
        primes.push_back((int)i);
    }
}

bool is_prime(ll n) {
    if (n < sieve_size) return bs[n];
    for (int i = 0; i < primes.size(); i++)
        if (n % primes[i] == 0) return false;
    return true;
}

vi prime_factors(ll n) {
    vi factors;
    int p_idx = 0, pf = primes[p_idx];
    while (n != 1 && pf * pf <= n) {
        while (n % pf == 0) { n /= pf; factors.push_back(pf); }
        pf = primes[++p_idx];
    }
    if (n != 1)
        factors.push_back(n);
    return factors;
}

int num_divs(ll n) {
    int count = 1, p_idx = 0, pf = primes[p_idx], power = 0;
    while (n != 1 && pf*pf <= n) {
        power = 0;
        while (n % pf == 0) { n /= pf; power++; }
        count *= power+1;
        pf = primes[++p_idx];
    }
    if (n != 1) count *= 2;
    return count;
}

int main() {
    sieve(10000L);
//    printf("Primes within 10000");
//    for (auto it=primes.begin(); it != primes.end(); it++) printf("%d ", *it);
    ll n = 144;
    printf("For number %d \n", n);
    vi pfs = prime_factors(n);
    printf("prime factos: ");
    for (auto it=pfs.begin(); it != pfs.end(); it++) printf("%d ", *it);
    printf("\n");
    printf("number of dividents: %d \n", num_divs(n));
    return 0;
}


