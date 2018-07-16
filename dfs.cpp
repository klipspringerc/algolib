//
// Various DFS Application
// Created by KevinCui on 14/4/18.
//

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector <vii> AdjList;

#define DFS_WHITE -1
#define DFS_BLACK 1
#define DFS_GRAY 2

vi dfs_num; // the status for each vertex
int numCC;

// standard dfs
void dfs(int v) {
    printf("%d ", v);
    dfs_num[v] = DFS_BLACK;
    for (int i = 0; i < AdjList[v].size(); i++) {
        ii u = AdjList[v][i];
        if (dfs_num[u.first] == DFS_WHITE)
            dfs(u.first);
    }
}

vi dfs_parent;

void graphCheck(int v) {
    dfs_num[v] = DFS_GRAY; // mark the vertex as on-going
    for (int i = 0; i < AdjList[v].size(); i++) {
        ii u = AdjList[v][i];
        if (dfs_num[u.first] == DFS_WHITE) {
            dfs_parent[u.first] = v;
            graphCheck(u.first);
        } else if (dfs_num[u.first] == DFS_GRAY) {
            if (dfs_parent[v] == u.first)
                printf(" Bidirectional (%d, %d) - (%d, %d)\n", v, u.first, u.first, v);
            else
                printf("Back Edge / Cycle (%d, %d)\n", v, u.first);
        } else if (dfs_num[u.first] == DFS_BLACK) {
            printf("Forward / Cross Edge (%d, %d)\n", v, u.first);
        }
    }
    dfs_num[v] = DFS_BLACK;
}

// Articulation point: the point connecting two connected components
// If a articulation point is removed along with its edges,
// the connected component it resides in would be broken into multiple CCs.
// Bridge is the edge connecting the would-be CCs
// If the bridge edge is removed, the CC would be broken to 2 CCs

int dfs_counter; // track the number of vertices examined and initialize the level
vi dfs_low; // track the lowest level each vertex connected to
vector<bool> articulationPoint; // whether the vertex is an AP
int dfs_root, rootChildren;

void articulationPointAndBridge(int v) {
    dfs_low[v] = dfs_num[v] = dfs_counter++; // initialize level info
    for (int i = 0; i < AdjList[v].size(); i++) {
        ii u = AdjList[v][i];
        if (dfs_num[u.first] == DFS_WHITE) {
            dfs_parent[u.first] = v;
            if (v == dfs_root) rootChildren++; // If no. of rootChildren > 1, root is AP
            articulationPointAndBridge(u.first);
            if (dfs_low[u.first] >= dfs_num[v]) {
                articulationPoint[v] = true;
                if (dfs_low[u.first] > dfs_num[v])
                    printf("Edge (%d, %d) is a bridge\n", v, u.first);
            }
            dfs_low[v] = min(dfs_low[v], dfs_low[u.first]); // for new vertices, we propagate the dfs_low value
        } else {
            if (dfs_parent[v] != u.first)
                // note here we take the lower between low and num to reflect the actual lowest level of the current CC
                // so the value would not be affected by the lowest level of other CC the vertex u connects to
                dfs_low[v] = min(dfs_low[v], dfs_num[u.first]);
        }
    }
}

// Strongly connected component: a directed graph is called strongly connected if there is a path in each
// direction between each pair of the vertices of the graph (every v is reachable from every other v)

vector<bool> visited;
vi s; // auxiliary stack
int numSCC;

// Tarjan algorithm finds SCCs in linear time
// dfs with a stack to track current component,
// each call would return when v has a path to an earlier vertex, otherwise a component would be popped from stack
// the search result is a forest of spanning trees
// Any vertex of a spanning tree component can be the root if it happens to be the first node of the component that is discovered by the search

void tarjanSCC(int v) {
    dfs_low[v] = dfs_num[v] = dfs_counter++;
    s.push_back(v);
    visited[v] = true;
    for (int i = 0; i < AdjList[v].size(); i++) {
        ii u = AdjList[v][i];
        if (dfs_num[u.first] == DFS_WHITE)
            tarjanSCC(u.first);
        if (visited[u.first]) // only update if it belongs to the current traversal.
            dfs_low[v] = min(dfs_low[v], dfs_low[u.first]);
    }
    // if low == num, then the current node is the root of the current spanning tree.
    // we pop up nodes with guarantee that no nodes holds a reference ealier than the dfs_num[v] (if so, dfs_low[v] would be smaller than dfs_num[v])
    // pop the stack until reach the root node v
    if (dfs_low[v] == dfs_num[v]) {
        printf("SCC %d:", ++numSCC);
        while (1) {
            int u = s.back();
            s.pop_back();
            visited[u] = false; // clear visit state for possibly repetitive visit
            printf(" %d", u);
            if (u == v) break;
        }
        printf("\n");
    }
}

int main() {
    int V, total_neighbors, id, weight;
    freopen("./CP3/ch4/in_01.txt", "r", stdin);
    scanf("%d", &V);
    AdjList.assign(V, vii());
    for (int i = 0; i < V; i++) {
        scanf("%d", &total_neighbors);
        for (int j = 0; j < total_neighbors; j++) {
            scanf("%d %d", &id, &weight);
            AdjList[i].push_back(ii(id, weight));
        }
    }
    printf("Start standard DFS\n");
    numCC = 0;
    dfs_num.assign(V, DFS_WHITE);
    for (int v = 0; v < V; v++) {
        if (dfs_num[v] == DFS_WHITE) {
            numCC++;
            dfs(v);
            printf("\n");
        }
    }
    printf("number of CC: %d\n", numCC);

    printf("Start graph edge checking\n");
    dfs_parent.assign(V, -1);
    dfs_num.assign(V, DFS_WHITE);
    for (int v = 0; v < V; v++) {
        if (dfs_num[v] == DFS_WHITE) {
            graphCheck(v);
        }
    }

    printf("Articulation Points and Bridges\n");
    dfs_parent.assign(V, -1);
    dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0);
    articulationPoint.assign(V, false);
    dfs_counter = 0;
    printf("Bridges:\n");
    for (int v = 0; v < V; v++) {
        if (dfs_num[v] == DFS_WHITE) {
            dfs_root = v;
            rootChildren = 0;
            articulationPointAndBridge(v);
            articulationPoint[v] = (rootChildren > 1);

        }
    }
    printf("Articulation Points:\n");
    for (int i = 0; i < V; i++)
        if (articulationPoint[i])
            printf(" Vertex %d\n", i);

    printf("Strongly Connected Components (the input graph must be DIRECTED)\n");
    dfs_low.assign(V, 0); dfs_num.assign(V, DFS_WHITE); visited.assign(V, false);
    dfs_counter = numSCC = 0;
    for (int v = 0; v < V; v++)
        if (dfs_num[v] == DFS_WHITE)
            tarjanSCC(v);

    return 0;
}

