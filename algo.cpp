//
// Created by Cui Shengping on 26/3/18.
//

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))

bool comp(int a, int b) {
    return a <= b;
}

void test_lower_bound() {
    int arr[] = {1,3,5,9,10};
//    int arr[] = {10, 9, 5, 3,1};
    sort(arr, arr+5, comp);
    printf("%ld\n", (lower_bound(arr, arr+4, 5, comp)-arr)); // first no larger than
    printf("%ld\n", (upper_bound(arr, arr+4, 5, comp)-arr)); // first larger than
    printf("%ld\n", (upper_bound(arr, arr+4, -1, comp)-arr)); // this would go return last
}

void test_sort() {
    int arr[] = {6,4,2,3};
//    sort(arr+1, arr+4, comp);
    stable_sort(arr+1, arr+4, comp);
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


int main() {
//    test_sort();
    test_pow_2();
//    test_lower_bound();
}



