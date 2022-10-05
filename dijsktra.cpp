//
// Created by KSC on 5/10/22.
//

#include <queue>
#include <vector>
#define V 256
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;


int dists[V];
int parent[V];
vector<vii> adjList; // vector of pair<id, dist>

void dijsktra(int src, int total_v) {
    for (int i = 0; i < total_v; i++) {
        dists[i] = INT_MAX;
    }
    for (int i = 0; i < total_v; i++) {
        parent[i] = -1; // record shortest path
    }
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push(make_pair(0, src)); // distance must be first in pair for sorting by distance
    dists[src] = 0;
    while (pq.size()) {
        int cur = pq.top().second;
        pq.pop();
        for (int i = 0; i < adjList[cur].size(); i++) {
            ii p = adjList[cur][i];
            int v = p.first;
            int w = p.second;
            int new_d = dists[cur] + w;
            if (new_d < dists[v]) {
                dists[v] = new_d;
                pq.push(make_pair(new_d, v));
                parent[v] = cur;
            }
        }
    }
}

int main() {
    adjList.assign(V, vii()); // init all adj list to empty

    int total_v, total_neighbor, id, dist;
    // read graph from file
    freopen("./graph_in.txt", "r", stdin);
    scanf("%d", &total_v);
    for (int i = 0; i < V; i++) {
        scanf("%d", &total_neighbor);
        for (int j = 0; j < total_neighbor; j++) {
            scanf("%d %d", &id, &dist);
            adjList[i].push_back(ii(id, dist));
        }
    }
    dijsktra(4, total_v);
    for (int i = 0; i < total_v; i++) {
        if (dists[i] == INT_MAX) {
            printf("no path to %d\n", i);
            continue;
        }
        printf("path to %d, distance %d:\n", i, dists[i]);
        int v = i;
        printf("    %d", i);
        while (parent[v] >= 0) {
            printf(" <- %d", parent[v]);
            v = parent[v];
        }
        printf("\n");
    }
}

