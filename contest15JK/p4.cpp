//
// Created by KevinCui on 1/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cstring>

using namespace std;

bitset<1150> s;
vector <int> primes;
vector <int> comp;

int N=1150;

int nump;
int numc;
int T;
char input[40];

int main() {
    s.set();
    s[0] = s[1] = 0;
    for (int i = 2; i < N; i++) {
        if (s[i]) {
            primes.push_back(i);
            nump++;
        }
        for (int j = i*i; j < N; j+=i) {
            s[j] = 0;
        }
    }
//    for (auto &p : primes)
//        printf("%d ", p);
//    printf("\n");
//    for (auto &p : comp)
//        printf("%d ", p);
//    printf("\n");
    for (int i = 4; i < 500; i++) {
        if (s[i] == 0) {
            comp.push_back(i);
            numc++;
        }

    }

    scanf("%d", &T);
    getchar();
    for (int t = 0; t < T; t++) {
        int pos = 0;
        int count_p = 0;
        int count_c = 0;
        gets(input);
        int l = strlen(input);
        for (int i = 0; i < l; i++) {
            int num = input[i];
//            printf("%d ", num);
            for (int j = 7; j > -1; j--) {
                if (num & (1 << j)) {
                    printf("%d", primes[count_p++]);
                } else {
                    printf("%d", comp[count_c++]);
                }
                if (i == l-1 && j == 0)
                    printf("\n");
                else
                    printf(",");
            }
        }
    }
}

