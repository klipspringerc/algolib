//
// https://leetcode.com/problems/lru-cache/
//

#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    class Node {
    public:
        int key;
        int val;
        Node * prev = nullptr;
        Node * next = nullptr;
        Node() : key(0), val(0){};
        Node(int k, int v) : key(k), val(v){};
    };
    int capacity_;
    int size = 0;
    Node * head = nullptr;
    Node * tail = nullptr;
    unordered_map<int, Node*> m;


    LRUCache(int capacity) {
        capacity_ = capacity;
    }

    int get(int key) {
        cout << "-----------" << endl;
        cout << "lookup " << key << endl;
        Node * ptr = head;
        cout << "head " << (head? head->key : -1) << " tail " << (tail? tail->key : -1) << endl;
        while (ptr) {
            cout << ptr->key << ", ";
            ptr = ptr->next;
        }
        cout << endl;
        cout << "-----------" << endl;
        if (m.find(key) == m.end())
            return -1;
        Node * n = m[key];
        if (n == tail) {
            return n->val;
        }
        Node *prev = n->prev, * next = n->next;
        if (n == head) {
            head = next;
        } else {
            cout << "found key " << key << " let " << prev->key << " point to " << next->key << endl;
            prev->next = next;
            cout << "; let " << next->key << " rev point to " << prev->key << endl;
            next->prev = prev;
        }
        tail->next = n; // tail would not be null if key exists
        n->next = nullptr;
        n->prev = tail;
        tail = n;

        return n->val;
    }

    void put(int key, int value) {
        Node * n;
        cout << "-----------" << endl;
        cout << "current size " << size <<  " cap " << capacity_ << " put " << key << " " << value << endl;
        Node * ptr = head;
        cout << "head " << (head? head->key : -1) << " tail " << (tail? tail->key : -1) << endl;
        while (ptr) {
            cout << ptr->key << ", ";
            ptr = ptr->next;
        }
        cout <<endl;
        if (m.find(key) != m.end()) {
            n = m[key];
            n->val = value;
            // already tail
            if (n == tail)
                return;
            Node *prev = n->prev, * next = n->next;
            if (n == head) {
                // if n is head, move head to next
                head = next;
            } else {
                // n not head, remove n between prev and next
                cout << "found key " << key << " let " << prev->key << " point to " << next->key;
                prev->next = next;
                cout << "; let " << next->key << " rev point to " << prev->key << endl;
                next->prev = prev;
            }
        } else {
            n = new Node(key, value);
            m[key] = n;
            if (size == capacity_) {
                // if size == cap, head must not be null
                Node * to_delete = head;
                cout << "deleting head " << to_delete->key << endl;
                m.erase(to_delete->key);
                head = head->next;
                if (head)
                    cout << "move head to " << head->key << endl;
                else
                    cout << "move head to null" << endl;
                delete to_delete;
            } else {
                size++;
            }
            if (head == nullptr) {
                // init fast path
                head = n;
                tail = n;
                size = 1;
                cout << "reinit with head " << key << endl;
                return;
            }
        }
        // if n is found but not already tail, or if n is newly created with non-empty list, add to tail
        tail->next = n;
        n->next = nullptr;
        n->prev = tail;
        tail = n;
    }
};

int main() {
    LRUCache *c = new LRUCache(2);
    c->put(1,1);
    c->put(2,2);
    cout << c->get(1) << endl;
    c->put(3,3);
    cout << c->get(2) << endl;
    c->put(4,4);
    cout << c->get(1) << endl;
    cout << c->get(3) << endl;
    cout << c->get(4) << endl;
}