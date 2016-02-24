//https://leetcode.com/problems/linked-list-cycle-ii/
// 12ms, 83.18%, 16.82%

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
    ListNode *detectCycle(ListNode *head) {

        if (!head) return NULL;

        ListNode *p1 = head, *p2 = head;
        bool ans = true;

        // given a, p
        //1. a + kp + r = t
        //2. a + lp + r = 2t
        do{
            if (p2){
                p2 = p2->next;
            }else{
                ans = false;
                break;
            }
            if (p2){
                p2 = p2->next;
            }else{
                ans = false;
                break;
            }
            p1 = p1->next;
        }while (p1 != p2);

        if (ans){
            int count = 0;
            do{
                p2 = p2->next;
                count++;
            }while (p1 != p2);
            p2 = head;
            while(count > 0){
                p2 = p2->next;
                count--;
            }
            p1 = head;
            while(p1 != p2){
                p1 = p1->next;
                p2 = p2->next;
            }
            return p1;
        }else return NULL;

    }
};
