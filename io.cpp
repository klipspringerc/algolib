//
// Created by Shengping Cui on 2023/4/25.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void cppIO() {
    char filename[20];
    cin.getline(filename, 20);

    ifstream fin;
    fin.open(filename);
    int num;
    vector<int> record;
    while (fin >> num ) {
        printf("%d ", num);
        record.push_back(num);
    }

    ofstream fout;
    fout.open("output.txt");
    fout << "got result sum" <<endl;
    for (int i = 0; i < record.size(); i++) {
        fout << record[i] << " ";
    }
    fout << endl;
    fout.close();
}

int main() {
    cppIO();
    return 0;
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