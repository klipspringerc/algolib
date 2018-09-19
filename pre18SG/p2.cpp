//
// Created by KevinCui on 15/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

typedef pair<int, int > ii;
typedef vector<ii> vii;

int N, K;
int a, b;
//vii aps;

int p[1000010];
//int rank[1000010]


int findS(int i) {
    return ((p[i] == i)? i : (p[i] = findS(p[i])));
}

void unionS(int i, int j) {
    int x = findS(i);
    int y = findS(j);
    if (x != y) {
        p[x] = y;
    }
}

bool isSameS(int i, int j) {
    return (findS(i) == findS(j));
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i <= N; i++)
        p[i]=i;
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &a, &b);
//        aps.push_back(ii(a, b));
        unionS(a, b);
    }
    for (int i = 1; i <= N/2+2; i++) {
        int j = N + 1 - i;
        if (j <= i)
            break;
        if (!isSameS(i, j)) {
            printf("NO\n");
            return 0;
        }

    }
    printf("Yes\n");
    return 0;
}