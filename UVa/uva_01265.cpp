//
// Created by KevinCui on 10/8/18.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef pair<int, ii> pii;
int parent[5010]; // ufds
int set_rank[5010]; // ufds rank
vi set_size;
vector<pii> edges;

int T, V, E;
int u, v, w, num_e, num_set, sum_size;

bool comp(pii a, pii b) {return a.first > b.first;}

int find(int i) {
    return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
}

bool is_same_set(int i, int j) {
    return find(i) == find(j);
}

void union_set(int i, int j) {
    if (is_same_set(i, j))
        return;
//    num_set--;
    int ri = find(i);
    int rj = find(j);
    if (set_rank[ri] > set_rank[rj]) {
        parent[rj] = ri;
        set_size[ri] += set_size[rj];
    }
    else {
        parent[ri] = rj;
        set_size[rj] += set_size[ri];
        if (set_rank[ri] == set_rank[rj]) set_rank[rj]++;
    }
}

bool check(int r) {
    if (set_size[r] == V)
        return true;
    int mx = 0, mi = 1000000;
    for (auto &e: edges) {
        int u = e.second.first;
        int v = e.second.second;
        if (find(u) == r && find(v) == r) {
            mi = min(mi, e.first);
        } else if (find(u) == r || find(v) == r) {
            mx = max(mx, e.first);
        }
        if (mx >= mi)
            return false;
    }
    return true;
}

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &V, &E);
        edges.clear();
        for (int e = 0; e < E; e++) {
            scanf("%d %d %d", &u, &v, &w);
            edges.push_back(pii(w, ii(u, v)));
        }
        for (int v = 1; v < V+1; v++)
            parent[v] = v;
        sort(edges.begin(), edges.end(), comp);

        memset(set_rank, 0, sizeof set_rank);
        set_size.assign(V+2, 1);
        num_e = 0;
        sum_size = 0;
        for (auto &e: edges) {
            if (num_e == V-1)
                break;
            ii edge = e.second;

            if (!is_same_set(edge.first, edge.second)) {
                union_set(edge.first, edge.second);
                num_e++;
                if (check(find(edge.first))) {
                    sum_size += set_size[find(edge.first)];
                }
            }
        }
        printf("%d\n", sum_size);
    }
}