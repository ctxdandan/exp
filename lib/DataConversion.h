//
// Created by admin on 2018/4/8.
//

#ifndef EXP_DATACONVERSION_H
#define EXP_DATACONVERSION_H


#include "header.h"

namespace dataconversion {
    void convertchartobinarydata() {
//        ifstream ifs("E:\\迅雷下载\\twitter_big\\Twitter-dataset\\data\\edges.csv");
//        FILE *fin = fopen("D:\\Dataset\\Twitter-dataset\\data\\edges.csv", "r");
//        FILE *fin = fopen("E:\\twitter_big\\Twitter-dataset\\data\\edges.csv", "r");
//#define debug
#ifdef debug
        FILE *fin = fopen("C:\\Users\\admin\\ClionProjects\\exp\\data\\testdata", "r");
        FILE *fout = fopen("C:\\Users\\admin\\ClionProjects\\exp\\data\\testdata.bin", "wb");
#else
        FILE *fin = fopen("out.twitter_mpi_1", "r");
        FILE *fout = fopen("out.twitter_mpi_1.bin", "wb");
#endif
        if (fin == NULL) {
            log("fin opened failed.");
        }
        if (fout == NULL) {
            log("fout opened failed.")
        }
        //read two line of meta-data
        const int len = 1024;
        char buf[len];
        fgets(buf, len, fin);
        printf("%s\n", buf);
        fgets(buf, len, fin);
        printf("%s\n", buf);

        int line_processed = 0;
        double prev_time = get_current_time();

        int x, y;
        while (fscanf(fin, "%d %d\n", &x, &y) != EOF) {
            fwrite(&x, sizeof(int), 1, fout);
            fwrite(&y, sizeof(int), 1, fout);
            line_processed++;
            if ((get_current_time() - prev_time) > 5) {
                prev_time = get_current_time();
                log("processed line#%d", line_processed)
            }
#ifdef debug
            printf("%d %d\n", x, y);
#endif
        }

        fclose(fin);
        fclose(fout);

    }
}


#endif //EXP_DATACONVERSION_H
