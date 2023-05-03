// https://leetcode.com/problems/palindrome-pairs/description/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> results;
        unordered_map<string, int> revs;
        int empty_idx = -1;
        vector<int> pal_idx;
        // first store the reverse (mirror) of each word in map to index
        for (int i = 0; i < n; i++) {
            string curs = words[i];
            if (curs.length() == 0)
                empty_idx = i;
            else if (check_pal(words[i])) {
                pal_idx.push_back(i);
            }
            reverse(curs.begin(), curs.end());
            revs[curs] = i;
            
        }
        if (empty_idx > -1) {
            for (int idx : pal_idx) {
                results.push_back({idx, empty_idx});
                results.push_back({empty_idx, idx});
            }
        }
        for (int i = 0; i < n; i++) {
            if (revs.count(words[i]) > 0) {
                int idx = revs[words[i]];
                if (idx != i) {
                    results.push_back({i, idx});
                }
            }
            // split each string to <left | right> part
            // lookup the reverse map, if there's another word that mirrors left/right
            // if another word mirrors left part, and right part is itself a palindrome, then
            // <left | right(is_palin) | mirror_left>  must be a palindrom
            // vise verca, <mirror_right | left(is_palin) | right> 
            for (int j = 1; j < words[i].length(); j++) {
                string left = words[i].substr(0, j);
                string right = words[i].substr(j);
                if (revs.count(left) > 0 && check_pal(right)) {
                    int idx = revs[left];
                    if (idx != i)
                        results.push_back({i, idx});
                }
                if (revs.count(right) > 0 && check_pal(left)) {
                    int idx = revs[right];
                    if (idx != i)
                        results.push_back({idx, i});
                }
            }
        }
        return results;
    }

    bool check_pal(string s) {
        if (s.length() == 1) {
            return true;
        }
        int l = 0, r = s.length()-1;
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }
};