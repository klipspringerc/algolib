//
// Created by KevinCui on 22/7/18.
//


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

int T, N, M, K;
typedef unsigned short ui;
ui nums[1000001] = {1,2,3};
int ks[101]; // track key number frequency
int count;

int min(int a, int b) {
    return (a < b)? a : b;
}

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        memset(ks, 0, 101 * sizeof(int));
        count = 0;
        scanf("%d %d %d", &N, &M, &K);
        for (int i = 3; i < N; i++) {
            nums[i] = (nums[i-1] + nums[i-2] + nums[i-3]) % M + 1;
        }
        int r = 0, l = 0, len = N+1;
        while (r < N) {
            while (count < K && r < N) {
                if (1 <= nums[r] && nums[r] <= K) {
                    if (ks[nums[r]] == 0)
                        count++;
                    ks[nums[r]]++;
                }
                r++;
            }
            if (r == N && count != K) {
                break;
            }
            while (true) {
                if (1 <= nums[l] && nums[l] <= K) {
                    ks[nums[l]]--;
                    if (ks[nums[l]] == 0) {
                        count--;
                        len = min(len, r-l);
                        l++;
                        break;
                    }
                }
                l++;
            }
        }
        if (len == N+1)
            printf("Case %d: sequence nai\n", t+1);
        else
            printf("Case %d: %d\n", t+1, len);
    }
}