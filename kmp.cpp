//
// Knuth–Morris–Pratt algorithm for string pattern matching
// The algorithm would remember the already matched portion of the pattern
// therefore would NOT always restart matching from the start of pattern
// useful for patterns containing many recurring prefix patterns
// O(n + m):  matching O(n) + pre-processing O(m)
// Created by Cui Shengping on 9/4/18.
//

#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_N 100
char T[MAX_N]; // text
char P[MAX_N]; // pattern
int b[MAX_N]; // back table
int n, m; // length of T and P


// in preprocess, it is all about identifying prefix that are also postfix
// e.g. abcabx, in this case 'ab' is both a prefix and postfix, so when pattern matching failed at 'x' idx 5, it could return
// to index 3 since the first 2 'ab' is a guaranteed match at this point.
//
void kmpPreprocess(){
    int i = 0, j = -1;
    b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        i++;
        j++;
        b[i] = j;
    }
}

void kmpSearch() {
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && P[j] != T[i]) j = b[j];
        i++; j++;
        if (j == m) {
            printf("P found at index %d in T\n", i-j);
            j = b[j];
        }
    }
}

int main() {
    strcpy(T, "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN");
    strcpy(P, "SEVENTY SEVEN");
    n = (int)strlen(T);
    m = (int)strlen(P);
    printf("%d \n", m);
    kmpPreprocess();
    printf("after pre-processing, back-off array: ");
    for (int i = 0; i < m; i++)
        printf("%d ", b[i]);
    printf("\n");
    kmpSearch();

    // for illustration of pre-processing
    strcpy(P,"ETETETW");
    memset(b, 0, MAX_N);
    kmpPreprocess();
    printf("after pre-processing, back-off array: ");
    for (int i = 0; i < 8; i++)
        printf("%d ", b[i]);
}
