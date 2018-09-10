#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
int mmap[105][105], T, n, m, Ax, Ay, Bx, By, dis[105][105], sum = 0, path[105][105];
bool vis[105][105]; //if p is 0, use s1, else s2
struct node {
    int x, y;

    node(int a, int b) {
        x = a;
        y = b;
    }

    bool operator<(const node v) const {
        return dis[x][y] > dis[v.x][v.y];
    }
};

bool checkpath(int a, int b, int x, int y) // to expand x y
{
    if (path[a][b] < mmap[x][y]) // cur node max
    {
        if (dis[x][y] > dis[a][b] + path[a][b]) {
            dis[x][y] = dis[a][b] + path[a][b];
            return 1;
        }
    } else //path have max value
    {
        if (dis[x][y] > dis[a][b] + mmap[x][y]) {
            dis[x][y] = dis[a][b] + mmap[x][y];
            return 1;
        }
    }
    return 0;
}

int dji() {
    priority_queue<node> q;
    q.push(node(Ax, Ay));
    vis[Ax][Ay] = 1;
    dis[Ax][Ay] = 0;
    path[Ax][Ay] = 0;

    while (!q.empty()) {
        node u = q.top();
        q.pop();
        int x = u.x, y = u.y;
        //printf("%d %d\n",x,y);

        if (x + 1 < n && !vis[x + 1][y] && mmap[x + 1][y] != -1 && checkpath(x, y, x + 1, y)) {
            //printf("x1 %d\n", dis[x+1][y]);
            path[x + 1][y] = max(path[x][y], mmap[x + 1][y]);
            q.push(node(x + 1, y));
            vis[x + 1][y] = 1;

        }
        if (x - 1 >= 0 && !vis[x - 1][y] && mmap[x - 1][y] != -1 && checkpath(x, y, x - 1, y)) {
            //printf("x-1 %d\n", dis[x-1][y]);
            path[x - 1][y] = max(path[x][y], mmap[x - 1][y]);
            q.push(node(x - 1, y));
            vis[x - 1][y] = 1;

        }
        if (y + 1 < m && !vis[x][y + 1] && mmap[x][y + 1] != -1 && checkpath(x, y, x, y + 1)) {
            // printf("y1 %d\n", dis[x][y+1]);
            path[x][y + 1] = max(path[x][y], mmap[x][y + 1]);
            q.push(node(x, y + 1));
            vis[x][y + 1] = 1;

        }
        if (y - 1 >= 0 && !vis[x][y - 1] && mmap[x][y - 1] != -1 && checkpath(x, y, x, y - 1)) {
            //printf("y-1 %d\n", dis[x][y-1]);
            path[x][y - 1] = max(path[x][y], mmap[x][y - 1]);
            q.push(node(x, y - 1));
            vis[x][y - 1] = 1;
        }
    }
}

void init() {
    memset(vis, 0, sizeof(vis));
    memset(mmap, 0, sizeof(mmap));
    memset(dis, 0x3f, sizeof(dis));
    memset(path, 0, sizeof(path));
    sum = 0;
}

int main() {
    int i, j, k;
    char c;
    scanf("%d", &T);
    for (int kkk = 1; kkk <= T; kkk++) {
        init();
        scanf("%d%d", &n, &m);
        for (i = 0; i < n; i++) {
            scanf("%c", &c);//whitespace
            for (j = 0; j < m; j++) {
                scanf("%c", &c);
                if (c == 'A') {
                    Ax = i;
                    Ay = j;
                    dis[Ax][Ay] = 0;
                } else if (c == 'B') {
                    Bx = i;
                    By = j;
                } else {
                    mmap[i][j] = c - 48;
                    sum += mmap[i][j];
                    if (mmap[i][j] == 0) mmap[i][j] = -1;
                }
            }
        }
        dji();
        if (!vis[Bx][By])
            printf("Case #%d: 0\n", kkk);
        else
            printf("Case #%d: %d\n", kkk, sum - dis[Bx][By]);
    }

}