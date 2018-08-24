//
// Created by KevinCui on 15/8/18.
//

#include <cstdio>
#include <cstring>
using namespace std;

#define D 540
int num;

short max[110][550];
short min[110][550];
int input[110];
short one[550];

int count;

// multiply b to a big integer a and store resulting big integer in r
void big_mul(short r[], short a[], int b) {
    int carry = 0;
    for (int i = 0; i < D; i++) {
        int mul = a[i] * b + carry;
        r[i] = mul % 10;
        carry = 0;
        if (mul < -9 || mul > 9) {
            carry = mul / 10;
        }
    }
}

int comp(short a[], short b[]) {
    for (int i = D; i > -1; i--) {
        if (a[i] == b[i])
            continue;
        return (a[i] > b[i])? 1 : -1;
    }
    return 0;
}

int comp_zero(short a[]) {
    for (int i = 0; i < D; i++)
        if (a[i] != 0)
            return (a[i] > 0)? 1 : -1;
    return 0;
}

void print_out(short a[]) {
    int head = D;
    for (head = D; head > 0; head--) {
        if (a[head])
            break;
    }
    for (int i = head; i > -1; i--)
        printf("%d", a[i]);
    printf("\n");
}

int main() {
    one[0] = 1;
    while (scanf("%d", &num) == 1) {
        count = 1;
        memset(max, 0, sizeof max);
        memset(min, 0, sizeof min);
        memset(input, 0, sizeof input);
        while (num != -999999) {
            input[count++] = num;
            scanf("%d", &num);
        }
        int cmp;
        for (int i = 1; i < count; i++) {
            if (input[i] > 0) {
                cmp = comp_zero(max[i-1]);
                if (cmp == 1) {
                    big_mul(max[i], max[i-1], input[i]);
                } else  {
                    big_mul(max[i], one, input[i]);
                }
                cmp = comp_zero(min[i-1]);
                if (cmp != -1) {
                    big_mul(min[i], one, input[i]);
                } else {
                    big_mul(min[i], min[i-1], input[i]);
                }
            } else if (input[i] < 0) {
                cmp = comp_zero(min[i-1]);
                if (cmp == -1) {
                    big_mul(max[i], min[i-1], input[i]);
                } else  {
                    big_mul(max[i], one, input[i]);
                }
                cmp = comp_zero(max[i-1]);
                if (cmp == 1) {
                    big_mul(min[i], max[i-1], input[i]);
                } else {
                    big_mul(min[i], one, input[i]);
                }
            }
        }
        int max_idx = 1;
        for (int i = 2; i < count; i++) {
            if (comp(max[i], max[max_idx]) == 1)
                max_idx = i;
        }
        print_out(max[max_idx]);
    }

}

