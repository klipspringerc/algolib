//
// Created by KevinCui on 15/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;


char cand[200][400];
vector<int> cand_l;
typedef long long int ll;
int cand_ptr;
int mod = 1000000007;
int N;
char T[210];
char temp[400];


bool checkP(char* p, int n) {
    int i = 0, j = n-1;
    while (i < j) {
        if (p[i] == p[j]) {
           j--;
            i++;
        } else
            return false;
    }
    return true;
}

int get_mid(int l, int r) {
    int k = (r - l) >> 2;
    return l + k -1;
}

bool checkSame(char * p1, char * p2, int n) {
    for (int i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return false;
    }
    return true;
}


ll pow_mod(ll a, ll p) {
    int n = mod;
    if (!p)
        return 1;
    ll ans = pow_mod(a, p/2);
    ans = ans * ans % n;
    if (p % 2)
        ans = ans * a % n;
    return ans;
}

int main() {
    scanf("%d", &N);
    getchar();
    gets(T);
//    puts(T);
    int l, r;
    ll count = 0L;
    bool rep;
    if (N % 2 == 0 && checkP(T, N)) {
        strncpy(cand[cand_ptr++], T+N/2, N/2);
        cand_l.push_back(N/2);
    }
    for (int k = N/2-1; k > 0; k--) {
        // check left
        l = 0;
        r = 0 + 2 * k;
        if (T[l+k-1] == T[l+k])
            if (checkP(T, 2*k)) {
                rep = false;
                for (int i = 0; i < cand_ptr; i++) {
                    for (int j = 0; j < k; j++) {
                        temp[j] = T[N-1-j];
                    }
                    temp[k] = '\0';
                    if (checkSame(cand[i], temp, cand_l[i])) {
                        rep = true;
                        break;
                    }
//                    if (checkSame(cand[i], T, k)) {
//                        rep = true;
//                        break;
//                    }
                }
                if (!rep) {
                    strncpy(cand[cand_ptr++], temp, k);
                    cand_l.push_back(k);
                }
            }
        l = N-2*k;
        r = N;
        if (T[l+k-1] == T[l+k])
            if (checkP(T, 2*k)) {
                rep = false;
                for (int i = 0; i < cand_ptr; i++) {
//                    for (int j = 0; j < k; j++) {
//                        temp[j] = T[N-1-j];
//                    }
//                    if (checkSame(cand[i], temp, k)) {
//                        rep = true;
//                        break;
//                    }
                    if (checkSame(cand[i], T+l, cand_l[i])) {
                        rep = true;
                        break;
                    }
                }
                if (!rep) {
                    strncpy(cand[cand_ptr++], T, k);
                    cand_l.push_back(k);
                }
            }

    }
    rep = false;
    for (int i = 0; i < cand_ptr; i++) {
        if (checkSame(cand[i], T, cand_l[i])) {
            rep = true;
            break;
        }
    }
    if (!rep)
        count++;
    for (int i = 0; i < N; i++) {
        temp[i] = T[N-1-i];
    }
    temp[N] = '\0';
    rep = false;
    for (int i = 0; i < cand_ptr; i++) {
        if (checkSame(cand[i], temp, cand_l[i])) {
            rep = true;
            break;
        }
    }
    if (!rep)
        count++;
    long long int prod;
    for (auto & curl : cand_l) {
        int p = N - curl;
        prod = pow_mod(26, p) % mod;
//        printf("adding %lld\n", prod);
        count += prod;
        count %= mod;

    }
    for (int i = 0; i < cand_ptr; i++) {
        puts(cand[i]);
    }
    printf("%lld\n", count);

}

