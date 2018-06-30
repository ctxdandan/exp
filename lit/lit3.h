//
// Created by Admin on 2018/3/25.
//

#ifndef LEARNCPP_LIT3_H
#define LEARNCPP_LIT3_H

#include "header.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unsigned int maxlen = 0;
        unsigned int l = 0, r = 0;
        while (r < s.size()) {
            //locate new l
            unsigned int newl = l;
            while (newl < r) {
                if (s.at(newl) == s.at(r))break;
                newl++;
            }
            if (newl < r)l = newl + 1;
//            log("(%d,%d)",l,r);
            //compute maxlen
            maxlen = max(maxlen, r - l + 1);

            r++;
        }
        return maxlen;
    }

    void test() {
        printf("%d\n", lengthOfLongestSubstring("abcabcbb"));

    };
};

#endif //LEARNCPP_LIT3_H
