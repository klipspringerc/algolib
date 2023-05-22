//
// Created by Cui Shengping on 2023/5/17.
//

#include <thread>
#include <atomic>
#include <iostream>
#include <memory>
#include <unordered_map>
using namespace std;

template <typename T>
T add (T a, T b) {
    return a + b;
}

template int add(int a, int b);


template<typename T>
class SPP{
    struct PCB {
        T * addr;
        atomic<uint64_t> ref {1};
        PCB(): addr(nullptr) {}
        PCB(T * _addr): addr(_addr) {}
    };
private:
    T* addr;
    PCB * pcb;
    static unordered_map<uint64_t, bool> gm; // global map

public:
    SPP() {
        addr = nullptr;
        pcb = nullptr;
    }
    explicit SPP(T *v): addr(v) {
        addr = v;
        pcb = new PCB(v);
        uint64_t  key = ((uint64_t) v);
        if (gm.find(key) != gm.end())
            cout << "duplicate address detected by global table" << endl;
        atomic<uint64_t> nv(1);
        gm[key] = true;
        cout << "pointer constructor called on addr " << addr << endl;
    }
    void set(T * v) {
        addr = v;
        cout << "set called with address assigned " << addr <<endl;
        pcb = new PCB(v);
    }
    SPP(const SPP<T> & sp): addr(sp.addr), pcb(sp.pcb) {
        pcb->ref+=1;
        cout << "copy constructor called on" << addr << ", pcb ref now is " << pcb->ref << endl;
    }

    SPP(SPP<T> && sp): addr(sp.addr), pcb(sp.pcb) {
        sp.addr = nullptr;
        sp.pcb = nullptr;
        cout << "move constructor called on" << addr << ", pcb ref now is " << pcb->ref << endl;
    }

    T operator*() {
        cout << "operator overload * invoked" <<endl;
        return *pcb->addr;
    }

    T* operator->() {
        return addr;
    }

    void operator=(const SPP<T> & sp) {
        if (addr) {
            _cleanup();
        }
        addr = sp.addr;
        pcb = sp.pcb;
        pcb->ref+=1;
        cout << "assignment operator called on " << addr << ", pcb ref now is " << pcb->ref << endl;
    }

    void operator=(SPP && sp) {
        if (addr) {
            _cleanup();
        }
        addr = sp.addr;
        pcb = sp.pcb;
        sp.addr = nullptr;
        sp.pcb = nullptr;
        cout << "move assignment operator called on " << addr << ", pcb ref now is " << pcb->ref << endl;
    }

     friend ostream & operator<<(ostream & os, const SPP<T> & sp) {
        os << sp.addr;
        return os;
    }

    void _cleanup() {
        uint64_t cur_ref = pcb->ref.load();
        cout << "cleanup invoked with current addr " << addr << " ref " << cur_ref <<  endl;
        uint64_t new_ref = cur_ref-1;
        while (true) {
            if (pcb->ref.compare_exchange_weak(cur_ref, new_ref)) {
                cout << "ref decreased to  " << new_ref << endl;
                if (new_ref==0) {
                    cout << "ref is now zero, delete memory" << endl;
                    if (pcb->ref == 0)
                        delete pcb->addr;
                    delete pcb;
                }
                break;
            } else {
                cur_ref = pcb->ref.load();
                new_ref = cur_ref-1;
            }
        }
        addr = nullptr;
        pcb = nullptr;
    }

    T & operator[](int idx) {
        return *(addr + idx);
    }

    ~SPP() {
        if (!pcb && !addr) {
            cout << "destructor invoked with empty ref " <<  endl;
            return;
        }
        cout << "destructor invoked" <<  endl;
        _cleanup();
    }
};

template <typename T>
SPP<T> makeSPP(T* ptr) {
    return SPP<T>(ptr);
}

template <typename T>
void atconv(T* ptr) {
    atomic<T *> ap;
    ap.store(ptr);
    cout << ap.load() << " " << *ap.load() << endl;
}

// ensure static member creation
template <typename T>
unordered_map<uint64_t, bool> SPP<T>::gm;

SPP<int> get_shared_ptr(int &v) {
    return SPP<int>(&v);
}

void receive_sp(SPP<int> sp) {
    SPP<int> local = sp;
    return;
}

struct ts {
    int val;
    ts():val(0){};
    ts(int v) : val(v){};
};



int main() {

//    atomic<int *> ap;
    int * v = new int(132);
//    ap.store(v);
    SPP<int> sp(new int[10]{1,20,1});
    cout << sp[0] << sp[1] << endl;
    sp[1] = 2;
    cout << sp[0] << sp[1] << endl;
    int m = 19;
//    atconv<int>(v);
//    cout << *ap.load()<<endl;
//    uint64_t num_addr = (uint64_t)v;
//    cout << * (int *) num_addr << endl;
    SPP<ts> t (new ts);
    t->val = 15;
//    SPP<int> t(new int(13));
//    SPP<int> t = makeSPP<int>(new int(13));
    SPP<ts> d(new ts(16));
    cout << d->val << endl;
    d = t;
    int v2 = 14;
//    t = SPP<int>(v); // this would trigger move assignment since rvalue
//    t = v;
//    receive_sp(t);
//    SPP<int> f(get_shared_ptr(v2));
//    shared_ptr<int> spp = shared_ptr<int>(v);
    cout << "int address: " << v <<endl;
    cout << "spp address: " << t <<endl;
//    t = v;
//    d = v;
//    cout << *t << endl;
    cout << t->val << endl;
    cout << d->val << endl;
}
