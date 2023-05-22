#include <iostream>
#include <bitset>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <atomic>
#include <vector>
#include <string>

#include "mp/io.h"
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

//void test_gets() {
//    char str[20];
//    while (gets(str) != NULL) {
//        int str_len = strlen(str);
//        printf("input length: %d last char %c \n", str_len, str[str_len - 1]);
//    }
//    while (gets(str) != NULL) {
//        while (strlen(str)) {
//            puts("receive line");
//            if (gets(str) == NULL)
//                break;
//        }
//        puts("process");
//    }
//}

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

void test_cstring() {
    char as[100] = "abcd" ;
    as[2] = '\0';
    char bs[20] = "efg";
    strcat(as, bs);
    puts("string concatenation result");
    puts(as);
}

int array_pointers()
{
/* let's make the arrays first                                             */
    int array_A[3] = {1, 2, 3};
    int array_B[3] = {4, 5, 6};
    int array_C[3] = {7, 8, 9};

/* now let's declare some pointers to such arrays:                          */
    int (*pA)[3] = &array_A;
    int (*pB)[3] = &array_B;
    int (*pC)[3] = &array_C;  /* notice the difference:                         */
/* int *pA[3] would be an array of 3 pointers to int because the [] operator*/
/* has a higher precedence than *(pointer) operator. so the statement would */
/* read: array_of_3 elements of type_pointer_to_int                         */
/* BUT, "int (*pA)[3]" is read: pointer_A (points to) type_array_of_3_ints! */

/* so now we need a different array to hold these pointers:                 */
/* this is called an_ARRAY_of_3_pointers to_type_array_of_3_ints            */
    int (*ARRAY[3])[3] = {pA, pB, pC};

/* along with a a double pointer to type_array_of_3_ints:                   */
    int (**PTR)[3] = ARRAY;

/* and check that PTR now points to the first element of ARRAY:             */
    if (*PTR == pA) printf("PTR points to the first pointer from ARRAY \n");

    PTR++;

    if (*PTR == pB) printf("PTR points to the second pointer from ARRAY! YAY!\n");

    return 0;
}


void lambda() {
    auto func = []() {
        cout <<"lambda out"<<endl;
    };
    func();

    auto r = [](double v) -> double {
        cout <<"lambda param" << v <<endl;
        return v;
    }(12);
    cout <<"returned " << r <<endl;

    long double num = 12.1f;
    // give lambda access to outer scope value by capture list
    // capture by value -> copy
    [num](double f) {

        cout << "val capture " << num * f << endl;
    }(2.0);

    cout << num << endl;

    // capture by value
    int base = 32;
    auto inc = [base] (int v) {
        cout << "capture by base value " << base << " result " << base + v << endl;
    };
    inc(16);
    base = 48;
    inc(16);  // second call still use base value 32


    // pass by reference
    [&num](double f) {
        cout << (num+=1) * f << endl;
    }(2.0);
    cout << num << endl;

    auto incr = [&base] (int v) {
        cout << "capture by base reference " << base << " result " << base + v << endl;
    };
    incr(16);
    base = 64;
    incr(16);  // second call use updated base value 64

    // capture all context
    [=](double f) {
        cout << num + f << endl;
    }(3.0);

    // capture all context by reference
    [&](double f) {
        cout << (num+=1) + f << endl;
    }(3.0);
    cout << num << endl;

}
class TS {
public:
    int id;
//    int id2;
//    char c;
//    char b;
//    long long lk;
//    double v;
//    long double lv;
//    double key;
//    double key2;
//    vector<int> history;
    TS(int _id) {
        id = _id;
    }
    TS(TS & a) {
        id = a.id;
//        history = a.history;
    }
    virtual int get_result(int mode)  {
        return id;
    }
};

// 4 byte
class TA {
public:
    int id;
    TS(int _id) {
        id = _id;
    }
    TS(TS & a) {
        id = a.id;
    }
};

// 16 byte, with virtual table pointer as the first field, which make the class 8-byte aligned
class TB {
public:
    int id;
    TS(int _id) {
        id = _id;
    }
    TS(TS & a) {
        id = a.id;
    }
    virtual int get_result(int mode)  {
        return id;
    }
};

void class_size() {
    TS t(1);
    cout << sizeof(long) <<endl;
    cout << sizeof(long long) <<endl;
    cout << sizeof(long double) <<endl;
//    cout << sizeof(vector<int>) <<endl;
    cout << sizeof(t) <<endl;
//    t.history.resize(231);
//    cout << sizeof(t) <<endl;
}

// no variable declaration, no for loop in constexpr
int factorial(int num) {
    return (num == 1)? 1 : num * factorial(num-1);
}

void num_limit () {
    // the type cast is necessary as the template result would still be uint32
    uint64_t r = uint64_t (numeric_limits<uint32_t>::max()) * numeric_limits<uint32_t>::max();
    cout << r << endl;
}


void size_alignment() {
    struct A {long x; long y;};  // 16 byte
    struct B {int x; int y; int z;}; // 12 byte
    struct C {long x; int y;}; // 16 byte, aligned to long
    struct D {long double a; int b;}; // 32 byte, aligned to long double (16byte)
    struct E {vector<int> a;}; // 24 byte
    struct F {vector<int> a; int b;}; // 32 byte, 8 byte aligned (vector as 3 8-byte field)
    struct G {long double a; double b; double c;}; // 32 byte, aligned to long double, but the 16 byte alignment can hold 2 double.
    struct H {long double a; char b; char c;}; // 32 byte, aligned to long double, the 16 byte alignment can hold multiple char.
    struct I {long double a; double b; double c; double d;}; // 48 byte, aligned to long double, so size increase by 16 byte
    struct J {long double a; vector<int> b;}; // 48 byte, aligned to long double, (vector==3 uint64_t)
    struct K {long double a; vector<int> b; long double c;}; // 64 byte, aligned to long double. vector (25byte) need 2*16=32 byte room
    struct L {long double a; vector<int> b; long double c; int* d;}; // 80 byte, aligned to long double. vector (25byte) need 2*16=32 byte room, pointer takes another 16 byte
    // class virtual method follows the same rule, but add a 8 byte virtual table pointer as the first element
    cout << sizeof(A) <<endl;
    cout << sizeof(B ) << endl;
    cout << sizeof(C ) << endl;
    cout << sizeof(D ) << endl;
    cout << sizeof(E ) << endl;
    cout << sizeof(F ) << endl;
    cout << sizeof(H) << endl;
    cout << sizeof(I) << endl;
    cout << sizeof(J) << endl;
    cout << sizeof(K) << endl;
    cout << sizeof(L) << endl;
    cout << "----" << endl;
    cout << sizeof(TS) << endl;

}

int main() {
//    constexpr auto r = factorial(4);
//    cout << r <<endl;
//    lambda();
//
//    string t = "abcd";
//    string s = t;
//    reverse(s.begin(), s.end());
//    cout << s << " "  << t << endl;


//    class_size();
//    int r = scgt_write();
//    test_lower_bound();
//    test_sizeof();
//    test_bitset();
//    test_print_str();
//    test_gets();
//    test_char();
//    if (is_big_endian()) {
//        printf("big endian\n");
//    } else {
//        printf("little endian\n");
//    }
//    test_cstring();
//    printf("%d\n" , (-27) % (8));

    return 0;
}