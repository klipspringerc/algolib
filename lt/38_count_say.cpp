//
// https://leetcode.com/problems/count-and-say/
// Created by KSC on 25/9/22.
//

#include<cstdio>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        vector<int> v = vector<int>(1,1);
        vector<int> tmp;
        int s = 1;

        if (n == 1) {
            return "1";
        }
        for (int itr = 1; itr < n; itr++) {
            int cur = v[0];
            int count = 1;
            int tmp_size = 0;
            for (int i = 1; i < s; i++) {
                if (v[i] == cur) {
                    count++;
                } else {
                    tmp.push_back(count);
                    tmp.push_back(cur);
                    count = 1;
                    cur = v[i];
                    tmp_size += 2;
                }
            }
            tmp.push_back(count);
            tmp.push_back(cur);
            tmp_size += 2;
            v.clear();
            for (int i = 0; i < tmp_size; i++) {
                v.push_back(tmp[i]);
            }
            tmp.clear();
            s = tmp_size;
        }
        string result = "";
        for (int i = 0; i < s; i++) {
            result += to_string(v[i]);
        }
        return result;
    }
};

int main() {
    Solution s;
    for (int n = 1; n < 31; n++) {
        printf("%d: result: %s \n", n, s.countAndSay(n).c_str());
    }
};