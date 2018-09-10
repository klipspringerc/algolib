//
// Created by KevinCui on 1/9/18.
//

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;


typedef pair<int, int> ii;
typedef vector<ii> vii;

vii e;
int T, N;
int x[210];
int y[210];
int see[210];
int count_p[40010]; // how many negative edges after idx (e > idx);


int main() {
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        e.clear();
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", x+i);
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", y+i);
        }
        int s;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &s);
                e.push_back(ii((x[i]-x[j]) * (x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]), s));
            }
        }
        sort(e.begin(), e.end());
//        int ptr = e.size()-1;
        int count = 0;
        for (int i = e.size()-1; i > -1; i--) {
            count_p[i] = count;
            if (e[i].second == 1)
                count++;
        }
        int ptr = 0;
        int count_n = 0;
        int min_count = 400000;
        int P;
        while (true) {
            while (ptr < e.size()-1 && e[ptr].first == e[ptr+1].first) {
                if (e[ptr].second == 0)
                    count_n++;
                ptr++;
            }
            if (e[ptr].second == 0)
                count_n++;
            if (count_n + count_p[ptr] < min_count) {
                min_count = count_n + count_p[ptr];
                P = e[ptr].first;
            }
            ptr++;
            if (ptr == e.size())
                break;
        }
        printf("Case #%d: %d %d\n", t+1, P, min_count);
    }

    return 0;
}