//
// Created by KevinCui on 8/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef vector<int> vi;
vector<vi> adj(210);
short color[210];

int T, V, E;
int u, v, num_w, num_b;
bool bipartite;

void dfs_bip(int v, int c) {
    color[v] = c;
    if (c == 1)
        num_w++;
    else
        num_b++;
    for (auto &u: adj[v]) {
        if (!bipartite)
            break;
        if (color[u] == 0)
            dfs_bip(u, -c);
        else if (color[u] == c) {
            bipartite = false;
        }
    }
}

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &V, &E);
        for (auto &v: adj)
            v.clear();
        for (int e = 0; e < E; e++) {
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        memset(color, 0, sizeof color);
        bipartite = true;
        int ans = 0;
        for (int v = 0; v < V; v++) {
            if (color[v] == 0) {
                num_b = 0; num_w = 0;
                dfs_bip(v, 1);
                ans += max(min(num_b, num_w), 1);
            }
            if (!bipartite)
                break;
        }
        if (!bipartite)
            printf("-1\n");
        else {
            printf("%d\n", ans);
        }
    }

}