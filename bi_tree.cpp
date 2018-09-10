//
// Binary Index Tree
// Used to track the sum the first i elements of an array
// provide two operations
// adjust (update value) and rsq (query sum)
// Created by Cui Shengping on 13/4/18.
//

#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;

typedef vector<int> vi;
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
        return rsq(r) - (l == 1 ? 0 : rsq(l));
    }

    // adjuest the value of i by v
    void adjust(int i, int v) {
        for (; i < (int)ft.size(); i += LSOne(i)) ft[i] += v;
    }

};


// Fenwick tree for zero-indexed scheme
struct ZeroFenwickTree {

private:
    vi ft;

public:

    void adjust(int i, int v) {
        for (; i < ft.size(); i |= i-1)
            ft[i] += v;
    }

    int rsq(int r) {
        int sum = 0;
        for (; r > 0; r = (r & (r+1)) -1)
            sum += ft[r];
        return sum;
    }

    int rsq(int l, int r) {
        return (l == 0)? rsq(r) : rsq(r) - rsq(l);
    }
};



int main() {
    FenwickTree ft(10);
    printf("%d\n", ft.rsq(1, 10));
    ft.adjust(3,7);
    printf("%d\n", ft.rsq(1, 10));
    printf("%d\n", ft.rsq(2));
    ft.adjust(1,4);
    printf("%d\n", ft.rsq(1, 10));
    printf("%d\n", ft.rsq(1));
}
