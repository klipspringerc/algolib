//
// Created by Cui Shengping on 26/3/18.
//

#include <cstdio>
#include <vector>
#include <stack>
#define isOn(S, j) (S & (1 << j))
#define setBit(S, j) (S |= (1 << j))
#define clearBit(S, j) (S &= ~(1 << j))
#define toggleBit(S, j) (S ^= (1 << j))
#define lowBit(S) (S & (-S)) // get the last 1 of the binary form of S
#define setAll(S, n) (S = (1 << n) - 1)
#define modulo(S, N) ((S) & (N - 1))   // returns S % N, where N is a power of 2
#define isPowerOfTwo(S) (!(S & (S - 1)))
#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))
#define turnOffLastBit(S) ((S) & (S - 1))
#define turnOnLastZero(S) ((S) | (S + 1))
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define twurnOnLastConsecutiveZeroes(S) ((S) | (S - 1))

using namespace std;

void printSet(int bs) {
    stack<int> aux;
    while (bs) {
        aux.push(bs % 2);
        bs /= 2;
    }
    while (!aux.empty()) {
        printf("%d", aux.top());
        aux.pop();
    }
    printf("\n");
}

void build_in_bit_methods() {
    printf("count bit 30, %d \n", __builtin_popcount(30));
    printf("count bit 32, %d \n", __builtin_popcount(32));
    printf("trailing zero 30, %d \n", __builtin_ctz(30));
    printf("trailing zero 32, %d \n", __builtin_ctz(32));

}

int main() {
    int n = 7;
    printSet(n);
    printf("lowbit of %d: %d \n", n, lowBit(n));
    printSet(n);
    printSet(turnOnLastZero(n));
    build_in_bit_methods();
    return 0;
}
