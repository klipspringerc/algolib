//
// Ancient messages
// Created by KevinCui on 8/8/18.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char graph[210][210];
char line[60];
bool mark[210][210];
char ans[100];
int H, W;
int j;
int white_count; // global var track number of white area inside a symbol

char hex[16][5] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
char symbol[6] = {'W','A','K','J','S','D'};
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void dfs_mark_w(int i, int j) {
    if (i < 0 || i > H+1 || j < 0 || j > W+1 || graph[i][j] == '1')
        return;
    mark[i][j] = true;
    for (int d = 0; d < 4; d++) {
        if (!mark[i+dr[d]][j+dc[d]])
            dfs_mark_w(i+dr[d], j+dc[d]);
    }
}

void dfs_mark_symbol(int i, int j) {
    mark[i][j] = true;
    for (int d = 0; d < 4; d++) {
        if (!mark[i+dr[d]][j+dc[d]]) {
            if (graph[i+dr[d]][j+dc[d]] == '0') {
                white_count++;
                dfs_mark_w(i+dr[d], j+dc[d]);
            } else {
                dfs_mark_symbol(i+dr[d], j+dc[d]);
            }
        }
    }
}


int main() {
    int no = 1;
    while (scanf("%d %d", &H, &W) && H+W) {
        memset(mark, 0, sizeof mark);
        W *= 4;
        getc(stdin);
        for (int i = 0; i < H+2; i++) {
            if (i == 0 || i == H+1) {
                for (int j = 0; j < W+2; j++)
                    graph[i][j]='0';
                graph[i][W+2] = '\0';
                continue;
            }
            gets(line);
            graph[i][0] = '0';
            graph[i][1] = '\0';
            for (auto &c : line) {
                if (c < 'a')
                    strcat(graph[i], hex[c-'0']);
                else
                    strcat(graph[i], hex[c-'a'+10]);
            }
            graph[i][W+1] = '0';
            graph[i][W+2] = '\0';
        }
        dfs_mark_w(0,0);
        int count = 0;
        for (int i = 0; i < H+2; i++) {
            for (int j = 0; j < W+2; j++) {
                if (!mark[i][j] && graph[i][j] == '1') {
                    white_count = 0;
                    dfs_mark_symbol(i, j);
                    ans[count++] = symbol[white_count];
                }
            }
        }
        ans[count] = '\0';
        sort(ans, ans+count);
        printf("Case %d: ", no);
        puts(ans);
        no++;
    }
    return 0;
}
