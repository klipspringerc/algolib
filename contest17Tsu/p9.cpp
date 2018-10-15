//
// Created by KevinCui on 22/9/18.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>


using namespace std;


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
#define LSOne(S) (S & (-S)) // return the least significant 1


class FenwickTree {
private:
    vi ft;
public:
    FenwickTree() {}
    explicit FenwickTree(int n) { ft.assign(n+1, 0); }
    int rsq(int r) {
        int sum = 0;
        for (; r; r -= LSOne(r)) sum += ft[r];
        return sum;
    }

    int rsq(int l, int r) {
        return rsq(r) - (l == 0 ? 0 : rsq(l));
    }

    // adjuest the value of i by v
    void adjust(int i, int v) {
        for (; i < (int)ft.size(); i += LSOne(i)) ft[i] += v;
    }

};

int N;
int start[200010]; // no. of passengers when passenger i's trip starts
vii trips; // trips of all passengers
vii points; // points of trip start & end
int max1; // under policy 1
int max2;
vi additions;

// use bi tree to track no. of start trip in a given range
// for passenger i (s1 -> s2), set size at s1 + range query of s1, s2 equals the number of seat required during the trip
int main() {
    // index starts from 1
    int s, e;
    int p;
    while (scanf("%d", &N) == 1) {
        points.clear();
        max1 = 0;
        max2 = 0;
        FenwickTree bi(100010);
        trips.clear();
        memset(start, 0, sizeof start);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &s, &e);
            points.push_back(ii(s, i));
            points.push_back(ii(e, i));
            trips.push_back(ii(s, e));
            bi.adjust(s, 1);
        }
        sort(points.begin(), points.end());
        set<int> aux;
        additions.clear();
        for (int i = 0; i < points.size(); i++) {
            ii sp = points[i];
            p = sp.second;
            if (aux.find(p) != aux.end()) {
                aux.erase(p);
            } else {
                additions.push_back(p);
            }
            if (additions.size() > 0 && ( i+1 == points.size() || points[i+1].first != sp.first)) {
//                for (int i = 0; i < additions.size(); i++)
//                    aux.insert(additions[i]);
                for (auto & per: additions)
                    aux.insert(per);
                if (aux.size() > max2)
                    max2 = aux.size();
                for (auto & per: additions)
                    start[per] = aux.size();
                additions.clear();
            }
        }
        for (int i = 0; i < N; i++) {
            int cur_max = start[i];
            ii cur_t = trips[i];
            if (cur_t.second > cur_t.first + 1)
                cur_max += bi.rsq(cur_t.first, cur_t.second-1);
            if (cur_max > max1)
                max1 = cur_max;
        }
//        printf("passenger 0 %d %d\n", start[0], bi.rsq(1,2));
        printf("%d %d\n", max1, max2);
    }



}