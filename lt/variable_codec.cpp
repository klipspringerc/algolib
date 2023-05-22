//
// Created by KSC on 22/5/23.
// variable length encoding scheme
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<uint8_t> codes;
    codes.push_back(1);
    codes.push_back( 14 | (1 << 7));
//    codes.push_back(1);
    codes.push_back(102 | (1 << 7));
    int val = 0;
    for (int i = 0; i < codes.size(); i++) {
        if (i == 0) {
            val += int(codes[i]);
            continue;
        }
        if (codes[i] & (1<<7)) {
            val *= 128;

            val += (codes[i] &= ~(1<<7));

        } else {
            break;
        }
    }
    cout <<val <<endl;
}