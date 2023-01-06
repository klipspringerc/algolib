//
// https://leetcode.com/problems/rotate-list/description/
// Solution: rotate count exceeding list length has no meaning, so modulo is useful
// link the end of list to head, then reposition head to n-k position, break link pointing to head

#include <cstdio>

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode * ptr = head;
        ListNode * tail;
        ListNode * prev;
        int length = 0;
        while (ptr) {
            length++;
            if (ptr->next == nullptr) {
                tail = ptr;
            }
            ptr = ptr->next;
        }
        k = k % length;
        if (k == 0) {
            return head;
        }
        // reposition head based on k modulo n
        ptr = head;
        tail->next = head;
        prev = tail;
        for (int i = 0; i < length - k; i++) {
            ptr = ptr->next;
            prev = prev->next;
        }
        prev->next = nullptr;
        return ptr;
    }
};


void printList(ListNode* head) {
    while(head) {
        printf("%d", head->val);
        if (head->next) {
            printf(" -> ");
        } else {
            printf("\n");
            return;
        }
        head = head->next;
    }
}

int main() {
    Solution s;
    ListNode c(3);
    ListNode b(2, &c);
    ListNode a(1, &b);
    ListNode * r = s.rotateRight(&a, 5);
    printList(r);

}