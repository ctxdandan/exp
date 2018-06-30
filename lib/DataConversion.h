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
//        FILE *fin = fopen("out.twitter_mpi_1", "r");
//        FILE *fout = fopen("out.twitter_mpi_1.bin", "wb");
        FILE *fin = fopen("E:\\WEBSPAM-UK2007\\graph\\webspam_uk2007.edge.txt", "r");
        FILE *fout = fopen("E:/WEBSPAM-UK2007/graph/webspam_uk2007.edge.bin", "wb");
#endif
        /*

0 9
8 91
11 11
11 12
11 13
11 14
11 15
11 16
11 17
11 18
         */
        if (fin == NULL) {
            log("fin opened failed.");
        }
        if (fout == NULL) {
            log("fout opened failed.")
        }
        //read two line of meta-data

        int line_processed = 0;
        double prev_time = get_current_time();
        long long n, m;
        fscanf(fin, "%lld %lld\n", &n, &m);
        fwrite(&n, sizeof(long long), 1, fout);
        fwrite(&m, sizeof(long long), 1, fout);
        printf("n:%lld m:%lld\n",n,m);

        int x, y;
        fscanf(fin, "%d %d\n", &x, &y);
        fwrite(&x, sizeof(int), 1, fout);
        fwrite(&y, sizeof(int), 1, fout);
        printf("(%d,%d)\n", x, y);
        line_processed++;

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
