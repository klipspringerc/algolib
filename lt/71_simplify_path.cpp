//
// Created by SG0014000445M on 2023/1/17.
//

#include <string>
#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string result;
        vector<string> comps;
        int last = 0; // points to last '/' first char is guaranteed `/`
        int pos = 0; // push position in comps, the position may change by '..'

        // parse string, ignore consecutive '/', handle '.' and '..'
        for (int i = 1; i < path.length(); i++) {
            if (path[i] == '/' || i == path.length()-1) {
                if (i == path.length()-1 && path[i] != '/') {
                    i++;
                }
                if (i - last > 1) {
                    string tmp = path.substr(last+1, i-last-1);
//                    printf("tmp: %s\n", tmp.c_str());
                    last = i;
                    if (tmp == ".") {
                        continue;
                    } else if (tmp == "..") {
                        if (pos>0) {
                            pos--;
                        }
                        continue;
                    }
//                    printf("start adding %s to position %d, comps size %lu\n", tmp.c_str(), pos, comps.size());
                    if (comps.size() <= pos) {
                        comps.push_back(tmp);
                    } else {
                        comps[pos] = tmp;
                    }
                    pos++;
//                    printf("added component %s, size %lu, pos %d\n", comps[pos-1].c_str(), comps.size(), pos);
                }
                last = i;
            }
        }
        if (pos == 0) {
            return "/";
        }
        for (int i = 0; i < pos; i++) {
            result.push_back('/');
            result.append(comps[i]);
        }
        return result;
    }
};

int main() {
    Solution s;
    printf("result %s\n", s.simplifyPath("/../a/b.././..../.././../c").c_str());
};