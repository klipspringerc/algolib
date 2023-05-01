//
// Returns error message of given requirement
// Given the position of err in the input text, contains the line of error, the line before it and after it
// Insert a line after the error line, contains `^` sign that points to the position of error
// At the same time, print at most Z character before & after the position of error, excluding the error position itself.
//


#include <string>
#include <iostream>
using namespace std;


string err_text_align(string & input, int pos, int z) {
    int lb, rb;
    int shift_count = 0;
    int nl_count = 0;
    int pointer_offset = 0;
    for (lb = pos; lb >= 0; lb--,shift_count++) {
        // omit if input[pos] itself is `\n`
        if (shift_count > 0) {
            if (input[lb] == '\n') {
                nl_count++;
                if (nl_count == 1) {
                    pointer_offset = shift_count-1;
                }
                if (nl_count == 2)
                    break;
            }
        }
        if (shift_count == z) {
            if (nl_count == 0)
                pointer_offset = pos-lb;
            break;
        }
    }
    if (nl_count > 1 && input[lb] == '\n')
        lb++;
    int err_line_end = pos;
    for (rb = pos, nl_count=0, shift_count=0; rb < input.length(); rb++,shift_count++) {
        if (input[rb] == '\n') {
            nl_count++;
            if (nl_count == 1)
                err_line_end = rb;
            if (nl_count == 2)
                break;
        }
        if (nl_count == 0)
            err_line_end = rb;
        if (shift_count == z) {
            break;
        }
    }
    string result;
    result += input.substr(lb, err_line_end-lb+1);
    if (input[err_line_end] != '\n')
        result += '\n';
    for (int i =0; i < pointer_offset; i++)
        result += ' ';
    result += "^\n";
    if (rb > err_line_end)
        result += input.substr(err_line_end+1, rb - err_line_end);
    return result;
}

int main() {
    string input = "int solution()\n    error position = 1;\n return 1;\n hee";
    string err_msg = err_text_align(input, 26, 2);
    cout << err_msg;
}