//
// Created by KevinCui on 10/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef pair<int, ii> pii;
typedef pair<double, ii> pdii;
vii mst;
int parent[100010]; // ufds
int set_rank[100010]; // ufds rank
int c[100010][2];
bool point[1010][1010];
vector<pdii> edges;

int T, V, E, R;
int num_e, num_set;


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
    while (scanf("%d", &V) == 1) {
        memset(c, 0, sizeof c);
        edges.clear();
        int x,y;
        for (int n = 0; n < V; n++) {
            scanf("%d %d", &x, &y);
            if (point[x][y])
                n--;
            else {
                c[n][0] = x;
                c[n][1] = y;
                point[x][y] = true;
            }
        }
        for (int i = 0; i < V; i++) {
            for (int j = i+1; j < V; j++) {
                edges.push_back(pdii(abs(c[i][0] - c[j][0]) + abs(c[i][1]-c[j][1]), ii(i, j)));
            }
        }
        sort(edges.begin(), edges.end());
        num_e = 0;
        memset(parent, -1, sizeof parent);
        memset(set_rank, 0, sizeof set_rank);
        int mst = 0;
        for (auto &e: edges) {
            if (num_e == V-1)
                break;
            ii edge = e.second;
            if (!is_same_set(edge.first, edge.second)) {
                union_set(edge.first, edge.second);
                num_e++;
                mst += e.first;
            }
        }
    }
    return 0;
}