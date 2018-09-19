#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

// Using a sorted suffix array for string matching & computing LCP (longest common prefix array)
typedef pair<int, int> ii;

#define MAX_N 100010
char T[MAX_N];                   // the input string
int n;                                        // the length of input
int RA[MAX_N], tempRA[MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort

char P[MAX_N];                  // the pattern string (for string matching)
int m;                                      // the length of pattern string

int Phi[MAX_N];                      // for computing longest common prefix
int PLCP[MAX_N];
int LCP[MAX_N];  // LCP[i] stores the LCP between previous suffix T+SA[i-1] and current T+SA[i]

int b[MAX_N];

void countingSort(int k) {
    int i, sum, maxi = max(300, n);   // up to 255 ASCII chars or length of n
    memset(c, 0, sizeof c);
    for (i = 0; i < n; i++)
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)                     // update the suffix array SA
        SA[i] = tempSA[i];
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
    for (i = 0; i < n; i++) SA[i] = i;     // initial SA
    for (k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;             // start from rank r = 0
        for (i = 1; i < n; i++)                    // compare adjacent suffixes
            tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
                    (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;
    } }

void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1];    // remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++) {
        if (Phi[i] == -1) { PLCP[i] = 0; continue; }
        while (T[i + L] == T[Phi[i] + L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];   // put the permuted LCP to the correct position
}
int owner(int idx) { return (idx < n-m-1) ? 1 : 2; }
// longest common substring
ii LCS() {                 // returns a pair (the LCS length and its index)
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++)                         // O(n), start from i = 1
        if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
            maxLCP = LCP[i], idx = i;
    return ii(maxLCP, idx);
}

void kmpPreprocess() {
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        i++; j++;
        b[i] = j;
    } }

void kmpSearch() {
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j]) j = b[j];
        i++; j++;
        if (j == m) {
            printf("P is found at index %d in T\n", i - j); // record result
            j = b[j];
        } } }



int main() {
    //printf("Enter a string T below, we will compute its Suffix Array:\n");
    strcpy(T, "GATAGACA");
    n = (int)strlen(T);
    T[n++] = '$';
    // if '\n' is read, uncomment the next line
    //T[n-1] = '$'; T[n] = 0;

    constructSA();                                              // O(n log n)
    printf("\nThe Suffix Array of string T = '%s' is shown below (O(n log n) version):\n", T);
    printf("i\tSA[i]\tSuffix\n");
    for (int i = 0; i < n; i++) printf("%2d\t%2d\t%s\n", i, SA[i], T + SA[i]);

    computeLCP();                                                     // O(n)

    // LRS demo

//    strncpy(lrsans, T + SA[ans.second], ans.first);

    // stringMatching demo
    //printf("\nNow, enter a string P below, we will try to find P in T:\n");
//    strcpy(P, "A");
//    m = (int)strlen(P);
//    // if '\n' is read, uncomment the next line
//    //P[m-1] = 0; m--;
//    ii pos = stringMatching();
//    if (pos.first != -1 && pos.second != -1) {
//        printf("%s is found SA[%d..%d] of %s\n", P, pos.first, pos.second, T);
//        printf("They are:\n");
//        for (int i = pos.first; i <= pos.second; i++)
//            printf("  %s\n", T + SA[i]);
//    } else printf("%s is not found in %s\n", P, T);

    // LCS demo
    //printf("\nRemember, T = '%s'\nNow, enter another string P:\n", T);
    // T already has '$' at the back
    strcpy(P, "CATA");
    m = (int)strlen(P);
    // if '\n' is read, uncomment the next line
    //P[m-1] = 0; m--;
    strcat(T, P);                                                 // append P
    strcat(T, "#");                                    // add '$' at the back
    n = (int)strlen(T);                                           // update n

    // reconstruct SA of the combined strings
    char target[MAX_N];
    constructSA();                                              // O(n log n)
    computeLCP();                                                     // O(n)
    printf("\nThe LCP information of 'T+P' = '%s':\n", T);
    printf("i\tSA[i]\tLCP[i]\tOwner\tSuffix\n");
    for (int i = 0; i < n; i++) {
        printf("%2d\t%2d\t%2d\t%2d\t%s\n", i, SA[i], LCP[i], owner(SA[i]), T + SA[i]);
        strncpy(target, T+SA[i], LCP[i]);
        target[LCP[i]] = '\0';
        printf("%2d %s\n", i, target);
    }

    ii ans = LCS();         // find the longest common substring between T and P
    char lcsans[MAX_N];
    strncpy(lcsans, T + SA[ans.second], ans.first);
    printf("\nThe LCS is '%s' with length = %d\n", lcsans, ans.first);


    strcpy(T, "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN");
    strcpy(P, "SEVENTY SEVEN");
    n = (int)strlen(T);
    m = (int)strlen(P);
    kmpPreprocess();
    kmpSearch();
    return 0;
}
