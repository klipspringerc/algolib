//
// Created by KevinCui on 22/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int ll;

int dmin[100010];
int dmax[100010];
int a[100010];


int N;

int main() {
    while (scanf("%d", &N) == 1) {
        for (int i = 0, cur_max = 1<<31; i < N; i++) {
            scanf("%d", a+i);
            cur_max = max(cur_max, a[i]);
            dmax[i] = cur_max;
        }
        for (int i = N-1, cur_min = (1<<31)-1; i > -1; i--) {
            cur_min = min(cur_min, a[i]);
            dmin[i] = cur_min;
        }
        int count  = 0;
        if (a[0] < dmin[1])
            count++;
        if (a[N-1] >= dmax[N-2])
            count++;
        for (int i = 1; i < N-1; i++)
            if (dmax[i-1] <= a[i] && dmin[i+1] > a[i])
                count++;
        printf("%d\n", count);
    }


}