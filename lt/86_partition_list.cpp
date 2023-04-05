//
// https://leetcode.com/problems/partition-list/
//

#include <cstdio>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode * h1 = nullptr, * h2 = nullptr, * ptr1 = nullptr, * ptr2 = nullptr, * ptr; // nullptr need explicitly init
        ptr = head;
        while (ptr) {
            if (ptr->val < x) {
                if (h1 == nullptr) {
                    h1 = ptr;
                    ptr1 = ptr;
                } else {
                    ptr1->next = ptr;
                    ptr1 = ptr;
                }
            } else {
                if (h2 == nullptr) {
                    h2 = ptr;
                    ptr2 = ptr;
                } else {
                    ptr2->next = ptr;
                    ptr2 = ptr;
                }
            }
            ptr = ptr->next;
        }
        if (ptr2 != nullptr)
            ptr2->next = nullptr;
        if (h1 == nullptr)
            return h2;
        ptr1->next = h2;
        return h1;
    }
};

int main() {
    Solution s;
//    ListNode * l4 = new ListNode(1);
//    ListNode * l3 = new ListNode(2, l4);
//    ListNode * l2 = new ListNode(3, l3);
    ListNode * l2 = new ListNode(2);
    ListNode * l1 = new ListNode(4, l2);

//    ListNode * l1 = new ListNode(4);

    ListNode * r = s.partition(l1, 3);
    while (r) {
        printf(" %d", r->val);
        r = r->next;
    }
    printf("\n");
}