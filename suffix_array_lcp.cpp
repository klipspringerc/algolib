//
// Created by Cui Shengping on 9/4/18.
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef pair<int, int> ii;
#define MAX_V 255  // max value for counting sort
#define MAX_N 1000 // max length of input string

int n; // length of input string
int RA[MAX_N], tempRA[MAX_N]; // rank array, provide the char value of given index position
int SA[MAX_N], tempSA[MAX_N]; // suffix array, use starting index to specify a suffix
int c[MAX_V]; // counting sort array
char T[MAX_N]; // input string

char P[MAX_N]; // pattern string
int m; // length of pattern string
int pre[MAX_N]; // used in LCP, record previous suffix in sorted SA
int PLCP[MAX_N]; // permuted LCP array
int LCP[MAX_N]; // LCP array by SA order, i.e. LCP[i] is equivalent to PLCP[SA[i]]


// revise counting sort
int* countingSortIntArray(int nums[], int length) {
    int sum, i;
    auto pos = (int*) malloc(sizeof(int) * MAX_V);
    auto result = (int *) malloc(sizeof(int) * length);
    memset(pos, 0, 255 * sizeof(int));
    memset(result, 0, length * sizeof(int));
    for (i = 0; i < length; i++) {
        pos[nums[i]]++;
    }
    for (i = sum = 0; i < MAX_V; i++) {
        int t = pos[i]; pos[i] = sum; sum += t;
    }
    for (i = 0; i < length; i++) {
        result[pos[nums[i]]++] = nums[i]; // stable sort
    }
    return result;
}

// counting sort for suffix array sorting
// sort basing on the k-th char
void countingSort(int k) {
    memset(c, 0, sizeof c);
    int i, sum;
    for (i = 0; i < n; i++)
        c[i+k < n ? RA[i+k]: 0]++;
    for (i = sum = 0; i < MAX_V; i++) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++) {
        tempSA[c[SA[i] + k < n? RA[SA[i]+k] : 0]++] = SA[i];
    }
    for (i = 0; i < n ; i++)
        SA[i] = tempSA[i];
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i;
    for (k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++)
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;
    }
}

// Find all occurence of pattern in mlog(n)
// return the range of matched suffices in SA.
// SA need to be sorted
ii stringMatching() {
    // find lower bound
    int l = 0, r = n-1, mid = l;
    while (l < r) {
        mid = (l + r) / 2;
        int res = strncmp(T+SA[mid], P, m);
        if (res >= 0)
            r = mid;
        else
            l = mid + 1;
    }
    if (strncmp(T+SA[l], P, m) != 0)
        return ii(-1, -1);
    ii range;
    range.first = l;
    // find upper bound
    // notice l = mid+1 when res = 0
    // this would help to find upperbound, but can lead to cases that l-1 is the actual upper bound
    l = 0, r = n-1, mid = l;
    while (l < r) {
        mid = (l + r) / 2;
        int res = strncmp(T+SA[mid], P, m);
        if (res > 0)
            r = mid;
        else
            l = mid + 1;
    }
    if (strncmp(T+SA[l], P, m) != 0) l--;
    range.second = l;
    return range;
}

// compute permuted LCP array in O(n)
// SA shall be sorted
void computeLCP() {
    int i, l;
    pre[SA[0]] = -1;
    for (i = 1; i < n; i++)
        pre[SA[i]] = SA[i-1];
    for (i = l = 0; i < n; i++) {
        if (pre[i] == -1) {
            PLCP[i] = 0;
            continue;
        }
        while(T[i+l] == T[pre[i]+l]) l++;
        PLCP[i] = l;
        l = max(l-1, 0);
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}


// Compute the LRS longest recurring substring
// LCP shall be computed
ii LRS() {
    int maxLCP = -1, idx = -1;
    for (int i = 1; i < n; i++) {
        if (LCP[i] > maxLCP) {
            maxLCP = LCP[i]; idx = i;
        }
    }
    return {maxLCP, idx};
}

// Compute LCS longest common substring of string A and B
// by combine the string to A$B#
// then run LCP

// return a suffix from the combined string belongs to which string
int owner(int idx) {
    return (idx < n-m-1) ? 1 : 2;
}

// compute the longest common substring using LCP array of the combined string
// the LCP of adjacent SA of different string would be the LCS
ii LCS() {
    int maxLCP = -1, idx = -1;
    for (int i = 1; i < n; i++) {
        if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP) {
            maxLCP = LCP[i];
            idx = i;
        }
    }
    return {maxLCP, idx};
}

void printSA() {
    printf("SA:\n");
    for (int i = 0; i < n; i++) {
        printf(" %s \n", T+SA[i]);
    }
}

void printSALCP() {
    printf("SA + LCP:\n");
    for (int i = 0; i < n; i++) {
        printf(" %s  LCP:%d\n", T+SA[i], LCP[i]);
    }
}


int main() {
//    int a[] = {4,4,3,2,2,2,1,1,1,1};
//    int* r = countingSortIntArray(a, (sizeof a)/4);
//    for (int i = 0; i < (sizeof a)/4; i++) {
//        printf("%d ", r[i]);
//    }
//    printf("\n");

    // string matching by SA
    strcpy(T, "GATAGCATGACATGCAGGATC");
    n = (int) strlen(T);
    T[n++] = '$';
    strcpy(P, "AT");
    m = (int) strlen(P);
    constructSA();
    printSA();
    ii range = stringMatching();
    for (int i = range.first; i <= range.second; i++)
        printf("string match '%s' at position %d-%d\n", P, SA[i], SA[i]+m);
    computeLCP();
    printSALCP();

    // longest recurring substring
    char result[MAX_N];
    ii lrs = LRS();
    strncpy(result, T+SA[lrs.second], size_t(lrs.first));
    printf("longest recurring substring: %s\n", result);

    // longest common substring
    strcat(T, "GATCAGGA");
    strcat(T, "#");
    printf("combined string: %s\n", T);
    n = (int) strlen(T);
    m = 8;
    // recompute
    constructSA();
    computeLCP();
    ii lcs = LCS();
    strncpy(result, T+SA[lcs.second], size_t(lcs.first));
    printf("longest common substring: %s\n", result);
    return 0;
}

