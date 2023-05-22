//
// Created by SG0014000445M on 2023/5/19.
//


#include <type_traits>
#include <memory>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

//typedef std::shared_ptr<Foo> SharedFoo;

template <class T>
class Foo {
public:
    void getValue(T param) {
        printf("normal template!\n");
        cout << param <<endl;
    }


    void out() {cout << "base function" << endl;};
};

template<>
template <typename S> void Foo::getValue(shared_ptr<S> param) {
    printf("shared pointer!\n");
    cout << *param << endl;
}

// partial specialization this way would not work. treated as separate definition
//template <typename S>
//class Foo<shared_ptr<S>> {
//public:
//    void getValue(shared_ptr<S> param) {
//        printf("shared pointer!\n");
//        cout << *param << endl;
//    }
//};

int main() {
    Foo<shared_ptr<string>> fs;
    Foo<int> fi;
    fs.out();
    fi.out();
    fs.getValue(make_shared<string>("abc"));
    fi.getValue(123);
    return 0;
}