//
// https://leetcode.com/problems/word-search/description/
// Solution:
// dfs search

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<bool> trace(board.size() * board[0].size(), false);
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    trace[i * n + j] = true;
                    if (recur(i, j, 0, word, board, trace))
                        return true;
                    trace[i * n + j] = false;
                }
            }
        }
        return false;
    }

    bool recur(int x, int y , int step, string word, vector<vector<char>>& board, vector<bool> & trace) {
        if (step == word.length()-1) {
            return true;
        }
        int m = board.size();
        int n = board[0].size();
        if (x > 0) {
            if (word[step+1] == board[x-1][y] && !trace[(x-1) * n + y]) {
                trace[(x-1) * n + y] = true;
                if (recur(x-1, y, step+1, word, board, trace))
                    return true;
                trace[(x-1) * n + y] = false;
            }
        }
        if (x < m-1) {
            if (word[step+1] == board[x+1][y] && !trace[(x+1) * n + y]) {
                trace[(x+1) * n + y] = true;
                if (recur(x+1, y, step+1, word, board, trace))
                    return true;
                trace[(x+1) * n + y] = false;
            }
        }
        if (y > 0) {
            if (word[step+1] == board[x][y-1] && !trace[x * n + (y-1)]) {
                trace[x * n + (y-1)] = true;
                if (recur(x, y-1, step+1, word, board, trace))
                    return true;
                trace[x * n + (y-1)] = false;
            }
        }
        if (y < n-1) {
            if (word[step+1] == board[x][y+1] && !trace[x * n + (y+1)]) {
                trace[x * n + (y+1)] = true;
                if (recur(x, y+1, step+1, word, board, trace))
                    return true;
                trace[x * n + (y+1)] = false;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<char>> in = {
            {'A', 'A'},
//            {'B'},
//            {'C'},
//            {'A','B','C','E'},
//            {'S','F','C','S'},
//            {'A','D','E','E'}
    };
    Solution s;
    printf("found: %s\n", s.exist(in, "AAA")? "true": "false");
}
