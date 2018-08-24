#include <algorithm>
#include <cstdio>
#include <stack>
using namespace std;

#define MAX_N 100000

// Get the longest increasing sub-sequence for a given sequence
// L is an auxiliary array storing the current sub sequence.
// lis_end track the ending index (in the original array) of the current longest sub sequence.
// array P to track the previous index position (in original array) of the given index in candidate longest sub-sequences.
// array L_id track the index position (in original array) for a given index in the current longest sub sequence

void print_array(const char *s, int a[], int n) {
  for (int i = 0; i < n; ++i) {
    if (i) printf(", ");
    else printf("%s: [", s);
    printf("%d", a[i]);
  }
  printf("]\n");
}

void reconstruct_print(int end, int a[], int p[]) {
  int x = end;
  stack<int> s;
  for (; p[x] >= 0; x = p[x]) s.push(a[x]);
  printf("[%d", a[x]);
  for (; !s.empty(); s.pop()) printf(", %d", s.top());
  printf("]\n");
}

int main() {
  int n = 12, A[] = {-7, 10, 9, 2, 3, 8, 8, 1, 2, 2, 3, 4};
  int L[MAX_N], L_id[MAX_N], P[MAX_N];

  int lis = 0, lis_end = 0;
  for (int i = 0; i < n; ++i) {
    int pos = upper_bound(L, L + lis, A[i]) - L; // find the position to insert the current element
    L[pos] = A[i];
    L_id[pos] = i;
    P[i] = pos ? L_id[pos - 1] : -1; // update the index to the previous element, -1 marks the start of subsequence
    if (pos + 1 > lis) {
      lis = pos + 1; // update end position of current sub array
      lis_end = i; // update ending position of current longest sub array
    }

    printf("Considering element A[%d] = %d\n", i, A[i]);
    printf("LIS ending at A[%d] is of length %d: ", i, pos + 1);
    reconstruct_print(i, A, P);
    print_array("L is now", L, lis);
    printf("\n");
  }

  printf("Final LIS is of length %d: ", lis);
  reconstruct_print(lis_end, A, P);
  return 0;
}
