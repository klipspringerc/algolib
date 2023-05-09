//
// https://leetcode.com/problems/design-circular-deque/
//

#include <vector>
#include <algorithm>
using namespace std;

class MyCircularDeque {
public:
    vector<int> nums;
    int l, r, size; // l point to first element, r point to one after first element
    int len;
    // how to determine deque empty or full? active maintain variable

    MyCircularDeque(int k) {
        nums.resize(k);
        l = 0; // point to the current front
        r = 0; // point to the next index of insert last
        len = 0;
        size = k;
    }

    int prev(int idx) {
        return (idx-1 + size) % size;
    }
    int next(int idx) {
        return (idx + 1) % size;
    }

    bool insertFront(int value) {
        if (isFull())
            return false;
        l = prev(l);
        nums[l] = value;
        len++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull())
            return false;
        nums[r] = value;
        r = next(r);
        len++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty())
            return false;
        l = next(l);
        len--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty())
            return false;
        r = prev(r);
        len--;
        return true;
    }

    int getFront() {
        if (isEmpty())
            return -1;
        int v = nums[l];
        return v;
    }

    int getRear() {
        if (isEmpty())
            return -1;
        int v = nums[prev(r)];
        return v;
    }

    bool isEmpty() {
        return (len == 0);
    }

    bool isFull() {
        return (len == size);
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

int main() {
    MyCircularDeque d(3);
    d.insertLast(1);
    d.insertLast(2);
    d.insertFront(3);
    d.insertFront(4);
}
