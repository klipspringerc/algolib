//
// Created by KevinCui on 20/7/18.
//

#include <cstdio>
#include <cstdlib>
using namespace std;

#define LS_BIT(S) (S & (-S))

// row: bitmask for occupied rows
// ld: bitmask for occupied left diagonal
// rd: bitmask for occupied right diagonal

int n, sol_count, ok, no = 0;
int bad[31];

void queen_backtrack(int c, int row, int ld, int rd) {
    if (c == n)
        sol_count++;
    else {
        int pos = ok & (~(bad[c] | row | ld | rd));
        while (pos) {
            int p = pos & -pos; // try first available position
            pos -= p;
            queen_backtrack(c+1, row|p, (ld|p)<<1, (rd|p)>>1); // note how blocked grids along diagonal moves
        }
    }
}


int main() {

    char row[31];
    while(true) {
        scanf("%d", &n);
        if (!n)
            break;
        sol_count = 0;
        ok = (1 << n) - 1;
//        char c;
        for (int i = 0; i < n; i++) {
            bad[i] = 0;
            scanf("%s", row);
            for (int j = 0; j < n; j++) {
                if (row[j] == '*') {
                    bad[i] |= 1 << j;
                }
            }
        }
        queen_backtrack(0, 0, 0, 0);
        printf("Case %d: %d\n", ++no, sol_count);

    }

}

