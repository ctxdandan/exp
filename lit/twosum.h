//
// Created by Admin on 2018/3/25.
//
/*
 * leetcode #1
 */
#ifndef LEARNCPP_TWOSUM_H
#define LEARNCPP_TWOSUM_H


#include "header.h"

class Solution {
public:
    void test() {
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        log("%s", vec2str(nums).c_str());
        log("%s", vec2str(twoSum(nums, target)).c_str());

        nums = {3, 2, 4};
        target = 6;
        log("%s", vec2str(nums).c_str());
        log("%s", vec2str(twoSum(nums, target)).c_str());
    }

    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> sorted=nums;

        sort(sorted.begin(),sorted.end());
        int l = 0, r = sorted.size() - 1;
        while (l < r) {
            if (sorted[l] + sorted[r] > target)
                r--;
            else if (sorted[l] + sorted[r] < target)
                l++;
            else
                break;
        }

        int lv=sorted[l],rv=sorted[r];
        l=-1;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==lv&&l<0)l=i;
            if(nums[i]==rv)r=i;
        }
        return vector<int>({l,r});
    }
};

#endif //LEARNCPP_TWOSUM_H
