//
// https://leetcode.com/problems/group-anagrams/
// Group all anagrams together
// Solution: encode char composition via ordered map / sort, resulting code would identify unique anagram

#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> results;
        unordered_map<string, int> code_to_result_idx;
        for (int i = 0; i < strs.size(); i++) {
            string code = strs[i];
            sort(code.begin(), code.end());
            // can use char array as an ordered map, or sort to create unique code for each anagram
//            map<char, int> char_map;
//            for (int j = 0; j < strs[i].length(); j++) {
//                char_map[strs[i][j]]++;
//            }
//            string code;
//            for (const pair<char, int> & kv : char_map) {
//                code.push_back(kv.first);
//                code.push_back('0' + kv.second);
//            }
            if (code_to_result_idx.count(code) > 0) {
                // seen code, add to existing result array.
                int result_idx = code_to_result_idx[code];
                results[result_idx].push_back(strs[i]);
            } else {
                // new code, append to result vector and record the result index of this code
                code_to_result_idx[code] = results.size();
                results.push_back(vector<string>{strs[i]});
            }
        }
        return results;
    }
};

int main() {
    Solution s;
    vector<string> input = {"", "a", "b", ""};
    vector<vector<string>> results = s.groupAnagrams(input);
    printf("results: ");
    for (int i = 0; i < results.size(); i++) {
        printf("\n  ");
        for (int j = 0; j < results[i].size(); j++) {
            printf("%s, ", results[i][j].c_str());
        }
    }
}