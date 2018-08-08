//
// Created by KevinCui on 8/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;


int scc[100001];
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<vi> adj(100001);
int T, V, E;
int scc_count;

int dfs_num[100001];
int dfs_low[100001];
int dfs_order;
bool visited[100001];
int degree[100001];
vi s;

void tarjan(int v) {
    dfs_num[v] = dfs_low[v] = dfs_order++;
    visited[v] = true;
    s.push_back(v);
    for (auto &u: adj[v]) {
        if (dfs_num[u] == -1)
            tarjan(u);
        if (visited[u])
            dfs_low[v] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_num[v] == dfs_low[v]) {
        while(true) {
            int u = s.back(); s.pop_back();
            scc[u] = scc_count;
            visited[u] = false;
            if (u == v)
                break;
        }
        scc_count++;
    }
}


int main() {
    int u,v;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        for (auto &va: adj)
            va.clear();
        scanf("%d %d", &V, &E);
        for (int e = 0; e < E; e++) {
            scanf("%d %d", &u, &v);
            adj[u-1].push_back(v-1);
        }
        scc_count = 0;
        memset(dfs_num, -1, sizeof dfs_num);
        memset(visited, 0, sizeof visited);
        memset(degree, 0, sizeof degree);
        dfs_order = 0;
        for (v = 0; v < V; v++) {
            if (dfs_num[v] == -1)
                tarjan(v);
        }
        // transform to DAG
        for (v = 0; v < V; v++) {
            int newV = scc[v];
            for (auto &nb: adj[v]) {
                if (scc[nb] == newV)
                    continue;
                else {
                    degree[scc[nb]]++;
                }
            }
        }
        // remove from v with degree 0 (no edge pointed to v)
        int ans = 0;
        for (v = 0; v < scc_count; v++)
            if (degree[v] == 0)
                ans++;
        printf("%d\n", ans);
    }


}