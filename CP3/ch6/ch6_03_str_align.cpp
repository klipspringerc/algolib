#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

// dynamic programming with a score matrix
// opt to obtain the best matching sequence from two sequences
// used for genetic analysis dealing with tansformation of DNA sequence
// transformation can be: an element is inserted to a sequence, or an element is deleted from a sequence
// for each matrix tile[i,j], the score is determined by the max of :
// [i-1,j-1] - continue matching the sequence
// [i][j-1] - consider an element as been inserted into the seq in i direction that result in seq in j direction
// [i-1][j] - consider an element is deleted from the seq in i that result to the seq in j 
// the score penalty for insertion, deletion and match can be chosen arbitrarily 

int main() {
  char A[20] = "ACAATCC", B[20] = "AGCATGC";
  int n = (int)strlen(A), m = (int)strlen(B);
  int i, j, table[20][20]; // Needleman Wunsnch's algorithm

  memset(table, 0, sizeof table);
  // insert/delete = -1 point
  for (i = 1; i <= n; i++)
    table[i][0] = i * -1;
  for (j = 1; j <= m; j++)
    table[0][j] = j * -1;

  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++) {
      // match = 2 points, mismatch = -1 point
      table[i][j] = table[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 2 : -1); // cost for match or mismatches
      // insert/delete = -1 point
      table[i][j] = max(table[i][j], table[i - 1][j] - 1); // delete
      table[i][j] = max(table[i][j], table[i][j - 1] - 1); // insert
    }

  printf("DP table:\n");
  for (i = 0; i <= n; i++) {
    for (j = 0; j <= m; j++)
      printf("%3d", table[i][j]);
    printf("\n");
  }
  printf("Maximum Alignment Score: %d\n", table[n][m]);

  return 0;
}
