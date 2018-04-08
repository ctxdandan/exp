//
// Created by admin on 2018/4/8.
//

#ifndef EXP_DATACONVERSION_H
#define EXP_DATACONVERSION_H


#include "header.h"

namespace dataconversion {
    void convertchartobinarydata() {
#define vec 1
        //ifstream ifs("E:\\迅雷下载\\twitter_big\\Twitter-dataset\\data\\edges.csv");
        double starttime, endtime;

        starttime = get_current_time();
        int CAPACITY = 250000000;
#ifdef vec
        vector<int> data;
        data.resize(250000000);
#else
        int *data = new int[CAPACITY];
#endif
        FILE *fp = fopen("E:\\twitter_big\\Twitter-dataset\\data\\edges.csv", "r");
        if (fp == NULL) {
            log("file opened failed.");
        }
        int x, y;
        int size=0;

        while (fscanf(fp, "%d,%d\n", &x, &y) != EOF) {
            data[size++]=x;
            assert(size<CAPACITY);
            data[size++]=y;
            assert(size<CAPACITY);
        }

        fclose(fp);
        endtime = get_current_time();

        log("load data consumed %f seconds.", endtime - starttime);

        for(int i=0;i<10;i++){
            printf("%d,%d\n",data[i],data[i+1]);
            i++;
        }

        log("the size of data is %d*4\n",size);


        starttime = get_current_time();
        fp = fopen("E:\\twitter_big\\Twitter-dataset\\data\\edges.csv.bin", "w");
        if (fp == NULL) {
            log("file opened failed.");
        }
#ifdef vec
        fwrite(data.data(), sizeof(int), size, fp);
#else
        fwrite(data, sizeof(int), size, fp);
#endif
        fclose(fp);
        endtime = get_current_time();
        log("dump data consumed %f seconds.", endtime - starttime);


    }
}


#endif //EXP_DATACONVERSION_H
