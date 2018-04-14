//
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
    kmpSearch();
}
