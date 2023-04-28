//
// https://leetcode.com/problems/pascals-triangle/
//

#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> results;
        vector<int> row;
        row.push_back(1);
        results.push_back(row);
        for (int n = 2; n <= numRows; n++) {
            vector<int> nrow;
            nrow.push_back(1);
            for (int i = 1; i < n-1; i++) {
                nrow.push_back(row[i-1] + row[i]);
            }
            nrow.push_back(1);
            results.push_back(nrow);
            row = nrow;
        }
        return results;
    }
    vector<int> getRow(int rowIndex) {
        vector<int> row;
        row.push_back(1);
        for (int n = 2; n <= rowIndex+1; n++) {
            vector<int> nrow;
            nrow.push_back(1);
            for (int i = 1; i < n-1; i++) {
                nrow.push_back(row[i-1] + row[i]);
            }
            nrow.push_back(1);
            row = nrow;
        }
        return row;
    }
    vector<int> getRowOOR(int rowIndex) {
        vector<int> results;
        if (rowIndex == 0) {
            results.push_back(1);
            return results;
        }
        int n = rowIndex;
        results.push_back(1);
        for (int i = 1; i <= rowIndex-1; i++) {
            if ( i > rowIndex / 2) {
                results.push_back(results[rowIndex-i]);
                continue;
            }
            long long int val = 1;
            // n * (n-1) * ... * (n-i+1)  /  i * (i-1) * ... *(1)
            for (int e = 0; e < i; e ++) {
                val *= (n-e);
                val /= (1+e);
            }
            results.push_back(int(val));
        }
        results.push_back(1);
        return results;
    }
};

int main() {
    Solution s;
//    vector<vector<int>> results = s.generate(5);
//    for (int i = 0; i < results.size(); i++) {
//        for (int j = 0; j < results[i].size(); j++)
//            printf("%d, ", results[i][j]);
//        printf("\n");
//    }

    vector<int> row = s.getRowOOR(33);
    for (int i = 0;  i < row.size(); i++) {
        printf("%d, ", row[i]);
    }
    printf("\n");
}