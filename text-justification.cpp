#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// https://discuss.leetcode.com/topic/4189/share-my-concise-c-solution-less-than-20-lines
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {

        vector<string> ans;
        string spaceline(maxWidth, ' ');
        words.push_back(spaceline);
        char buffer[maxWidth + 1], *p;

        int count, len, nspace, lspace, morespace;
        vector<string>::iterator start, it;
        for (start = words.begin(); start != prev(words.end()); ) {
            len = -1;
            count = -1;
            it = start;
            while (len <= maxWidth) {
                len += 1 + (*it).size();
                ++count;
                ++it;
            }
            if (it == words.end()) count = 1; // last line
            if (count == 0) // single word too long
                return vector<string>();
            --it;
            len -= 1 + it->size();

            nspace = maxWidth - len + count - 1;
            if (count == 1) {
                morespace = 0;
                lspace = 1;
            } else {
                morespace = nspace % (count - 1);
                lspace = nspace / (count - 1);
            }

            strcpy(buffer, spaceline.data());
            p = buffer;
            for (; start != it; ++start) {
                int wordLen = start->size();
                start->copy(p, wordLen);
                p += wordLen + lspace;
                if (morespace > 0) {
                    --morespace;
                    ++p;
                }
            }
            ans.push_back(string(buffer));
            // start = it;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<string> words{"This", "is", "a", "justification.",  "example", "of", "text", "justification."};
    // vector<string> words{""};
    for (auto &a: solution.fullJustify(words, 16)) {
        cout << a << endl;
    }

	return 0;
}
