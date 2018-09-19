//
// Created by KevinCui on 11/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;


typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
int T, N, M, K;
//int d[60][60];
vii adj[60];
vi path;
int dp[100010];
bool visited[60];

// first traverse tree to get path
// then dp over all values, storing the minimum number of roads needed to obtain that value.

// find the unique path and return the cost
int find_path(int v, int t) {
    int cost = 0;
    visited[v] = true;
    if (v == t)
        return 0;
    for (auto &p : adj[v]) {
        if (!visited[p.first] && (cost = find_path(p.first, t)) != -1) {
            if (p.first != t)
                path.push_back(p.second);
            return cost + p.second;
        }
    }
    return -1;
}

int main() {
    int u, v, c;
    for (scanf("%d", &T); T--;) {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; i++)
            adj[i].clear();
        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &u, &v, &c);
            adj[u].push_back(ii(v,c));
            adj[v].push_back(ii(u,c));
//            d[v][c] = d[c][v] = c;
        }
        for (scanf("%d", &K); K--;) {
            scanf("%d %d %d", &u, &v, &c);
            path.clear();
            memset(visited, 0, sizeof visited);
            int cost = find_path(u, v);
//            printf("path cost %d\n", cost);
//            for (auto & p: path)
//                printf(" %d", p);
//            puts("");
            if (cost == c)
                printf("Yes %lu\n", path.size()+1);
            else if (cost == -1 || c < cost)
                printf("No\n");
            else {
                memset(dp, 0, sizeof dp);
                dp[0] = path.size()+1;
                int k = c - cost;
                for (int i = 0; i < path.size(); i++) {
                    for (int j = 0; j <= k; j++)
                        if (dp[j] && j+path[i] <= k)
                            if (dp[j+path[i]] > dp[j]+1 || dp[j+path[i]] == 0)
                                dp[j+path[i]] = dp[j]+1;
                }
                if (dp[k])
                    printf("Yes %d\n", dp[k]);
                else
                    printf("No\n");
            }
        }
    }


}