//
// https://leetcode.com/problems/poor-pigs/
//

#include <iostream>
#include <cmath>
using namespace std;


class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int attempt = minutesToTest/minutesToDie;
        int count = log(double(buckets))/log(double(attempt+1));
        if (pow(attempt+1, count) < buckets)
            count++;
        return count;
    }
};


int main() {
    Solution s;
    cout << s.poorPigs(122, 1,4) <<endl;
}