//
// Created by KevinCui on 9/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef pair<int, ii> pii;
vii mst;
int parent[110]; // ufds
int set_rank[110]; // ufds rank
vector<pii> edges;

int T, V, E;
int num_e, mst_cost, num_set;


int find(int i) {
    return (parent[i] == -1) ? i : (parent[i] = find(parent[i]));
}

bool is_same_set(int i, int j) {
    return find(i) == find(j);
}

void union_set(int i, int j) {
    if (is_same_set(i, j))
        return;
    num_set--;
    int ri = find(i);
    int rj = find(j);
    if (set_rank[ri] > set_rank[rj])
        parent[rj] = ri;
    else {
        parent[ri] = rj;
        if (set_rank[ri] == set_rank[rj]) set_rank[rj]++;
    }
}


int main() {
    scanf("%d", &T);
    int u, v, w;
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &V, &E);
        edges.clear();
        mst.clear();
        for (int e = 0; e < E; e++) {
            scanf("%d %d %d", &u, &v, &w);
            edges.push_back(pii(w, ii(u, v)));
        }
        sort(edges.begin(), edges.end());
        // kruskal
        num_e = 0;
        mst_cost = 0;
        num_set = V;
        memset(parent, -1, sizeof parent);
        memset(set_rank, 0, sizeof set_rank);
        for (int i = 0; i < E && num_e < V-1; i++) {
            pii cur = edges[i];
            ii edge = cur.second;
            if (!is_same_set(edge.first, edge.second)) {
                num_e++;
                mst.push_back(edge);
                union_set(edge.first, edge.second);
                mst_cost += cur.first;
            }
        }
        printf("%d ", mst_cost);
        int min_mst_cost = 1000000000;
        for (auto &e: mst) {
            mst_cost = 0;
            num_e = 0;
            num_set = V;
            memset(parent, -1, sizeof parent);
            memset(set_rank, 0, sizeof set_rank);
            for (int i = 0; i < E && num_e < V-1; i++) {
                pii cur = edges[i];
                ii edge = cur.second;
                if (!is_same_set(edge.first, edge.second) && (e.first != edge.first || e.second != edge.second)) {
                    num_e++;
                    union_set(edge.first, edge.second);
                    mst_cost += cur.first;
                }
            }
            if (num_set == 1)
                min_mst_cost = min(min_mst_cost, mst_cost);
        }
        printf("%d\n", min_mst_cost);
    }
}
