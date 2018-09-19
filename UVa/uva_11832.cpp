//
// Created by KevinCui on 10/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
// dp on pos, value
short dp[45][56000];
int c[45];
int a[45];
char re[] = {' ','+', '-', '?'};
int N, F;


// state machine to track result
// op = 0 -> '+', op = 1 -> '-'
void update(int pos, int op) {
    if (c[pos] == 0 && op == 0)
        c[pos] = 1;
    else if (c[pos] == 1 && op == 1)
        c[pos] = 3;
    else if (c[pos] == 0 && op == 1)
        c[pos] = 2;
    else if (c[pos] == 2 && op == 0)
        c[pos] = 3;
}


bool prop(int pos, int v) {
    if (pos == N)
        return v == F;
    if (v < 0 || v > 56000)
        return false;
    if (dp[pos][v] != -1)
        return dp[pos][v] == 1;
    bool addi = prop(pos+1, v+a[pos]);
    bool minu = prop(pos+1, v-a[pos]);
    if (addi)
        update(pos, 0);
    if (minu)
        update(pos, 1);
    return (dp[pos][v] = addi || minu) == 1;
}


int main() {
    while (scanf("%d %d", &N, &F) && N) {
        F += 28000;
        memset(dp, -1, sizeof dp);
        memset(c, 0, sizeof c);
        for (int i = 0; i < N; i++)
            scanf("%d", a+i);
        if (!prop(0, 28000)) {
            printf("*\n");
        }
        else {
            for (int i = 0; i < N; i++)
                printf("%c", re[c[i]]);
            printf("\n");
        }
    }
}



