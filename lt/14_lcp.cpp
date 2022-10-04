//
// https://leetcode.com/problems/longest-common-prefix/description/
// only lowercase English letters, so vocabulary space for Trie is 26
// Created by KSC on 4/10/22.
//
#include <cstdio>
#include<string>
#include <vector>
using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        struct TrieNode *head = NewNode();
        for (vector<string>::iterator itr = strs.begin(); itr != strs.end(); itr++) {
            insert(head, *itr);
        }
        return find_lcp(head);
    }
    struct TrieNode {
        struct TrieNode *children[26];
        bool is_end;
    };
    struct TrieNode * NewNode() {
        struct TrieNode * node = new TrieNode; // new used to init struct
        for (int i = 0; i < 26; i++) {
            node->children[i] = nullptr;
        }
        node->is_end = false;
        return node;
    }
    void insert(struct TrieNode * root, string key) {
        struct TrieNode *p = root;
        for (int i = 0; i < key.size(); i++) {
            char c = key[i] - 97;
            if (!p->children[c]) {
                p->children[c] = NewNode();
            }
            p = p->children[c];
        }
        p->is_end = true;
    }

    string find_lcp(struct TrieNode * root) {
        string result = "";
        struct TrieNode * p = root;
        while (true) {
            char c;
            bool found = false;
            if (p->is_end) {
                return result;
            }
            for (int i = 0; i < 26; i++) {
                if (p->children[i]) {
                    if (found) {
                        // multiple match, LCP ends here
                        return result;
                    }
                    c = i + 97;
                    found = true;
                }
            }
            if (!found) {
                // end of words, lcp could not be longer than current result
                break;
            }
            result += c;
            p = p->children[c - 97];
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> input = {"", "abc", "abc"};
    string r = s.longestCommonPrefix(input);
    printf("lcp: %s\n", r.c_str());
}