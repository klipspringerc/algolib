//
// Created by KSC on 29/4/23.
//


#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int  n = s.length();
        vector<vector<string>> results(n); // store sequence ending at string position i
        unordered_set<string> dict;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (const string & v : wordDict) {
            dict.insert(v);
        }
        for (int i = 0 ; i < n; i++) {
            if (i > 0 && results[i-1].size() == 0)
                continue;
            for (int j = i+1; j < n+1; j++) {
                string token = s.substr(i, j-i);
                bool valid = false;
                if (dp[i][j-1])
                    valid = (dp[i][j-1] == 1);
                if (dict.count(token) > 0) {
                    valid = true;
                    dp[i][j-1] = 1;
                } else {
                    dp[i][j-1] = 2;
                }
                if (valid) {
                    if (i == 0 ) {
                        results[j-1].push_back(token);
                    } else {
                        vector<string> cached = results[i-1];
                        for (int idx = 0; idx < cached.size(); idx++) {
                            results[j-1].push_back(cached[idx] + " " + token);
                        }
                    }

                }
            }
        }
        return results[n-1];
    }
};

int main() {
    Solution s;
    vector<string> dict = {
//            "cat","cats","and","sand","dog",
            "apple","pen","applepen","pine","pineapple"
    };
    vector<string> results =s.wordBreak("pineapplepenapple", dict);
    for (int i = 0; i < results.size(); i++) {
        cout << results[i] << endl;
    }
}