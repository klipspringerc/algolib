//
// Created by KevinCui on 22/8/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>

#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define INF 1000000000

int V, E, s, u, v, w, t;
vector<vii> AdjList;
int dp[10010];
int dist[10010];

int main() {
    while (scanf("%d %d", &V, &E) == 2) {
        AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
        for (int e = 0; e < E; e++) {
            scanf("%d %d %d", &u, &v, &w);
            AdjList[u].push_back(ii(v, w));
        }
        scanf("%d %d", &s, &t);
        memset(dp, 0, sizeof dp);
        memset(dist, -1, sizeof dist);
        priority_queue<ii,  vector<ii>, greater<ii>> pq;
        pq.push(ii(0,s));
        dist[s] = 0;
        dp[s] = 1;
        while (!pq.empty()) {
            ii f = pq.top(); pq.pop();
            int d = f.first; u = f.second;
//            printf("check %d\n", u);
            if (u == t)
                break;
            if (dist[u] < d)
                continue;
            for (auto &vw: AdjList[u]) {
                v = vw.first;
                w = vw.second;
                if (dist[v] == -1 || dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    dp[v] = dp[u];
                    pq.push(ii(dist[v], v));
                } else if (dist[v] == dist[u]+w) {
                    dp[v] += dp[u];
                }
            }
        }

        printf("%d\n", dp[t]);
    }
    return 0;
}
