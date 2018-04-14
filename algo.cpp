//
// Created by Cui Shengping on 26/3/18.
//

#include <cstdio>
#include <algorithm>
using namespace std;

bool comp(int a, int b) {
    return a > b;
}

int main() {
    int arr[] = {1,3,5,9,10};
    sort(arr, arr+5, comp);
    printf("%ld\n", (lower_bound(arr, arr+5, 3, comp)-arr)); // first no larger than
    printf("%ld\n", (upper_bound(arr, arr+5, -1, comp)-arr)); // first smaller than
    printf("%d\n", *upper_bound(arr, arr+5, -1, comp)); // this would go return last
    return 0;
}



