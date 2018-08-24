//
// Created by Cui Shengping on 26/3/18.
//

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> pii;

#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))

bool comp(int a, int b) {
    return a <= b;
}

bool comp_lower(int a, int b) {
    return a > b;
}
void test_lower_bound() {
    int arr[] = {1,3,5,9,10};

    int arr_r[] = {10, 9, 5, 3,1};
    sort(arr, arr+5, comp);
    puts("compare lower_bound & upper_bound with <=");
    printf("%ld\n", (lower_bound(arr, arr+5, 5, comp)-arr)); // first no larger than
    printf("%ld\n", (upper_bound(arr, arr+5, 5, comp)-arr)); // first larger than
    puts("compare lower_bound & upper_bound with default comp");
    printf("%ld\n", (lower_bound(arr, arr+5, 5)-arr)); // first no larger than
    printf("%ld\n", (upper_bound(arr, arr+5, 5)-arr)); // first larger than
    puts("compare lower_bound & upper_bound with >");
    printf("%ld\n", (lower_bound(arr_r, arr_r+5, 5, comp_lower)-arr_r)); // this would go return last
    printf("%ld\n", (upper_bound(arr_r, arr_r+5, 5, comp_lower)-arr_r)); // this would go return last
    puts("compare lower_bound & upper_bound with range zero");
    printf("%ld\n", (lower_bound(arr, arr+0, 1)-arr)); // first no larger than
    printf("%ld\n", (upper_bound(arr, arr+0, 1)-arr)); // first larger than
}

struct cmp
{bool operator()(int a,int b) { return  a > b; }
};

void test_sort() {
    int arr[] = {6,4,2,3};
    sort(arr, arr+4, comp);
//    stable_sort(arr+1, arr+4, comp);
    for (int i = 0; i < 4; i++)
        printf("%d ", arr[i]);
}

void test_pow_2() {
    int num;
    for (num = 1; num < 30; num++) {
        double log_num = log((double)num) / log(2.0);
        printf("%d log = %f \n", num, log_num);
        printf("pow of log = %f \n", pow(2.0, int(log_num+0.5)));
    }
}

void test_vector() {
//    vector<int> tv(20);
//    tv[10] = 33;
//    for (auto &e: tv) {
//        printf("%d ", e);
//    }
//    printf("\n");

//    vector<pii> ts;
//    ts.push_back(pii(13, ii(2,1)));
//    ts.push_back(pii(4, ii(5,9)));
//    sort(ts.begin(), ts.begin()+2);
//    printf("%d %d \n", ts[0].first, ts[1].first);

//    vector<vector<int>> tvv;
//    tvv.assign(3,vector<int>());
//    tvv[0].push_back(13);
//    tvv[0].push_back(14);
//    tvv[1].push_back(3);
//    tvv[1].push_back(2);
//    tvv[2].push_back(23);
//    tvv[2].push_back(19);
//    tvv.clear();
//    printf("%d ", tvv[0][0]);
//    printf("size %d \n", tvv[0].size());
//    tvv.push_back(vector<int>());
//    tvv[0].push_back(15);
//    printf("%d ", tvv[0][1]);
//    printf("size %d \n", tvv[0].size());
//
    vector<ii> tii;
    tii.push_back(ii(1,3));
    tii.push_back(ii(2,4));
    for (auto &p: tii)
        printf("%d ", p.first);
    printf("\n");
    printf("\n");
    tii.clear();
    printf("%d\n", tii[0].first);
    printf("%d\n", tii[1].second);
    for (auto &p: tii)
        printf("%d ", p.first);
    printf("\n");
    tii.push_back(ii(5,2));
    printf("%d\n", tii[0].first);
    printf("%d\n", tii[1].second);
    for (auto &p: tii)
        printf("%d ", p.first);
    printf("\n");


}

void test_pq() {
    priority_queue<int, vector<int>, cmp> pq;
    pq.push(13);
    pq.push(2);
    printf("top : %d\n", pq.top());
}


int main() {
//    test_sort();
//    test_pow_2();
//    test_vector();
//    test_pq();
    test_lower_bound();
}



