//
// Created by Admin on 2018/3/25.
//

#ifndef LEARNCPP_LIT2_H
#define LEARNCPP_LIT2_H

#include "header.h"

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};
static const auto _____ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int higher = 0;
        ListNode *p1 = l1, *p2 = l2;
        while (p1 || p2) {
            if (p2) {
                higher += p1->val + p2->val;
                p1->val = higher % 10;
                higher /= 10;
                if (!p1->next)
                {
                    p1->next=p2->next;
                    p2->next=NULL;
                }
                if(!p1->next && higher){
                    p1->next=new ListNode(1);
                    break;
                }
                p2=p2->next;
            } else if(p1){
                higher+=p1->val;
                p1->val=higher%10;
                higher/=10;
                if(!p1->next && higher){
                    p1->next=new ListNode(1);
                    break;
                }

            }
            p1=p1->next;
        }
        return l1;
//        ListNode *last;
//        while (p1 && p2) {
//            p1->val+=p2->val+higher;
//            higher=p1->val/10;
//            p1->val%=10;
//            p2->val=p1->val;
//            last=p1;
//            p1=p1->next,p2=p2->next;
//        }
//        if(p2) {
//            p1 = p2;
//            l1=l2;
//        }
//        while(p1 && higher){
//            p1->val+=higher;
//            higher=p1->val/10;
//            p1->val%=10;
//            last=p1;
//            p1=p1->next;
//        }
//        if(higher){
//            last->next=new ListNode(1);
//        }
//        return l1;
    }

    ListNode *vec2lst(vector<int> &a) {
        ListNode *head = NULL;
        for (int i = 0; i < a.size(); i++) {
            ListNode *node = new ListNode(a[i]);
            node->next = head;
            head = node;
        }
        return head;
    }

    void printlst(ListNode *head) {
        while (head) {
            printf("%d", head->val);
            head = head->next;
        }
        printf("\n");
    }

    void test() {
        vector<int> a = {5};
        vector<int> b = {5};
        ListNode *pa = vec2lst(a);
        ListNode *pb = vec2lst(b);
        printlst(pa);
        printlst(pb);
        printlst(addTwoNumbers(pa, pb));
    };
};

#endif //LEARNCPP_LIT2_H
