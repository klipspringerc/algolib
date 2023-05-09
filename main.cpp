#include <iostream>
#include <bitset>
#include <cstdio>
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
//    while (gets(str) != NULL) {
//        int str_len = strlen(str);
//        printf("input length: %d last char %c \n", str_len, str[str_len - 1]);
//    }
    while (gets(str) != NULL) {
        while (strlen(str)) {
            puts("receive line");
            if (gets(str) == NULL)
                break;
        }
        puts("process");
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


int main() {
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
    printf("%d\n" , (-1 + 8) % (8));

    return 0;
}