//
// Created by Cui Shengping on 2020/3/29.
// https://leetcode.com/problems/swap-nodes-in-pairs/
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <cstdio>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* cur = head;
        ListNode* swapped_tail;
        bool root = true;
        while(cur != nullptr && cur->next != nullptr) {
            cur = swapWork(cur);
            if (root) {
                head = cur;
                root = false;
            } else {
                swapped_tail->next = cur;
            }
            swapped_tail = cur->next;
            cur = cur->next->next;
        }
        return head;
    }

    ListNode* swapWork(ListNode* ptr) {
        ListNode* suc = ptr->next;
        if (suc == nullptr) {
            return ptr;
        }
        ListNode * tail = suc->next;
        suc->next = ptr;
        ptr->next = tail;
        return suc;
    }
};

void printList(ListNode *head) {
    ListNode *ptr = head;
    while (ptr != nullptr) {
        printf("%d -> ", ptr->val);
        ptr = ptr->next;
    }
    printf("tail \n");
    return;
}

int main() {
    ListNode l1 = ListNode(1);
    ListNode l2 = ListNode(2);
    ListNode l3 = ListNode(3);
    ListNode l4 = ListNode(4);
    l1.next = &l2;
    l2.next = &l3;
    l3.next = &l4;
    printList(&l1);

    Solution s;
    ListNode* res = s.swapPairs(&l1);
    printList(res);
    return 0;
}