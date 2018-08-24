//
// Created by KevinCui on 17/8/18.
//

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 2048;
int sum[MAXN][MAXN];

int X, Y, N, Q;
int ans, ans_x, ans_y;


// left rotate the whole matrix by 45 degree to simplify reachable blocks to a rectangle
void rotate(int x, int y, int &tx, int &ty) {
    tx = x + y, ty = x - y + Y;
}

void update_max(int count, int x, int y) {
    if (count > ans) {
        ans = count;
        ans_x = x;
        ans_y = y;
    } else if (y <= ans_y) {
        if (y < ans_y) {
            ans = count;
            ans_x = x;
            ans_y = y;
        } else if (x < ans_x) {
            ans = count;
            ans_x = x;
            ans_y = y;
        }
    }
}


void query(int limit) {
    int tx, ty;
    int lx, rx, ly, ry, cnt;
    for (int j = 1; j <= Y; j++) {
        for (int i = 1; i <= X; i++) {
            rotate(i, j, tx, ty);
            lx = max(tx - limit, 1);
            ly = max(ty - limit, 1);
            rx = min(tx + limit, X + Y);
            ry = min(ty + limit, X + Y);
            cnt = sum[rx][ry] - sum[rx][ly-1] - sum[lx-1][ry] + sum[lx-1][ly-1];
            if (cnt >= ans) {
                update_max(cnt, i, j);
            }
        }
    }
    printf("%d (%d,%d)\n", ans, ans_x, ans_y);
}


int main() {

    int x, y, tx, ty, limit, cases = 0;
    while (scanf("%d %d %d %d", &X, &Y, &N, &Q) == 4 && X) {
        // rotate matrix, rotate 45 degree
//		for (int i = 1; i <= dx; i++) {
//			for (int j = 1; j <= dy; j++) {
//				printf("(%d %d) -> (%d %d)\n", i, j, i - j + dy, i + j);
//			}
//		}
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            rotate(x, y, tx, ty);
            sum[tx][ty]++;
        }

        for (int i = 1; i <= X + Y; i++) {
            for (int j = 1, s = 0; j <= X + Y; j++) {
                s += sum[i][j];
                sum[i][j] = sum[i-1][j] + s;
            }
        }

        printf("Case %d:\n", ++cases);
        for (int i = 0; i < Q; i++) {
            scanf("%d", &limit);
            ans = 0;
            ans_x = 1;
            ans_y = 1;
            query(limit);
        }
    }
    return 0;
}