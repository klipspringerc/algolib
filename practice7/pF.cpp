//
// wrong solution, pricing method is a 2-approx
// Created by KevinCui on 6/10/18.
//

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;


typedef pair<int, int> ii;
typedef vector<ii> vii;
int ga, gb;
int N;
int a, b, c;
int tight[1010];
int n, v, u;
vii edges;

int main() {
    edges.clear();
    scanf("%d", &N);
    scanf("%d %d", &ga, &gb);
    scanf("%d %d %d", &a, &b, &c);
//    printf("%d %d %d %d %d %d\n", N, ga, gb, a, b, c);
    for (int i = 1; i <= N; i++) {
        tight[i] = c;
    }
    int curV = N+1; // current group vertex
    for (int i = 0; i < ga; i++) {
        scanf("%d", &n);
        tight[curV] = a;
        for (int j = 0; j < n; j++) {
            scanf("%d", &v);
            edges.push_back(ii(v, curV));
        }
        curV++;
    }
    for (int i = 0; i < gb; i++) {
        scanf("%d", &n);
        tight[curV] = b;
        for (int j = 0; j < n; j++) {
            scanf("%d", &v);
            edges.push_back(ii(v, curV));
        }
        curV++;
    }
//    printf("sizeof edges %d\n", edges.size());

    for (auto e: edges) {
        int mint = min(tight[e.first], tight[e.second]);
        tight[e.first] -= mint;
        tight[e.second] -= mint;
        printf("tight %d-%d by %d\n", e.first, e.second, mint);
    }
    int curCost = 0;
    for (int i = 1; i <= N; i++)
        if (tight[i] == 0)
            curCost += c;
    for (int i = N+1; i <= N+ga; i++)
        if (tight[i] == 0)
            curCost += a;
    for (int i = N+ga+1; i <= N+ga+gb; i++)
        if (tight[i] == 0)
            curCost += b;



    printf("%d\n", curCost);
    return 0;

}