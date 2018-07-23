#include <iostream>
#include <bitset>
#include <climits>
#include <algorithm>
#include <string>
using namespace std;


// sizeof on array parameter would return the size of 'int *' instead of 'int []' or 'int[N]'
void get_size(int arr[100]) {
// actually compiler would generate warning for this
//    cout << sizeof(arr) << endl;
}

void test_sizeof() {
    char carr[100];
    int iarr[100];
    int * piarr = (int *) malloc(sizeof(int) * 100);
    cout << sizeof(int) << endl;
    cout << sizeof(bool) << endl;
    cout << sizeof(char) << endl;
    cout << sizeof(short) << endl;
    cout << sizeof(carr) << endl;
    cout << sizeof(iarr) << endl;
    cout << sizeof(piarr) << endl;
    // seems no difference between sizeof(var) and size of var
    // but cannot sizeof(type)

    // below two are equivalent
    memset(piarr, -1, 100 * sizeof(int));
    memset(iarr, -1, sizeof iarr);
//    for (int i = 0; i < 100; i++)
//        cout << piarr[i] << " ";
//    cout << endl;
//    for (int i = 0; i < 100; i++)
//        cout << iarr[i] << " ";
//    cout << endl;
    get_size(piarr); // sizeof behaviour for function array parameters
}

void test_bitset() {
    bitset<8> bs (0xA4);
    cout << bs << endl;
    bs.flip(3);
    cout << bs << endl;
    cout << bs.count() << endl;
    cout << bs.any() << endl;
}

void test_print_str() {
    char hstr[]= "hello world";
    printf("%s \n", ((string)hstr).c_str());
}

void test_lower_bound() {
//    long a[10] = {1,2,4,6,8,13,21,31,32,44};
//    long a[10] = {};
    long a[6] = {0,3,1,6,10,5};
    int idx = lower_bound(a, a+5, 5) - a;
    cout << idx << endl;
}

void test_gets() {
    char str[20];
    while (gets(str) != NULL) {
        int str_len = strlen(str);
        printf("input length: %d last char %c \n", str_len, str[str_len - 1]);
    }
}

int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

void test_char() {
    char a = 'A';
    if (a == 65 && 'a' == 97) {
        printf("remember it\n");
    }
    printf("char max %d\n", CHAR_MAX);
}

int main() {
//    test_lower_bound();
//    test_sizeof();
//    test_bitset();
//    test_print_str();
//    test_gets();
    test_char();
    if (is_big_endian()) {
        printf("big endian\n");
    } else {
        printf("little endian\n");
    }
    return 0;
}