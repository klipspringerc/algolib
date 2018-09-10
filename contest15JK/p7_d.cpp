//
// Created by KevinCui on 5/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

char grid[110][110];
int v_val[12100];
int da[12100];
int db[12100];
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};
int T, M, N;
int A, B, threshold;
int mind, cost_sum;
vi tracked_v;
vector<vii> adj;

bool check_position(int x, int y) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= M)
        return false;
    if (grid[x][y] == '0')
        return false;
    return true;
}

int trans_pos(int x, int y) {
    return x * M + y;
}

// call dijkstra for two times, A with dA, B with dB
void dijkstra(int d[], int s) {
    priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push(ii(0, s));
    d[s] = 0;
    while (!pq.empty()) {
        ii cur_ii = pq.top(); pq.pop();
        int v = cur_ii.second;
        if (cur_ii.first > d[v])
            continue;
        if (v_val[v] == threshold)
            tracked_v.push_back(v);
        for (auto & p: adj[v]) {
            if (v_val[p.second] <= threshold && (d[p.second] == -1 || p.first + d[v] < d[p.second])) {
                d[p.second] = d[v] + p.first;
                if (d[p.second] == -1)
                    printf("cur %d, u %d\n", v, p.second);
                pq.push(ii(d[p.second], p.second));
            }
        }
    }
}

int main() {

    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &N, &M);
        adj.assign(M*N, vii());
        // for adj, (weight, v) pair
        getchar();
        mind = 1210000;
        cost_sum = 0;
        int v, u, nx, ny;
        for (int i = 0; i < N; i++)
            gets(grid[i]);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                char cur_c = grid[i][j];
                if (cur_c == '0')
                    continue;
                v = trans_pos(i, j);
                if (cur_c == 'A')
                    A = v;
                else if (cur_c == 'B')
                    B = v;
                else {
                    v_val[v] = cur_c - '0';
                    cost_sum += v_val[v];
                }
                for (int d = 0; d < 4; d++) {
                    nx = i + dr[d];
                    ny = j + dc[d];
                    if (check_position(nx, ny)) {
                        u = trans_pos(nx, ny);
                        v_val[u] = grid[nx][ny] - '0';
                        adj[v].push_back(ii(v_val[u], u));
                    }
                }
            }
        for (threshold = 9; threshold > 0; threshold--) {
            tracked_v.clear();
            memset(da, -1, sizeof da);
            memset(db, -1, sizeof db);
            dijkstra(da, A);
            dijkstra(db, B);
//            puts("da");
//            for (int i = 0; i < 8; i++)
//                printf(" %d", db[i]);
//            puts("");
            for (auto & v: tracked_v) {
                if (da[v] > 0 && db[v] > 0 && da[v] + db[v] - 2 * threshold < mind) {
//                    printf("cur_v %d da %d db %d t %d\n", v, da[v], db[v], threshold);
                    mind = da[v] + db[v] - 2 * threshold;
                }
            }
            if (mind == 1210000)
                mind = cost_sum;
        }
        printf("Case #%d: %d\n", t+1, cost_sum - mind);
    }
}