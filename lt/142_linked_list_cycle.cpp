//
// https://leetcode.com/problems/linked-list-cycle-ii/
// Using floyd loop detection



//  Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };



class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *ptr1 = head, *ptr2 = head;
        // ptr2 move twice the distance each step, until they meetup at a node
        // if cycle exists, 2 pointers are guaranteed to meet
        if (head->next == nullptr)
            return nullptr;
        while (ptr2 && ptr2->next) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            if(ptr1 == ptr2)
                break;
        }
        if (ptr1 != ptr2)
            return nullptr;
        // from head to cycle start node: x
        // cycle start node to meetup node y
        // meetup node to start of cycle: z
        // then:
        // x + y = A     -- ptr1 travel distance
        // x + y + z + y = 2A    -- ptr2 travel distance
        // -> z + y = A
        // -> x == z
        ptr1 = head;
        int c = 0;
        // so now we move x steps from head to reach to cycle start node.
        // since x==z, ptr1 and ptr2 meetup again at the cycle start node.
        while (ptr1 != ptr2) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            c++;
        }
        return ptr1;
    }
};