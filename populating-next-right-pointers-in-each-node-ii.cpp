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
#include <unordered_set>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        // bfs
        TreeLinkNode *p = root, *q, *t1, *t2;
        TreeLinkNode *dummy = new TreeLinkNode(0);
        if (p) p->next = NULL;
        while (p) {
            // p is the head of previous level
            // q is the head of current level
            q = NULL; t1 = dummy;
            while (p != NULL) {
                if ((t2 = p->left) != NULL) {
                    t1->next = t2; t1 = t2; if (!q) q = t2;
                }
                if ((t2 = p->right) != NULL) {
                    t1->next = t2; t1 = t2; if (!q) q = t2;
                }
                p = p->next;
            }
            t1->next = NULL;
            p = q;
        }
    }
};


int main() {
    Solution solution;
    return 0;
}
