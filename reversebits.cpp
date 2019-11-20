//
// Reverse the bits of a number
// by look up table
// Created by Shengping Cui on 2019-11-20.
//
#include <cstdio>
using namespace std;

// byte bits position 7,6,5,4,3,2,1,0
// reverse the bits at 0,1 to 7,6
#define L(n) n, n+2*64, n+1*64, n+3*64
// reverse the bits at 2,3 to 5,4
#define L2(n) L(n), L(n+2*16), L(n+1*16), L(n+3*16)
// reverse the bits at 4,5 to 3,2
#define L3(n) L2(n), L2(n+2*4), L2(n+1*4), L2(n+3*4)
// finally reverse the bits at 6,7 to 1,0
unsigned int lt[256] = { L3(0), L3(2), L3(1), L3(3) }; // bits reversal loop-up table for any byte

//assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main() {
    int num = 530;
    // reverse each byte and combine the bytes backwards
    int reverse_num = lt[num & 0xff] << 24 | lt[(num>>8) & 0xff] << 16 |
            lt[(num>>16) & 0xff] << 8 | lt[(num>>24) & 0xff];
    printf("reverse of number %u is %u \n", num, reverse_num);
    printBits(sizeof(num), &num);
    printBits(sizeof(reverse_num), &reverse_num);
}
