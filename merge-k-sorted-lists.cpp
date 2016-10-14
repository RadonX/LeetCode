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

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

vector<ListNode*> makeLists(const vector<vector<int> > &arrays) {
    vector<ListNode*> lists;
    for (auto arr: arrays) {
        ListNode* head = new ListNode(0);
        ListNode* p = head;
        for (auto a: arr) {
            p->next = new ListNode(a);
            p = p->next;
        }
        lists.push_back(head->next);
    }
    return lists;
}


struct cmpNode {
    bool operator() (const ListNode* a, const ListNode* b) const { // min heap -> >
        if (!a) return true;
        if (!b) return false;
        return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return NULL;
        ListNode *p = new ListNode(0);
        ListNode *head = p;
        priority_queue<ListNode*,vector<ListNode*>,cmpNode> heap(lists.begin(), lists.end());
        ListNode *cur;
        heap.push(NULL);
        while (heap.top()) {
            cur = heap.top();
            heap.pop();
            if (cur->next) // 46ms->39ms
                heap.push(cur->next);
            p->next = new ListNode(cur->val);
            p = p->next;
        }

        return head->next;
    }
};

int main() {
    Solution solution;
    vector<ListNode*> lists = makeLists(vector<vector<int> > {{1,4},{3,6},{},{2,8}});
    ListNode* p = solution.mergeKLists(lists);
    while (p) { cout << p->val << ','; p = p->next; }
    return 0;
}
