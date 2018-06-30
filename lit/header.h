//
// Created by Admin on 2018/3/25.
//
//leetcod usr:zhangjunhua,pwd:zhangjunhua
#ifndef LEARNCPP_MACRO_H
#define LEARNCPP_MACRO_H

//headers

#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <sys/time.h>

using namespace std;

#define log(format, ...){\
time_t rawtime;\
rawtime%=10000000;\
float time=(double)rawtime/1000.0;\
fprintf(stdout, "[%8.3fs %s.%s()#%d] " format "\n", time,__FILE__, __func__,  __LINE__, ##__VA_ARGS__ );\
}
string& operator+(string& str,int num){
    stringstream ss;
    ss<<num;
    str+=ss.str();
    return str;
}

double get_current_time() {
    timeval t;
    gettimeofday(&t, 0);
    return (double) t.tv_sec + (double) t.tv_usec / 1000000;
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
