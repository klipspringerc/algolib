//
// Created by KevinCui on 17/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int num, ans=0, sum=0;
char sep;

int main() {
    while (scanf("%d", &num) == 1) {
        scanf("%c", &sep);
        sum += num;
        ans = max(ans, sum);
        if (sum < 0)
            sum = 0;
        if (sep == '\n') {
            printf("%d\n", ans);
            sum = 0;
            ans = 0 ;
        }
    }
}