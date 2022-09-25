//
// https://leetcode.com/problems/remove-element/
// Created by KSC on 25/9/22.
//

#include <cstdio>
#include <vector>
using namespace std;


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int ptr = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[ptr] = nums[i];
                ptr++;
            }
        }
        return ptr;
    }
};

int main() {
    Solution s;
    vector<int> in = vector<int>{13,13,13,13,13,13};
    printf("first %d element: ", s.removeElement(in, 13));
    for (vector<int>::iterator itr = in.begin(); itr != in.end(); itr++) {
        printf("%d ", *itr);
    }
    printf("\n");
}