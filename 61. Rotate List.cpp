// https://leetcode.com/problems/rotate-list/
// 8ms, 15.09% , 84.91%

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {

        //head: (n-k+1)th, tail: n-k

        if (k == 0 || !head) return head;

        ListNode *p1 = head;

        for (int i = 0; i < k; i++){
            // k > len?
            p1 = p1->next;
            if (!p1){
                k = k % (i+1);
                if (k == 0) return head;
                p1 = head;
                for (int i = 0; i < k; i++){
                    p1 = p1->next;
                }
                break;
            }
        }

        ListNode *pre1, *pre2, *p2 = head;
        while (p1){
            pre1 = p1;
            pre2 = p2;
            p1 = p1->next;
            p2 = p2->next;
        }
        pre1->next = head;
        head = p2;
        pre2->next = NULL;

        return head;
    }

};
