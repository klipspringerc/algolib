//
// Created by KevinCui on 17/8/18.
// TLE

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;
int city[1010][1010];
vector <ii> shops;

int X, Y, N, Q;
int d;
int maxc, max_x, max_y;

void update_max(int count, int x, int y) {
    if (count > maxc) {
        maxc = count;
        max_x = x;
        max_y = y;
    } else if (y <= max_y) {
        if (y < max_y) {
            maxc = count;
            max_x = x;
            max_y = y;
        } else if (x < max_x) {
            maxc = count;
            max_x = x;
            max_y = y;
        }
    }
}

void addto(int x, int y) {
    int lx = max(1, x-d);
    int rx = min(X, x+d);
    int ly, ry;
    for (int i = lx; i <= rx; i++) {
        ly = max(1, y - (d - abs(i - x)));
        ry = min(Y, y + (d - abs(i - x)));
        for (int j = ly; j <= ry; j++) {
            city[i][j]++;
            if (city[i][j] >= maxc)
                update_max(city[i][j], i, j);
        }
    }
}

int main() {
    int x, y;
    int count = 1;
    while (scanf("%d %d %d %d", &X, &Y, &N, &Q) && (X+Y+N+Q)) {
        shops.clear();
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            shops.push_back(ii(x, y));
        }
        printf("Case %d:\n", count++);
        for (int i = 0; i < Q; i++) {
            memset(city, 0, sizeof city);
            maxc = 0;
            max_x = 1;
            max_y = 1;
            scanf("%d", &d);
            for (auto &shop: shops) {
                addto(shop.first, shop.second);
            }
            printf("%d (%d,%d)\n", maxc, max_x, max_y);
        }
    }
}