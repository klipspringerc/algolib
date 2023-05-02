//
// https://leetcode.com/problems/merge-k-sorted-lists/description/
// Heap plus list merge

#include <queue>
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        class MaxNode {
            public:
            bool operator() (const ListNode * l, const ListNode* r) {
                return l-> val > r ->val;
            }
        };

        priority_queue<ListNode*, vector<ListNode*>, MaxNode> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i])
                pq.push(lists[i]);
        }
        ListNode * ptr;
        ListNode * head = nullptr;
        while (!pq.empty()) {
            ListNode * tnode = pq.top();
            pq.pop();
            if (head == nullptr) {
                head = tnode;
                ptr = head;
            } else {
                ptr->next = tnode;
                ptr = ptr->next;
            }

            if (tnode && tnode->next) {
                pq.push(tnode->next);
            }
        }
        return head;
    }
};