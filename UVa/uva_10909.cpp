//
// the lucky number problem
// practice using BIT to find k-th element
// BIT's index would be the values, its elements bit[i] would be number of values before i
// Created by KevinCui on 23/7/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_N 2000001
#define LS_ONE(S) (S & (-S))

int bit[MAX_N], rm_buffer[MAX_N], lucky[MAX_N];
bool is_lucky[MAX_N];

// change the element frequency of the tree
// adjust(n, 1), add number n into tree
// adjust(n, -1), remove number n from tree
void adjust(int n, int op) {
    for (; n < MAX_N; n+=LS_ONE(n)) bit[n] += op;
}

// find the k-th element
// note the back-off when sum == k. this is because when sum==k,
// the ans may not be the actual k-th value due to property of BIT (bit[ans] might be some parent node of target)
// we go to find sum == k-1 instead, then return ans+1
// for example, if bit[4]=4 and bit[5]=bit[6]=1, bit[7]=0, bit[8]=5,then find(5) may encounter ans=8 and ans=6 when sum=k.
// so we back-off, find bit[4]=4 first, then return 4+1=5, which is the correct answer.
// or if bit[5]=0 bit[6]=1 and others unchanged, we would find bit[4]=4, then bit[5]=0, then return 5+1=6, which is the correct answer.
int find_kth(int k) {
    int ans = 0, sum = 0;
    for (int i = 20; i >= 0; i--) {
        ans += (1 << i);
        if (ans > MAX_N || sum + bit[ans] >= k) {
            ans -= (1 << i);
        } else {
            sum += bit[ans];
        }
    }
    return ans+1;
}

void test_bit_kth() {
    memset(bit, 0, MAX_N * sizeof(int));
    for (int i = 1; i < 20; i++)
        adjust(i, 1);
    printf("\nfind 5th: %d\n", find_kth(5));
    adjust(4,-1);
    printf("\nfind 5th: %d\n", find_kth(5));
    adjust(9, -1);
    printf("\nfind 5th: %d\n", find_kth(5));
    printf("\nfind 10th: %d\n", find_kth(10));
}


int main() {
    for (int i = 1; i < MAX_N; i+=2) {
        adjust(i, 1);
    }
    int total = MAX_N / 2, tmp=0;
    for (int i = 2; ; i++) {
        tmp = find_kth(i);
        if (tmp > total)
            break;
        for (int j = tmp; j < total; j+=tmp) {
            rm_buffer[j] = find_kth(j);
        }
        for (int j = tmp; j < total; j+=tmp) {
            adjust(rm_buffer[j], -1);
        }
        total -= total/tmp; // remove the deleted numbers from total count
    }
    for (int i = 1; i < total; i++) {
        lucky[i] = find_kth(i);
        is_lucky[lucky[i]] = true;
    }
    int n;
    bool found;
    while (scanf("%d", &n) == 1) {
        int pos = upper_bound(lucky+1, lucky+total, n/2) - lucky;
        found = false;
        if (n % 2 == 0) {
            for (int i = pos-1; i >= 1; i--) {
                if (is_lucky[n-lucky[i]]) {
                    printf("%d is the sum of %d and %d.\n", n, lucky[i], n - lucky[i]);
                    found = true;
                    break;
                }
            }
        }
        if (! found)
            printf("%d is not the sum of two luckies!\n", n);
    }
    return 0;
}

