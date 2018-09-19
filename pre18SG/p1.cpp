//
// Created by KevinCui on 15/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
int N;
int A=2, I=2, P=1, S=2, G=1, C=2;
int cA, cI, cP, cS, cG, cC;
char m[1000][1000];
vii starts;

char target[15];

int dr[8] = {-1, -1, 1, 1, 2, 2, -2, -2};
int dc[8] = {2, -2, 2, -2, 1, -1, 1, -1};


bool check(int p, int x, int y) {
    if (p == 10)
        return true;
    if (x < 0 || x >= N || y < 0 || y >= N)
        return false;
    int nx, ny;
    if (target[p] == m[x][y]) {
        for (int i = 0; i < 8; i++) {
            nx = x + dr[i];
            ny = y + dc[i];
            if (check(p+1, nx, ny))
                return true;
        }
    } else {
        return false;
    }
    return false;
}

int main() {
    scanf("%d", &N);
    strcpy(target, "ICPCASIASG");
    getchar();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%c", &(m[i][j]));
            if (m[i][j] == 'A')
                cA++;
            else if (m[i][j] == 'I') {
                starts.push_back(ii(i, j));
                cI++;
            }
            else if (m[i][j] == 'S')
                cS++;
            else if (m[i][j] == 'P')
                cP++;
            else if (m[i][j] == 'G')
                cG++;
            else if (m[i][j] == 'C')
                cC++;
        }
    }
//    if (cA < A || cI < I || cP < P || cS < S || cG < G || cC < C) {
//        printf("NO\n");
//        return 0;

        for (auto & pi : starts) {
            if (check(0, pi.first, pi.second)) {
                printf("YES\n");
                return 0;
            }
        }

    printf("NO\n");
    return 0;

}
