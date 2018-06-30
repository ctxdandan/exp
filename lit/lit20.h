//
// Created by Admin on 2018/3/27.
//

#ifndef LEARNCPP_LIT20_H
#define LEARNCPP_LIT20_H

#include "header.h"

class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        for(string::iterator it=s.begin();it!=s.end();it++){
            if(*it=='{'){
                stack.push_back(*it);
            }else if(*it=='['){
                stack.push_back(*it);
            }else if(*it=='('){
                stack.push_back(*it);
            }else if(*it==')'){
                if(stack.empty()||stack.back()!='(')
                    return false;
                stack.pop_back();
            }else if(*it==']'){
                if(stack.empty()||stack.back()!='[')
                    return false;
                stack.pop_back();
            }else if(*it=='}'){
                if(stack.empty()||stack.back()!='{')
                    return false;
                stack.pop_back();
            }
//            printf("%d\n",stack.size());
//            for(int i=0;i<stack.size();i++){
//                printf("%c",stack[i]);
//            }
//            printf("\n");
        }
        if(stack.empty())return true;
        return false;
    }

    void test(){
        log("%d",isValid("[]{}"));
    };
};


#endif //LEARNCPP_LIT20_H
