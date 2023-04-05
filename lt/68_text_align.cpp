//
// https://leetcode.com/problems/text-justification/description/
// Greedy, insert according to spec.
// Read until reaching max width, then calculate extra spaces required.
// Modulo total space count for no. of uneven blanks.
//

#include <vector>
#include <string>
#include <cstdio>
using namespace std;



class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> results;
        int count = 1;
        int curWidth = words[0].length();
        for (int i = 1; i < words.size(); i++) {
            // each time, try greedy append 1 space & 1 word
//            printf("cur width %d, try word %s\n", curWidth, words[i].c_str());
            if (words[i].length() + 1 + curWidth <= maxWidth) {
//                printf("-->append, continue");
                count++;
                curWidth += (1 + words[i].length());
                continue;
            }
            // if cannot append more, compute current line.
            string line;
            int extraBlanks = maxWidth - curWidth;  // total number of spaces to be added
            if (count == 1) {
                // line contains only one word -> left justified
                 line.append(words[i-1]);
                for (int j = 0; j < extraBlanks; j++) {
                    line.push_back(' ');
                }
            } else {
                int widen = extraBlanks / (count-1); // number of additional spaces per blank
                int uneven = extraBlanks % (count-1); // number of uneven blanks with extra 1 space
                int printedUneven = 0;
                for (int j = 0; j < count-1; j++) {
                    line.append(words[i - count + j]);
                    for (int k = 0; k < widen+1; k++) {
                        line.push_back(' ');
                    }
                    // print extra 1 space for leftmost blanks
                    if (printedUneven < uneven) {
                        printedUneven++;
                        line.push_back(' ');
                    }
                }
                line.append(words[i-1]);
            }
            results.push_back(line);
            count = 1;
            curWidth = words[i].length();
        }
        if (count > 0) {
            string line = words[words.size() - count];
            for (int i = 1; i < count; i++) {
                line.push_back(' ');
                line.append(words[words.size() - count + i]);
            }
            for (int i = 0; i < maxWidth - curWidth; i++) {
                line.push_back(' ');
            }
            results.push_back(line);
        }
        return results;
    }
};

int main() {
    Solution s;
    vector<string> in = {
//            "This", "is", "an", "example", "of", "text", "justification."
//            "What","must","be","acknowledgment","shall","be"
            "Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"
    };
    vector<string> result = s.fullJustify(in, 15);
    for (int i = 0; i < result.size(); i++) {
        printf("%s|\n", result[i].c_str());
    }
}