#include <iostream>

using namespace std;

class Solution {

    void deleteSpaces(string &s) {
        int len = s.size();
        int i, j;
        i = s.find_first_not_of(' ');
        if (i == string::npos){
            s.resize(0);
            return;
        }
        s[0] = s[i];
        for (i++, j = 1; i < len; i++) {
            if ((s[i] != ' ') || (s[i] == ' ' && s[i-1] != ' ')) {
                s[j] = s[i];
                j++;
            }
        }
        if (s[j-1] == ' ') j--;
        s.resize(j);
    }

public:
    void reverseWords(string &s) {
        deleteSpaces(s); // comment this line to keep spaces

        // reverse sentence
        int len = s.size();
        int i, j;
        char tmp;
        for (i = 0, j = len - 1; i < j; i++, j-- ) {
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }

        // reverse words
        int left, right;
        right = -1;
        do {
            left = s.find_first_not_of(' ', right + 1);
            if (left == string::npos) break;
            right = s.find(' ', left + 1);
            if (right == string::npos) { // the end
                right = len;
            }

            // reverse s[left, right)
            for (i = left, j = right - 1; i < j; i++, j-- ) {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        } while (true);

    }
};

int main() {
    Solution solution;
    string s("");
    solution.reverseWords(s);
    cout << s << endl;
    return 0;
}
