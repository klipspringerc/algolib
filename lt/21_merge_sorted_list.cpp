//
// https://leetcode.com/problems/merge-two-sorted-lists/
// Created by KSC on 25/9/22.
//

#include <cstdio>
#include <cstdlib>
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode * head = nullptr;
        ListNode * cur, * prev = nullptr; // prev is necessary to link between 2 iterations without separate initialization on cur
        ListNode * p1 = list1;
        ListNode * p2 = list2;
        while (p1 || p2) {
            bool term = false;
            if (!p1) {
                cur = p2;
                p2 = p2->next;
                term = true;
            }
            else if (!p2) {
                cur = p1;
                p1 = p1->next;
                term = true;
            }
            else {
                if (p1->val > p2 -> val) {
                    cur = p2;
                    p2 = p2->next;
                } else {
                    cur = p1;
                    p1 = p1->next;
                }
            }
            if (prev) {
                prev->next = cur;
            }
            if (!head) {
                head = cur;
            }
            prev = cur;
            if (term) {
                break;
            }
        }
        return head;
    }
};

void print_ll(ListNode* head) {
    while (head) {
        printf("%d ->" , head->val);
        head = head->next;
    }
}

int main() {
//    ListNode l4 = ListNode(7);
    ListNode l3 = ListNode(4, nullptr);
    ListNode l2 = ListNode(3, &l3);
    ListNode l1 = ListNode(1, &l2);


//    ListNode l14 = ListNode(7);
    ListNode l13 = ListNode(4, nullptr);
    ListNode l12 = ListNode(2, &l13);
    ListNode l11 = ListNode(1, &l12);

    Solution s;
    ListNode * r = s.mergeTwoLists(&l1, &l11);
    print_ll(r);
}
