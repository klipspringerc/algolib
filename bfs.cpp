//
// Created by KevinCui on 14/4/18.
//

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int V, E;
vector<vii> AdjList;
vi P;

void printPath(int s, int d) {
    if (d == s) { printf("%d", d); return; }
    printPath(s, P[d]);
    printf(" %d", d);
}

void bfs(int s) {
    P.assign(V, -1);
    vi d = vi(V, 1000000); // distance
    d[s] = 0;
    queue<int> aux;
    aux.push(s);
    bool bipartite = true;
    while (!aux.empty()){
        int v = aux.front(); aux.pop();
        for (int j = 0; j < (int) AdjList[v].size(); j++) {
            ii up = AdjList[v][j];
            if (d[up.first] == 1000000) {
                d[up.first] = d[v] + 1;
                P[up.first] = v;
                aux.push(up.first);
            } else {
                if (d[up.first] % 2 == d[v] % 2)
                    bipartite = false;
            }
        }
    }
    printf("bipartite: %d\n", bipartite);
}

int main() {
    char filepath[100];
    strcpy(filepath, "/Users/Kevin/CLionProjects/algolib/CP3/ch4/in_04.txt");
    freopen(filepath, "r", stdin);
    scanf("%d %d", &V, &E);
    printf("%d %d\n", V, E);
    AdjList.assign(V, vii());
    int a,b;
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &a, &b);
        AdjList[a].push_back(ii(b, 0));
        AdjList[b].push_back(ii(a, 0));
    }
    printf("bfs\n");
    bfs(5);
    printf("Shortest path: ");
    printPath(5, 7);
    printf("\n");
    return 0;
}

