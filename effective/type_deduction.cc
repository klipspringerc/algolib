#include <iostream>
using namespace std;

// deduction on array size by template with by-reference parameter
template<typename T, std::size_t N> 
constexpr size_t get_array_size(T (&)[N]) {
    return N;
}

int array_size_by_tmpl() {
    int arr[10];
    cout << get_array_size(arr) << endl;
}

int main() {
    array_size_by_tmpl();
}



