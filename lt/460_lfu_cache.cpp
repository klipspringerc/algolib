//
// https://leetcode.com/problems/lfu-cache/description/
//
#include <unordered_map>
#include <iostream>
using namespace std;

class LFUCacheComplex {
public:
    class Node {
    private:
        int key;
        int val;
        int freq;
        Node * prev = nullptr;
        Node * next = nullptr;
        Node() : key(0), val(0), freq(0) {};
        Node(int k, int v) : key(k), val(v), freq(1) {};
    };
    int capacity_;
    int size = 0;
    Node * head = nullptr;
    Node * tail = nullptr;
    unordered_map<int, Node*> m;
    unordered_map<int, Node*> fheads; // map frequency f to first list node with frequency f
    unordered_map<int, Node*> ftails; // map frequency f to last list node with frequency f
    LFUCache(int capacity) {
        capacity_ = capacity;
    }

    int get(int key) {
        if (m.find(key) == m.end())
            return -1;
        Node * n = m[key];
        int f = n->freq;
        n->freq++;
        Node *prev = n->prev, * next = n->next;
        // maintain main list
        bool noop =false;
        bool tail = false;
        if (next && next->freq > f+1) {
            // fast path, no need to update position
            // do nothing
            noop = true;
        } else if (n == head) {
            head = next;
        } else if (n == tail) {
            tail = true;
        } else {
            prev->next = next;
            next->prev = prev;
        }
        // maintain freq head-tail mapping
        Node *curfhead = fheads[f];
        if (n == curfhead) {
            if (next->freq == f)
                fheads[f] = next;
            else {
                fheads.erase(f);
                ftails.erase(f);
            }
        }
        Node *curftail = ftails[f];
        if (n == curftail) {
            if (prev->freq == f)
                ftails[f] = prev;
            else {
                fheads.erase(f);
                ftails.erase(f);
            }
        }
        if (fheads.find(f+1) != fheads.end()) {
            Node *fhead = fheads[f+1];
            Node *prev = fhead->prev, * next = fhead->next;
            if (prev) {
                prev->next = n;
                n->prev = prev;
            }
            if (next) {
                next->prev = n;
                n->next = next;
            }
        } else {
            fheads[f+1] = n;
            ftails[f+1] = n;
            if (tail) {
                return n->val;
            }
            if (!noop) {
                ftail = ftails.find()
            }
        }
        fheads[f+1] = n;



        tail->next = n; // tail would not be null if key exists
        n->next = nullptr;
        n->prev = tail;
        tail = n;

        return n->val;
    }

    void put(int key, int value) {

    }
};

// since count increment by one each time, can use a vector index as count.
class LFUCache {
public:
    unordered_map<int,pair<int,int>> cache; // map[key] = {value,count}
    vector<deque<int>> counter; // one deque per count
    int max_size, num_elements;

    void increment_element(int key) {
        // increment cache counter
        cache[key].second++;
        // increase size of counter if necessary
        while (counter.size() <= cache[key].second)
            counter.push_back(deque<int>());
        // add a new element into the appropriate deque
        counter[cache[key].second].push_back(key);
    }

    void remove_LFU_element() {
        bool success = false;
        // start from the front of the counter
        for (int i = 0; i < counter.size() && !success; i++) {
            // start at the front of each deque
            while (!counter[i].empty() && !success) {
                // if this count is valid, delete the entry in the cache
                if (cache[counter[i].front()].second == i) {
                    success = true;
                    cache.erase(counter[i].front());
                    num_elements--;
                }
                counter[i].pop_front(); // delete invalid and 1st valid
            }
        }
    }

public:
    LFUCache(int c) {
        max_size = c;
        num_elements = 0;
        counter = {{}};
    }

    int get(int key) {
        // if not found, return -1
        if (cache.find(key) == cache.end())
            return -1;
        // count use
        increment_element(key);
        // return the value
        return cache[key].first;
    }

    void put(int key, int value) {
        // protect against capacity = 0
        if (max_size == 0) return;
        // if key exists
        if (cache.find(key) != cache.end()) {
            cache[key].first = value;
            increment_element(key);
            return;
        }
        // if at capacity
        if (num_elements == max_size)
            remove_LFU_element();
        // add the new key
        cache[key] = make_pair(value,0);
        counter[0].push_back(key);
        num_elements++;
    }
};


/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */