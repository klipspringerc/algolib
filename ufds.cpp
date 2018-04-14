//
// Implementation of Union Find Disjoint Set algorithm
// Include path compression and union rank optimisation
// Created by Cui Shengping on 18/3/18.
//

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

struct Edge {
    int src, dst;
};

struct Graph {
    int V,E;
    struct Edge * edge;
};

struct Subset {
    int parent;
    int rank;
};

struct Graph* create_graph(int v, int e) {
    auto graph = (Graph *) malloc(sizeof(struct Graph));
    graph->V = v;
    graph->E = e;
    graph->edge = (Edge *) malloc(e * sizeof(struct Edge));
    return graph;
}

// naive find
int find(int parent[], int v) {
    if (v == -1) {
        return v;
    } else {
        return find(parent, parent[v]);
    }
}

// naive union
void union_set(int parent[], int a, int b) {
    int pa = find(parent, a);
    int pb = find(parent, b);
    parent[pa] = pb;
}

// find with path compression
// after the root is obtained the current v would be directly linked with the root.
int find(Subset subsets[], int v) {
    if (subsets[v].parent != v) {
        subsets[v].parent = find(subsets, subsets[v].parent);
    }
    return subsets[v].parent;
}

// union by rank
void union_rank(Subset subsets[], int a, int b) {
    int pa = find(subsets, a);
    int pb = find(subsets, b);
    if (pa == pb)
        return;
    if (subsets[pa].rank < subsets[pb].rank) {
        subsets[pa].parent = pb;
    } else if (subsets[pa].rank > subsets[pb].rank) {
        subsets[pb].parent = pa;
    } else {
        subsets[pa].parent = pb;
        subsets[pb].rank++;
    }
}

//// using naive method
//bool isCycle(Graph * graph) {
//    auto parent = (int *) malloc(graph->V * sizeof(int));
//    memset(parent, -1, graph->V * sizeof(int));
//    for (int i = 0; i < graph->E; i++) {
//        Edge e = graph->edge[i];
//        int pa = find(parent, e.src);
//        int pb = find(parent, e.dst);
//        if (pa == pb){
//            return true;
//        }
//        else {
//            parent[pa] = pb;
//        }
//    }
//    return false;
//}

bool isCycle(Graph * graph) {
    auto subsets = (Subset *) malloc(graph->V * sizeof(Subset));
    for (int v = 0; v < graph->V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    for (int i = 0; i < graph->E; i++) {
        Edge e = graph->edge[i];
        int pa = find(subsets, e.src);
        int pb = find(subsets, e.dst);
        if (pa == pb) {
            return true;
        } else {
            union_rank(subsets, pa, pb);
        }
    }
    return false;
}


int main()
{
    /* Let us create following graph
         0
        |  \
        |    \
        1-----2 */
    int V = 3, E = 3;
    struct Graph* graph = create_graph(V, E);

    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dst = 1;

    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dst = 2;

    // add edge 0-2
    graph->edge[2].src = 0;
    graph->edge[2].dst = 2;

    if (isCycle(graph)) {
        cout << "graph contains cycle" << endl;
    }
    else
        cout << "graph doesn't contain cycle" <<endl;

    return 0;
}






