//
// Created by Shengping Cui on 2022/9/4.
//

#include <cstdio>
#include <cstdlib>
using namespace std;

class Solution {
public:
    void solution(char input[], int len) {
        bool * visit = (bool *)malloc(sizeof(bool) * len);
        char *output = (char *)malloc(sizeof(char) * (len+1));
        output[len] = '\0';
        for (int i = 0; i < len; i++) {
            visit[i] = false;
        }
        recur_print(input, len, visit, 0, output);
    }

    void recur_print(char input[], int len, bool visited[], int step, char output[]) {
        if (step == len){
            printf("%s\n", output);
            return;
        }
        for (int i = 0; i < len; i++) {
            if (visited[i]) {
                continue;
            } else {
                visited[i] = true;
                output[step] = input[i];
                recur_print(input, len, visited, step + 1, output);
                visited[i] = false;
            }
        }
    }

    void solution2(char input[], int len) {
        recur2(input, len, 0);
    }

    void recur2(char input[], int len, int step) {
        if (step == len - 1) {
            printf("%s\n", input);
            return;
        }
        for (int i = step; i < len; i++) {
            swap(input, step, i);
            recur2(input, len, step+1);
            swap(input, i, step);
        }
    }

    static void swap(char arr[], int i, int j) {
        if (i != j) {
            char tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
};

int main() {
    Solution s;
    char input[] = "abcdef"; // would not work if declare as char * input, seems that char array would not be initialized properly this way
//    s.solution(input, 3);
    s.solution2(input, 6);
}
