//
// 17 Asia Daejeon
// Created by KevinCui on 13/9/18.
//

#include <cstdio>
#include <cstdlib>

int nums[1000010];

int mins, mink, minp;
int N;


int main() {
    scanf("%d", &N);
        nums[0] = -1;
        for (int i = 1; i <= N; i++)
            scanf("%d", nums + i);
        mins = 100000000;
        int ptr2 = N;
        int ptr1 = N - 1;
        do {
            while (ptr1 > 0 && nums[ptr2] != nums[ptr1]) {
                ptr1--;
            }
            while (nums[ptr1] == nums[ptr2]) {
                ptr1--;
                ptr2--;
            }
            if (ptr2 < mins) {
                mins = ptr2;
                minp = ptr2 - ptr1;
                mink = mins - minp;
            }
            ptr2 = N;
        } while (ptr1 > 0);
        printf("%d %d\n", mink, minp);

    return 0;
}