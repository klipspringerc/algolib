//
// Created by Shengping Cui on 2023/4/25.
//

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    char filename[20];
    scanf("%s", filename);
    FILE *f, *fout;
    f = fopen(filename, "r");
    int num;
    vector<int> record;
    while(fscanf(f, "%d", &num) != EOF) {
        printf("%d ", num);
        record.push_back(num);
    }
    printf("\n");
    fclose(f);
    char outfile[20] = "out.txt";
    fout = fopen(outfile, "w");
    for (int i = 0; i < record.size(); i++) {
        fprintf(fout, "%d ", record[i]);
    }
    fprintf(fout, "\n");
    fflush(fout);
    fclose(fout);
}