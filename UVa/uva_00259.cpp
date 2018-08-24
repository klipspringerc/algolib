//
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

#define BASEAPP 1
#define BASECPU 27
#define T 37
#define S 0

// vertices: 0-source, 1~26-apps, 27~36-computers, 37-target


void augment(int v, int minF) {
    if (v == S)
        f = minF;
    else if (p[v] != -1) {
        augment(p[v], min(minF, res[p[v]][v]));
        res[p[v]][v] -= f;
        res[v][p[v]] += f;
    }
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
//            adj[S].push_back(app);
//            adj[app].push_back(S);
            int cap = line[1] - '0';
            res[S][app] = cap;
            sum += cap;
            int i = 3;
            while (line[i] != ';') {
                int cpu = line[i] - '0' + BASECPU;
//                adj[app].push_back(cpu);
//                adj[cpu].push_back(app);
                res[app][cpu] = 1000000000;
                i++;
            }
            if (gets(line) == NULL)
                break;
        }
        for (int c = 0; c < 10; c++) res[c+BASECPU][T] = 1;
        // do max flow here
        int mf = 0;
        while (true) {
            queue<int> q; q.push(S);
            bitset<40> visited; visited[S] = true;
            memset(p, -1, sizeof p);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                if (v == T)
                    break;
                for (auto &u: adj[v]) {
                    if (u == -1)
                        printf("detect -1 when v %d \n", v);
                    if (res[v][u] && !visited[u]) {
                        visited[u] = true;
                        q.push(u);
                        p[u] = v;
                    }
                }
            }
            f = 0;
            augment(T, 1000000000);
            mf += f;
            if (f == 0)
                break;
        }
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