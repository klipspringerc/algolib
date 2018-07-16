#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

void get_size(int arr[]) {
    cout << sizeof(arr) << endl;
}

void test_sizeof() {
    char carr[100];
    int iarr[100];
    int * piarr = (int *) malloc(sizeof(int) * 100);
    cout << sizeof(int) << endl;
    cout << sizeof(char) << endl;
    cout << sizeof(carr) << endl;
    cout << sizeof iarr << endl;
    cout << sizeof piarr << endl;
    memset(piarr, -1, 100 * sizeof(int));
    for (int i = 0; i < 100; i++)
        cout << piarr[i] << " ";
    cout << endl;
    memset(iarr, -1, sizeof iarr);
    for (int i = 0; i < 100; i++)
        cout << iarr[i] << " ";
    cout << endl;
    get_size(piarr);

    bitset<8> bs (0xA4);
    cout << bs << endl;
    bs.flip(3);
    cout << bs << endl;
    cout << bs.count() << endl;
    cout << bs.any() << endl;
}

void test_lower_bound() {
    long a[10] = {1,2,4,6,8,13,21,31,32,44};
//    long a[10] = {};
    int idx = lower_bound(a, a+0, 13) - a;
    cout << idx << endl;

}

int main() {
    test_lower_bound();

    return 0;
}