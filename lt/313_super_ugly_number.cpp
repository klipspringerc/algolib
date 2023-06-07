//
// https://leetcode.com/problems/super-ugly-number/
//

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> nums(n);
        int m = primes.size();
        vector<int> idxs(m, 0);
        nums[0]=1;
        for (int i = 1; i<n; i++) {
            unsigned long long cur_min = INT_MAX;
            for (int j = 0; j < m; j++) {
                cur_min = min(cur_min, (unsigned long long)(nums[idxs[j]]) * primes[j]);
            }
            nums[i] = cur_min;
            for (int j = 0; j < m; j++) {
                if ((unsigned long long)(nums[idxs[j]]) * primes[j] == cur_min)
                    idxs[j]++;
            }
        }
        return nums[n-1];
    }
};

int main() {
    vector<int> primes = {2,3,5,7};
    Solution s;
    cout << s.nthSuperUglyNumber(5911, primes) << endl;

}