//
// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
// Note that the getRandom should return number with probability in proportion to their occurrences
// Simpliest way is to put every number in the same vector, but how to maintain index?
// use linked-list as unordered_map's value, each list node contains one index.
// when remove element, simply pop the list as a stack
// when deleting a value from collection, remove value from vector and then move element at last position to the removed index
// each vector entry should contain a pointer to its node for fast index update.


#include <stack>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

class RandomizedCollection {
public:
    class Node {
    public :
        int val;
        int idx;
        Node *next;
        Node(int _v, int _idx): val(_v), idx(_idx), next(nullptr) {};
    };
    unordered_map<int, Node*> mapping;
    vector<Node*> entries;
    int size;
    RandomizedCollection() {
        size = 0;
        srand(time(0));
    }

    bool insert(int val) {
        bool exist = mapping.find(val) != mapping.end();

        Node * new_node = new Node(val, size);
        if (exist) {
            Node *cur_head = mapping[val];
            new_node->next = cur_head;
        }
        mapping[val] = new_node;
        if (size == entries.size())
            entries.push_back(new_node);
        else
            entries[size] = new_node;
        size++;
        return !exist;
    }

    bool remove(int val) {
        bool exist = mapping.find(val) != mapping.end();
        if (!exist)
            return false;
        Node *cur_node = mapping[val];
        Node *new_head = cur_node->next;
        if (new_head)
            mapping[val] = new_head;
        else
            mapping.erase(val);
        int idx = cur_node -> idx;
        if (idx != size-1) {
            Node *shuffle_node = entries[size-1]; // move the last node to now empty idx
            entries[idx] = shuffle_node;
            shuffle_node->idx = idx;
        }
        delete cur_node;
        size--;
        return exist;
    }

    int getRandom() {
        int idx = rand() % size;
        return entries[idx]->val;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main() {
    RandomizedCollection *obj = new RandomizedCollection();

    bool p1 = obj->insert(2);
    bool p2 = obj->insert(1);
    bool p3 = obj->insert(1);
    bool p4 = obj->remove(2);
    bool p5 = obj->remove(3);
    bool p6 = obj->insert(4);
    bool p7 = obj->insert(5);
    printf("%d %d %d %d %d %d\n", p1, p2, p3,p4, p5, p6);
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
    printf("%d\n", obj->getRandom());
}