//
// Created by Admin on 2018/3/25.
//
//leetcod usr:zhangjunhua,pwd:zhangjunhua
#ifndef LEARNCPP_MACRO_H
#define LEARNCPP_MACRO_H

//headers

#include <cstdio>
#include <iostream>
#include <ctime>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include <sys/time.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <cstdio>
#include <fstream>
using namespace std;

#define log(format, ...){\
fprintf(stdout, "[%s.%s()#%d] " format "\n", __FILE__, __func__,  __LINE__, ##__VA_ARGS__ );\
}
string& operator+(string& str,int num){
    stringstream ss;
    ss<<num;
    str+=ss.str();
    return str;
}



template<typename T>
string vec2str(vector<T> v) {
    string result = "[";
//    log("%s",result);
    for (int i = 0; i < v.size(); i++) {
//        log("%s",result.c_str());
        if (i < v.size() - 1)
            result = result + v[i] + ",";
        else
            result = result + v[i] + "]";
    }
    return result;
}

#endif //LEARNCPP_MACRO_H
