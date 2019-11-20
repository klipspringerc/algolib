//
// Created by Shengping Cui on 2019-09-16.
//

#include <cstdio>
#include <cstdlib>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL)
            return head;
        ListNode * tail, * cur;
        tail = head;
        cur = head;
        for (int i = 0; i < n; i++) {
            tail = tail->next;
            if (tail == NULL) {
                head = head->next;
                return head;
            }
        }
        while (tail != NULL) {
            cur = cur->next;
            tail = tail->next;
        }
        cur =  cur->next;
        return head;
    }
};

int main() {
    Solution s;
    printf("")
}
