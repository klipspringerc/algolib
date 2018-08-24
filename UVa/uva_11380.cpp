//
// Created by KevinCui on 14/8/18.
//

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef vector<int> vi;

#define S 1804
#define T 1805


int res[1810][1810];
int dist[1810];
vi adj[1810];
char map[35][35];

int dx[4] = {1, -1,  0, 0};
int dy[4] = {0,  0, -1, 1};

int X, Y, P;

bool bfs() {
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    queue<int> q; q.push(S);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &u: adj[v]) {
            if (dist[u] == -1 && res[v][u]) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return (dist[T] != -1);
}

int dfs(int v, int minFlow) {
    if (v == T)
        return minFlow;
    for (auto &u: adj[v]) {
        if (dist[u] == dist[v]+1 && res[v][u]) {
            int flow = dfs(u, min(res[v][u], minFlow));
            if (flow) {
                res[v][u] -= flow;
                res[u][v] += flow;
                return flow;
            }
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    int flow;
    while (bfs()) {
        while ((flow = dfs(S, 1000000000)))
            ans += flow;
    }
    return ans;
}

int transNode(int i, int j) {
    return i * Y + j;
}

void addEdge(int v, int u, int cap) {
    adj[v].push_back(u);
    res[v][u] = cap;
}

int main() {
    while (scanf("%d %d %d", &X, &Y, &P) == 3) {
        getc(stdin);
        for (int i = 0; i < 1800; i++)
            adj[i].clear();
        memset(res, 0, sizeof res);
        for (int i = 0; i < X; i++) gets(map[i]);
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++) {
                // node no. = i*Y+j
                // for split node, add 900
                // only connect outgoing edges
                char cur = map[i][j];
                if (cur == '~')
                    continue;
                bool split = (cur == '.') || (cur == '*');
                int v = transNode(i, j);
                // vertex capacity for people and float ice
                int v_s = v+900;
                if (split) {
                    adj[v].push_back(v_s);
                    adj[v_s].push_back(v);
                    res[v][v_s] = 1;
                }
                // handle special connection for people
                if (cur == '*') {
                    addEdge(S, v, 1);
                    adj[v].push_back(S);
                }
                // handle special connection for wood
                if (cur == '#') {
                    addEdge(v, T, P);
                    adj[T].push_back(v);
                }
                int u;
                char uc;
                // add outgoing connection to 4 surrounding tile
                for (int d = 0; d < 4; d++) {
                    int x = i+dx[d];
                    int y = j+dy[d];
                    if (x >= 0 && x < X && y >= 0 && y < Y) {
                        uc = map[x][y];
                        if (uc == '~')
                            continue;
                        u = transNode(x, y);

                        // add outgoing edges (res>0)
                        if (split) {
                            addEdge(v_s, u, 1000);
                        } else {
                            addEdge(v, u, 1000);
                        }

                        // add back edges (still outgoing connection, but res=0) for future reverse augmenting paths
                        if ((uc == '.') || (uc == '*')) {
                            addEdge(v, u+900, 0);
                        } else {
                            if (split)
                                addEdge(v, u, 0); // if u is not split and v is split add the back edge
                        }
                    }
                }
            }
        printf("%d\n", dinic());
    }

}
