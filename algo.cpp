//
// Created by Cui Shengping on 26/3/18.
//

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include <map>
#include <set>
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> pii;

#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

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

void test_zero_bi(int val, int n) {
    for (; val < n; val |= val+1)
        printf("%d ", val);
    puts("");
}

void test_log() {
    for ( int i = 0; i < 20; i++) {
        printf("%d %d\n", i, (int)floor(log((double)i) / log(2.0)));
    }
    // (int)((log((double)S) / log(2.0)) + 0.5))
    for ( int i = 0; i < 20; i++) {
        printf("%d %d\n", i, (int)ceil(log((double)i) / log(2.0)));
    }
}

void test_arr_pointer() {
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int as[5] = {1,2,3,4,5};
    int * b = a + 5;
    int (*c) [5]; // pointer to an array of 5 integers
    for (int i = 0; i < 4; i++)
        printf("%d ", b[i]);
    puts("");
    c = &as; // c = &a would be an error type mismatch
    for (int i = 0; i < 5; i++)
        printf("%d ", (*c)[i]);
    puts("");
}


void test_rand() {
    double m;
    srand(1); // set seed
    puts("simple rand");
    for (int i = 0; i < 10; i++) {
        m = (double)rand() / RAND_MAX;
        printf("%lf\n", m);
    }
    printf("random max %d\n", RAND_MAX);

    puts("uniform rand");
    double lower_bound = 0;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
//    double a_random_double = unif(re);
    for (int i = 0; i < 10; i++) {
        m = unif(re);
        printf("%lf\n", m);
    }
    puts("");
}

int my_sum(int a, int b) { return a+b; }

void test_function_pointer() {
    int (*fp[4]) (int, int);
    fp[0] = &my_sum;
    printf("my sum %d \n", (*fp[0])(21,31));
}


void assoc() {
    int a = 2;
    int b = 3;
    int result = a+++b; // (a++) + b
    printf("result %d and a %d  b %d\n", result, a, b);
}

void precision() {
    float af = 2.33e15;
    float bf = 1.0f + af;
    printf("bf - af %f\n", bf-af);

}

void integral_promotions() {
    unsigned long long al = 1e12;
    unsigned int aui = 1 << 31;
    int ai = 1 << 31;
    printf("%lld\n", al + aui);
    printf("%lld\n", al + ai);
}

void read_dates() {
    char days[10];
    int h1,h2;
    int m1, m2;
    int c = scanf("%s %d:%d-%d:%d", days, &h1, &m1, &h2,&m2);
    puts(days);
    printf("%d %d %d %d\n", h1, m1, h2, m2);
    printf("%d\n", strcmp("Tues", days));
    printf("%d\n", c);
}

void split_parse(string &S) {
    int pos_ws, pos_dot;
    int next_nl;
    int pos = 0;
    int len = S.length();
    pos_ws = S.find(" ");
    pos_dot = S.rfind(".");
    printf("ext: %s\n", S.substr(pos_dot+1, pos_ws-pos_dot-1).c_str());
    printf("size: %d\n", stoi(S.substr(pos_ws+1, len-pos_ws-2)));

}

void test_map() {
    map<string, int> mapper;
    mapper["mp3"] = 0;
    mapper["aac"] = 0;
    mapper["flac"] = 0;
    printf("%d\n", mapper["aac"]);
    printf("%d\n", mapper["bbc"]);

}

void test_set() {
    set<int, greater<int>> s;
    s.insert(7);
    s.insert(133);
    s.insert(24);
    s.insert(256);
    s.insert(99);
    // check all members
    for (set<int>::iterator it = s.begin(); it != s.end(); it++)
        printf("%d ", *it);
    puts("");
    // iterate with range
    for (set<int>::iterator it = s.begin(); it != s.lower_bound(55); it++)
        printf("%d ", *it);
    puts("");

    // check exist
    printf("find 33 %d \n", (s.find(33) == s.end()));
    printf("find 133 %d \n", *s.find(133));

}

void test_string() {
    string ts = "teststring";
    string tb = "teststring";
    string tc = "aeststring";
    printf("compare same literal %d\n", (ts == tb));
    tc[0] = 't';
    printf("compare string %d\n", (ts == tc));
    printf("char 3 equal t :%d\n", (ts[3] == 't'));
    ts[5] = 'a'; // string is mutable
    printf("%s\n", ts.c_str());
}


vector<int> counting_sort(vector<int> & nums) {
    // assume nums range [0-255]
    vector<int> count(256, 0);
    for (int num : nums) {
        count[num]++;
    }
    // count sum until each value
    // count[i] indicates :
    //  first position of value i in the sorted results;
    //  or alternatively: how many value smaller than i is in nums.
    for (int i = 0, sum = 0; i < 256; i++) {
        int cur_val_count = count[i];
        count[i] = sum;
        sum += cur_val_count;
    }
    vector<int> results(nums.size());
    for (int num : nums) {
        // if there are multiple same values, increment ranking index each time one value is added to results
        results[count[num]++] = num;
    }
    return results;
}

void run_sort() {
    vector<int> input = {9,2,0,4,2};
    vector<int> result = counting_sort(input);
    for (int num: result) {
        printf("%d ", num);
    }
    printf("\n");
}

int main() {
    printf("result: %d\n", gcd(14,18));
//    run_sort();
//    test_sort();
//    test_pow_2();
//    test_vector();
//    test_pq();
//    test_lower_bound();
//    test_zero_bi(6,50);
//    test_zero_bi(5,50);
//    test_zero_bi(4,50);
//    test_log();
//    test_arr_pointer();
//    test_rand();
//    test_function_pointer();
//    runt();
//    assoc();
//    precision();
//    integral_promotions();
//    read_dates();
//    test_map();
//    string st = "greatSong.flac 1000b";
//    split_parse(st);
//    test_string();
//    test_set();

}



