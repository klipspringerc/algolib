//
// Created by KevinCui on 7/8/18.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

int T, M, N;
char land[100][100];
char line[100];
bool visited[100][100];
int r, c, i, j;

int dr[] = {-1, 1, 0, 0, 1, 1,-1,-1};
int dc[] = { 0, 0,-1, 1, 1,-1, 1,-1};

int floodfill(int i, int j) {
    if (i == M || i < 0 || j == N || j < 0)
        return 0;
    if (land[i][j] == 'L')
        return 0;
    visited[i][j] = true;
    int ans = 1;
    for (int d = 0; d < 8; d++) {
        if (!visited[i+dr[d]][j+dc[d]])
            ans += floodfill(i+dr[d], j+dc[d]);
    }
    return ans;
}

int main() {
    scanf("%d", &T);
    getchar();
    getchar();
    for (int t = 0; t < T; t++) {
        M = 0;
        N = 0;
        while (gets(line)) {
            if (!strlen(line))
                break;
            if (line[0] == 'L' || line[0] == 'W') {
                strcpy(land[M++], line);
                if (!N)
                    N = strlen(line);
            } else {
                sscanf(line, "%d %d", &i, &j);
                memset(visited, 0, sizeof visited);
                printf("%d\n", floodfill(i-1, j-1));
            }
        }
        if (t != T-1) printf("\n");
    }
}
