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

class LinkedListNode{
public:
    int val;
    LinkedListNode *next;

    LinkedListNode(int node_value) {
        val = node_value;
        next = NULL;
    }
};

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode *head, LinkedListNode *tail, int val){
    if(head == NULL) {
        head = new LinkedListNode(val);
        tail = head;
    }
    else {
        LinkedListNode *node = new LinkedListNode(val);
        tail->next = node;
        tail = tail->next;
    }
    return tail;
}


/*
 * Complete the function below.
 */
/*
For your reference:
LinkedListNode {
    int val;
    LinkedListNode *next;
};
*/

LinkedListNode* removeNodes(LinkedListNode* list, int x) {
    if (!list) return NULL;

    LinkedListNode *dummy = new LinkedListNode(x);
    dummy->next = list;
    LinkedListNode *p, *q, *r;
    p = dummy;
    q = p->next;
    while (!q) {
        // process q
        if (q->val > x) {
            // delete q
            r = q->next;
            delete q;
            p = r;
            if (!r) break;
            q = r->next;
        } else {
            p = q;
            q = q->next;
        }
    }
    return dummy->next;
}




int main() {

	return 0;
}
