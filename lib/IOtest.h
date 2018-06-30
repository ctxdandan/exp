//
// Created by admin on 2018/5/31.
//

#ifndef EXP_IOTEST_H
#define EXP_IOTEST_H


#include "header.h"
namespace iotest{

#define SIZE (1<<30)

    void tfwrite() {
        double start_time = get_current_time();

        char *data = (char *) malloc(SIZE);
        FILE *fp = fopen("data", "wb");
        if (fp == NULL) {
            fprintf(stderr, "file not found");
            exit(1);
        }
        fwrite(data, sizeof(char), SIZE, fp);
        fclose(fp);
        free(data);

        double end_time = get_current_time();
        log("%f seconds elapsed in write binary.", end_time - start_time);
    }

    void tfread() {
        double start_time = get_current_time();

        char *data = (char *) malloc(SIZE);
        FILE *fp = fopen("data", "rb");
        fread(data, sizeof(char), SIZE, fp);
        fclose(fp);
        free(data);

        double end_time = get_current_time();
        log("%f seconds elapsed in read binary.", end_time - start_time);
    }

    void tfprintf() {
        double start_time = get_current_time();

        char *data = (char *) malloc(SIZE);
        memset(data, 0, SIZE);
        FILE *fp = fopen("data.txt", "w");
        if (fp == NULL) {
            fprintf(stderr, "file not found");
            exit(1);
        }
        for (int i = 0; i < SIZE; i++) {
            fprintf(fp, "%d ", data[i]);
        }
        fclose(fp);
        free(data);

        double end_time = get_current_time();
        log("%f seconds elapsed in fprintf.", end_time - start_time);
    }

    void tfscanf(){
        double start_time = get_current_time();

        char *data = (char *) malloc(SIZE);
        FILE *fp = fopen("data.txt", "r");
        if (fp == NULL) {
            fprintf(stderr, "file not found");
            exit(1);
        }
        for (int i = 0; i < SIZE; i++) {
            fscanf(fp,"%d",data+i);
        }
        fclose(fp);
        free(data);

        double end_time = get_current_time();
        log("%f seconds elapsed in fscanf.", end_time - start_time);
    }

    void writetest(){
        tfwrite();
        tfprintf();
    }
    void readtest(){
        tfread();
        tfscanf();
    }

}



#endif //EXP_IOTEST_H
