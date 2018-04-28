//
// RMQ Range Minimum Query
// For a given range, return the minimum value of the range
// Created by Cui Shengping on 28/4/18.
//

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define MAX_LOG_N 10

// RMQ with sparse table algorithm
// M[i][j] is an auxiliary array storing the index of the minimum value of the range [i , i+2^j-1],
// i is the starting position while 2^j is the length of the range.
class RMQST {
private:
    int A[MAX_N];
    int M[MAX_N][MAX_LOG_N];
public:
    // pre-processing
    RMQST(int a[], int n) {
        for (int i = 0; i < n; i++) {
            A[i] = a[i];
            M[i][0] = i;
        }
        // initialising from range length 1 to log N
        // for each range. the minimum is the smaller of the minimus of the 2 sub-range comprising this range
        // e.g. for range [0,3] (M[0][2]), the minimum is the smaller of range [0,1] (M[0][1]) and [2,3] (M[2][1])
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                if (a[M[i][j-1]] < a[M[i + (1 << (j-1))][j-1]])
                    M[i][j] = M[i][j-1];
                else
                    M[i][j] = M[i + (1<<(j-1))][j-1];
            }
        }
    }

    // for query, the idea is to find two overlapping range that fully covers [a,b]
    // first find k = log(b - a + 1), the the two range would be [a, a+2^k] (M[a][k]), [b-2^k+1, b] (M[b-2^k+1][k])
    int query(int a, int b) {
        auto k = int(floor(log(b-a+1) / log(2)));
        return A[M[a][k]] < A[M[b-(1<<k)+1][k]]? A[M[a][k]] : A[M[b-(1<<k)+1][k]];
    }
};

void sparseTable() {
    int a[10] = {1,5,3,23,64,2,54,11,3,0};
    auto st = RMQST(a, 10);
    printf("min for the range: %d\n", st.query(2,3));
}

int main() {
    sparseTable();
    return 0;
}

