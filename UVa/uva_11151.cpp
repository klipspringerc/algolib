//
// Created by KevinCui on 23/7/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

int T, n;
char str[1001];
int dp[1<<20];

int max(int a, int b) {
    return a > b? a : b;
}

int get_pal_len(int l, int r) {
    if (dp[(l<<10)+r] > 0)
        return dp[(l<<10)+r];
    int max_pal_len;
    if (l == r)
        max_pal_len = 1;
    else if (l + 1 == r && str[l] == str[r])
        max_pal_len = 2;
    else if (str[l] == str[r])
        max_pal_len = get_pal_len(l+1, r-1) + 2;
    else
        max_pal_len = max(get_pal_len(l+1, r), get_pal_len(l, r-1));
    dp[(l<<10)+r] = max_pal_len;
    return max_pal_len;
}

int main() {
    scanf("%d", &T);
    getc(stdin);
    while (T--) {
        memset(dp, 0, sizeof(dp));
        gets(str);
        n = strlen(str);
        if (n)
            printf("%d\n", get_pal_len(0,n-1));
        else
            printf("0\n");
    }
    return 0;
}