//
// https://leetcode.com/problems/implement-stack-using-queues/
//


#include <queue>
#include <cstdio>
#include <stack>
using namespace std;

// implement stack using queue
class MyStack {
public:
    queue<int> q;
    queue<int> bq;
    MyStack() {

    }

    void push(int x) {
        q.push(x);
    }

    int pop() {
        int r;
        while (!q.empty()) {
            r = q.front();
            q.pop();
            if (q.size() > 0)
                bq.push(r);
        }
        bq.swap(q);
        return r;
    }

    int top() {
        int r;
        while (!q.empty()) {
            r = q.front();
            q.pop();
            bq.push(r);
        }
        bq.swap(q);
        return r;
    }

    bool empty() {
        return q.empty();
    }
};


/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// suitable for read heavy
class BetterSolution {
public:
    queue<int> q;
    BetterSolution() {}
    void push(int v) {
        q.push(v);
        // must rotate  at each input to guarantee reverse order
        for (int i = 0; i < q.size()-1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    int pop() {
        int r = q.front();
        q.pop();
        return r;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

// now implement queue using stack
class MyQueue {
public:
    stack<int> s;
    stack<int> bs;
    MyQueue() {

    }

    void push(int x) {
        s.push(x);
    }

    int pop() {
        while (!s.empty()) {
            bs.push(s.top());
            s.pop();
        }
        int r = bs.top();
        bs.pop();
        while (!bs.empty()) {
            s.push(bs.top());
            bs.pop();
        }
        return r;
    }

    int peek() {
        while (!s.empty()) {
            bs.push(s.top());
        }
        int r = bs.top();
        while (!bs.empty()) {
            s.push(bs.top());
            bs.pop();
        }
        return r;
    }

    bool empty() {

    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


int main() {
}