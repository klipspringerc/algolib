//
// Remove duplicate nodes in sorted linked list.
//

#include <cstdlib>
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* ptr;
        ListNode* next;
        if (head == nullptr) {
            return head;
        }
        ptr = head;
        next = head->next;
        while (next != nullptr) {
            // compare current with next, if same, delete next and move; otherwise move both ptr and next
            if (ptr->val == next->val) {
                next = next->next;
                delete ptr->next;
                ptr->next = next;
            } else {
                ptr = ptr->next;
                next = next->next;
            }
        }
        return head;
    }
};

int main() {
    ListNode* l5 = new ListNode(3, nullptr);
    ListNode* l4 = new ListNode(3, l5);
    ListNode* l3 = new ListNode(2, l4);
    ListNode* l2 = new ListNode(1, l3);
    ListNode* l1 = new ListNode(1, l2);
    Solution s;
    ListNode * r = s.deleteDuplicates(l1);
    while (r) {
        printf(" %d", r->val);
        r = r->next;
    }
    printf("\n");
}