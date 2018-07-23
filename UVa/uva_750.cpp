//
// Created by KevinCui on 20/7/18.
//

/* 8 Queens Chess Problem */
#include <cstdlib>                       // we use the int version of 'abs'
#include <cstdio>
#include <cstring>
using namespace std;

int col[8], TC, a, b, lineCounter;            // ok to use global variables

bool place(int r, int c) {
    for (int prev = 0; prev < c; prev++)    // check previously placed queens
        if (col[prev] == r || (abs(col[prev] - r) == abs(prev - c)))
            return false;        // share same row or same diagonal -> infeasible
    return true;
}

void backtrack(int c) {
    if (c == 8) {         // candidate sol, (a, b) has 1 queen
        printf("%2d      %d", ++lineCounter, col[0] + 1);
        for (int j = 1; j < 8; j++) printf(" %d", col[j] + 1);
        printf("\n");
    }
    if (c == b) {
        if (place(a, b)) {
            col[c] = a;
            backtrack(c+1);
        }
    } else {
        for (int r = 0; r < 8; r++)                       // try all possible row
            if (place(r, c)) {          // if can place a queen at this col and row
                col[c] = r; backtrack(c + 1);      // put this queen here and recurse
            }
    }
}

int main() {
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d %d", &a, &b); a--; b--;         // switch to 0-based indexing
        memset(col, 0, sizeof col); lineCounter = 0;
        printf("SOLN       COLUMN\n");
        printf(" #      1 2 3 4 5 6 7 8\n\n");
        backtrack(0);           // generate all possible 8! candidate solutions
        if (TC) printf("\n");
    }
}
