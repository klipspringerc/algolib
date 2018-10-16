//
// Created by KevinCui on 16/10/18.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> names;

int p, c, t, r;
int l, m;

int prices[110];
bool can[110];
bool exist = false;
typedef long long int ll;
int min_price = 1000000;
int MIN_WEEK = 10080;


ll gcd(ll a, ll b) {
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

ll get_gcd(ll a, ll b) {
    ll r = (a > b)? gcd(a,b): gcd(b,a);
    return r;
}

ll get_gc(ll a, ll b) {
    ll gcdnum = get_gcd(a, b);
    return (a / gcdnum) * b;
}

int main() {
    string ins;
    scanf("%d %d", &l, &m);
    memset(can, 0, sizeof can);
    names.clear();
    getchar();
    for (int i = 0; i < m; i++) {
        getline(cin, ins);
        auto idx = ins.find(',');
        names.push_back(ins.substr(0, idx));
        sscanf(ins.substr(idx+1, ins.length() - idx - 1).c_str(), "%d,%d,%d,%d", &p, &c, &t, &r);
        prices[i] = p;
        int cycle = t+r;
        ll gc = get_gc(cycle, MIN_WEEK);
        can[i] = (gc / cycle * c * t >= gc / MIN_WEEK * l);
//        int full_cycle = MIN_WEEK / (t+r);
//        int rem_t = min(t, MIN_WEEK - (t+r) * full_cycle);
//        can[i] =  ((full_cycle * t + rem_t) * c >= l);
        if (can[i]) {
            exist = true;
            min_price = min(min_price, p);
        }
//        cout << names[i] << endl;
//        printf("read values %d %d %d %d\n", p, c, t, r);
    }
    if (!exist)
        printf("no such mower\n");
    else {
        for (int i = 0; i < m; i++) {
            if (can[i] && prices[i] == min_price)
                printf("%s\n", names[i].c_str());
        }
    }
    return 0;
}