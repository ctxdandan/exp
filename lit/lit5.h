//
// Created by admin on 2018/3/27.
//

#ifndef CPPLEARN_LIT5_H
#define CPPLEARN_LIT5_H

#include "header.h"

class Solution {
public:
    string longestPalindrome(string s) {
        vector<int> symcen;
        symcen.resize(s.size()*2,1);
        string longest=s.substr(0,1);

        for(int i=1;i<s.size();i++){
            for(int j=0;j<=i;j++){
                if(symcen[i+j]==1){
                    if(s[i]==s[j]){
                        if((i-j+1)>longest.size()) {
                            longest = s.substr(j, i - j + 1);
                        }
                    }else{
                        symcen[i+j]=0;
                    }
                }
            }
        }
        return longest;
    }

    void test() {
        longestPalindrome("aaaabbbbcdefxxxxxyxx");
    }
};
#endif //CPPLEARN_LIT5_H
