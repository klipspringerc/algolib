#include <cstdio>
#include <iostream>
#define SIZE 1299709
using namespace std;
int main(){
    bool a[SIZE] = {0};
    int i,num;
    a[1] = true;
    a[0] = true;
    for (i = 4; i<SIZE; i+=2)
        a[i] = true;
    for (i = 3; i*i<SIZE;i++ ){
        if (a[i] == false){
            num = i*i;
            while (num < SIZE){
                a[num] = true;
                num += i;
            }
        }
    }
    
    int s,e;
    int ans[500000],j=0;
    while (true){
        cin >> num;
        if (num == 0)
            break;
        s = num;
        e = num;
        while (a[s])
            s--;
        while (a[e])
            e++;
    
        ans[j] = e - s;
        j++;
    }
    
    for (i = 0; i < j; i++)
        printf("%d\n",ans[i]);

    return 0;
}