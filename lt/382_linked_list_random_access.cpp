//
// https://leetcode.com/problems/linked-list-random-node/description/
//

#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

/**
 * Definition for singly-linked list.
 */
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };


class Solution {
public:
    int size;
    ListNode * h;
    Solution(ListNode* head) {
        srand(time(0));
        h = head;
        ListNode * ptr = head;
        while (ptr) {
            size++;
            ptr = ptr->next;
        }
    }

    int getRandom() {
        int offset = rand() %size;
        ListNode *ptr = h;
        for (int i = 0 ; i < offset; i++) {
            ptr = ptr->next;
        }
        return ptr->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

int main() {


}