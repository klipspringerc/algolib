//
// Return k-th largest element in input stream
//

#include <queue>
#include <vector>
using namespace std;

class KthLargest {
private:
    int size;
    int k;
    priority_queue<int, vector<int>, greater<int>> pq ; // min heap
public:
    KthLargest(int k, vector<int>& nums) {
        size = 0;
        this->k = k;
        for (int n : nums) {
            add(n);
        }
    }

    int add(int val) {
        if (size < k) {
            pq.push(val);
            size++;
        } else {
            int tv = pq.top();
            if (tv < val) {
                pq.pop();
                pq.push(val);
            }
        }
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

int main() {
    vector<int> init = {1,2,3,4,5};
    KthLargest kl (4, init);
    for ( int n = 6; n < 9; n++) {
        printf("after adding %d, kth: %d\n", n, kl.add(n));
    }
}