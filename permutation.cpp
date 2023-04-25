//
// Created by Shengping Cui on 2022/9/4.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
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

    void solution3() {
        int n = 4;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }

        do {
            for (int i = 0; i < n; ++i) {
                std::cout << v[i] << " ";
            }
            std::cout << "\n";
        } while (std::next_permutation(v.begin(), v.end()));
    }

    // by permutation on a boolean array (size n, only r of them is true)
    // we could obtain all combination of C_n_r by index selection on where bool element is true
    // this returns all ordered combination output indices
    void combination() {
        int n, r;
        std::cin >> n;
        std::cin >> r;

        vector<bool> v(n);
        fill(v.begin(), v.begin() + r, true);

        do {
            for (int i = 0; i < n; ++i) {
                if (v[i]) {
                    std::cout << (i + 1) << " ";
                }
            }
            std::cout << "\n";
        } while (prev_permutation(v.begin(), v.end()));
    }

    void practice_combination() {
        int r = 2;
        vector<bool> v(10, false);
        fill(v.begin(), v.begin()+r, true);
        vector<int> selection(r);
        int count = 0;
        do {
            int idx = 0;
            for (int i = 0; i < v.size(); i++) {
                if (v[i]) {
                    selection[idx] = i;
                    idx++;
                }
            }
            for (int i = 0; i < r; i++)
                printf("%d ", selection[i]);
            printf("\n");
            count++;
        } while(prev_permutation(v.begin(), v.end()));
        printf("\n total combination: %d\n", count);
    }

    void practice_permutation() {
        int n = 4;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i]= i;
        }
        int count = 0;
        do {
            for (int i = 0; i < n; i++) {
                printf("%d ", v[i]);
            }
            printf("\n");
            count++;
        } while (next_permutation(v.begin(), v.end()));
        printf("total permutation %d\n", count);
    }
};

int main() {
    Solution s;
    char input[] = "abcdef"; // would not work if declare as char * input, seems that char array would not be initialized properly this way
//    s.solution(input, 3);
//    s.solution2(input, 6);
//    s.combination();
    s.practice_permutation();
}
