//
// Created by KevinCui on 10/8/18.
//

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef pair<int, ii> pii;
typedef pair<double, ii> pdii;
int parent[60]; // ufds
int set_rank[60]; // ufds rank
int c[60][2];
//double ppl_total[60];
int ppl[60];
vector<pdii> edges;

int T, V, E;
int p, num_e, total, num_set;

int find(int i) {
    return (parent[i] == i)? i : (parent[i] = find(parent[i]));
}

bool is_same_set(int i, int j) {
    return (find(i) == find(j));
}

void union_set(int i, int j) {
    if (is_same_set(i, j))
        return;
    num_set--;
    int ri = find(i);
    int rj = find(j);
    if (set_rank[ri] > set_rank[rj]) {
        parent[rj] = ri;
        ppl[ri] += ppl[rj];
    }
    else {
        parent[ri] = rj;
        ppl[rj] += ppl[ri];
        if (set_rank[ri] == set_rank[rj])
            set_rank[rj]++;
    }
}

int main() {
    int t = 1;
    while (true) {
        scanf("%d", &V);
        if (!V)
            break;
        memset(c, 0, sizeof c);
        memset(ppl, 0, sizeof ppl);
        total = 0;
        for (int v = 0; v < V; v++) {
            scanf("%d %d %d", &(c[v][0]), &(c[v][1]), &ppl[v]);
            parent[v] = v;
            total += ppl[v];
        }

        edges.clear();
        for (int i = 0; i < V; i++) {
            for (int j = i+1; j < V; j++) {
                edges.push_back(pdii(hypot(c[i][1]-c[j][1], c[i][0]-c[j][0]), ii(i, j)));
//                edges.push_back(pdii(sqrt((c[i][0]-c[j][0])*(c[i][0]-c[j][0])+(c[i][1]-c[j][1])*(c[i][1]-c[j][1])), ii(i, j)));
            }
        }
        sort(edges.begin(), edges.end());
        memset(set_rank, 0, sizeof set_rank);
        num_e = 0;
        double sum = 0;
        for (auto &e: edges) {
            if (num_e == V-1)
                break;
            ii edge = e.second;
            if (!is_same_set(edge.first, edge.second)) {
                if (find(edge.first) == find(0))
                    sum += ppl[find(edge.second)] * e.first;
                else if (find(edge.second) == find(0))
                    sum += ppl[find(edge.first)] * e.first;
                union_set(edge.first, edge.second);
                num_e++;
            }
        }
        printf("Island Group: %d Average %.2lf\n\n", t++, sum/total);
    }



}