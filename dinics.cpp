//
// Use Dinic's algorithm on uva 00259
// AC
// Created by KevinCui on 14/8/18.
//

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <bitset>
#include <stack>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

int res[40][40]; // residual values
int p[40]; // track augmenting path
vi adj[40];
char line[50]; // input
int f; // increase amount of flow
int dist[50]; // used for level graph

#define BASEAPP 1
#define BASECPU 27
#define T 37
#define S 0


bool d_bfs() {
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    queue<int> q; q.push(S);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &u: adj[v]) {
            if (dist[u] == -1 && res[v][u]) {
                dist[u] = dist[v]+1;
                q.push(u);
            }
        }
    }
    return (dist[T] != -1); // whether there is still a level graph with augment path
}


int d_dfs(int v, int minFlow) {
    if (v == T)
        return minFlow;
    for (auto &u: adj[v]) {
        // notice the level check below
        if (dist[u] == dist[v]+1 && res[v][u]) {
            int flow = d_dfs(u, min(res[v][u], minFlow));
            if (flow > 0) {
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
    while (d_bfs()) {
        while ((flow = d_dfs(S, 1000000000))) {
            ans += flow;
        }
    }
    return ans;
}


int main() {

    for (int c = BASECPU; c < BASECPU+10; c++) {
        adj[c].push_back(T);
        adj[T].push_back(c);
    }
    for (int app = BASEAPP; app < BASEAPP+26; app++) {
        adj[S].push_back(app);
        adj[app].push_back(S);
        for (int c = BASECPU; c < BASECPU+10; c++) {
            adj[app].push_back(c);
            adj[c].push_back(app);
        }
    }
    while (gets(line) != NULL) {
        memset(res, 0, sizeof res);
        int sum = 0;
        while (strlen(line)) {
            int app = (line[0] - 'A') + BASEAPP;
            int cap = line[1] - '0';
            res[S][app] = cap;
            sum += cap;
            int i = 3;
            while (line[i] != ';') {
                int cpu = line[i] - '0' + BASECPU;
                res[app][cpu] = 1000000000;
                i++;
            }
            if (gets(line) == NULL)
                break;
        }
        for (int c = 0; c < 10; c++) res[c+BASECPU][T] = 1;
        // do max flow here
        int mf = dinic();

        char output[11];
        bool success = (sum == mf);
        if (success) {
            for (int i = 0; i < 10; i++) {
                output[i] = '_';
                for (int j = 0; j < 26; j++) {
                    if (res[BASECPU + i][BASEAPP + j]) {
                        output[i] = 'A' + j;
                        break;
                    }
                }
            }
            output[10] = '\0';
            puts(output);
        } else {
            puts("!");
        }
    }


}

