//
// Created by Admin on 2018/3/25.
//

#ifndef LEARNCPP_LIT4_H
#define LEARNCPP_LIT4_H

#include "header.h"


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty())return findMedianSortedArrays(nums2,nums2);
        if(nums2.empty())return findMedianSortedArrays(nums1,nums1);

        int al=0,bl=0,ar=nums1.size(),br=nums2.size();
        int totalsize=nums1.size()+nums2.size();
        int oal=al,oar=ar,obl=bl,obr=br;
        while(true){
            int amid=(al+ar)/2;
            int bmid=(bl+br)/2;
            if(nums1[amid]<nums2[bmid]){
                if((amid+bmid+1)*2<=totalsize+1){
                    al=amid;
                }

                if((amid+bmid+2)*2>totalsize){
                    br=bmid+1;
                }
                if((amid+bmid+2)*2>=totalsize+3){
                    br=bmid;
                }
            }else if(nums1[amid]>nums2[bmid]){
                if((amid+bmid+1)*2<=totalsize+1){
                    bl=bmid;
                }
                if((amid+bmid+2)*2>totalsize){
                    ar=amid+1;
                }
                if((amid+bmid+2)*2>=totalsize+3){
//                    log("%d,%d,%d",al,amid,ar);
                    ar=amid;
                }
            } else{
                if((amid+bmid)*2<totalsize){
                    al=amid;
                    bl=bmid;
                }
                if((amid+bmid+2)*2>totalsize){
                    ar=amid+1;
                    br=bmid+1;
                }
            }
//            log("Anums1[%d,%d),nums2[%d,%d)",al,ar,bl,br);
            if(oal==al&&oar==ar&&obl==bl&&obr==br){
                if(nums1[amid]<nums2[bmid]){
                    if((amid+bmid+1)*2<totalsize){
                        bl=bmid;
                    }
                    if((amid+bmid+3)*2>totalsize){
                        ar=amid+1;
                    }
                }else if(nums1[amid]>nums2[bmid]){
                    if((amid+bmid+1)*2<totalsize){
                        al=amid;
                    }
                    if((amid+bmid+3)*2>totalsize){
                        br=bmid+1;
                    }
                }
            }
//            log("Bnums1[%d,%d),nums2[%d,%d)",al,ar,bl,br);
            if(oal==al&&oar==ar&&obl==bl&&obr==br){
                break;
            } else{
                oal=al,oar=ar,obl=bl,obr=br;
            }
        }
//        log("nums1[%d,%d),nums2[%d,%d)",al,ar,bl,br);
        vector<int> m;
        for(int i=al;i<ar;i++)m.push_back(nums1[i]);
        for(int i=bl;i<br;i++)m.push_back(nums2[i]);
        sort(m.begin(),m.end());
        int k=(nums1.size()+nums2.size())/2-al-bl;
        if((nums1.size()+nums2.size())%2==0){
            return (m[k-1]+m[k])/2.0;
        } else{
            return m[k];
        }
    }

    void test(){
        vector<int> a={1,3};
        vector<int> b={2};
        log("%f",findMedianSortedArrays(a,b));
        a={4,5};
        b={1,2,3};
        log("%f",findMedianSortedArrays(a,b));
        a={5,6};
        b={1,2,3,4};
        log("%f",findMedianSortedArrays(a,b));
    };
};
#endif //LEARNCPP_LIT4_H
