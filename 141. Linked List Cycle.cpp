//https://leetcode.com/problems/linked-list-cycle/
//12ms, 86.92%, 13.08%

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
    bool hasCycle(ListNode *head) {

     //1. a + kp + r
     //2. a + lp + r
     //(l-2k)p - r = a
        if (!head) return false;

        ListNode *p1 = head, *p2 = head;
        bool ans = true;

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

        return ans;

    }
};
