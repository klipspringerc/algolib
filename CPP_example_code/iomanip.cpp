#include <iostream>
#include <iomanip>
using namespace std;

int main (){
    double a[10];
    int i;
    for (i=0;i<10;i++) a[i] = (i+2)*(i+1)/3;
    
    cout<<fixed;
    cout.setf(ios_base::showbase);
    cout.precision(2);
    cout <<setfill('-') <<setw(10) <<left << a[7] << endl;
    cout <<setbase(16) << a[8] << endl;
    cout << a[9] << endl;
    
    return 0;
}