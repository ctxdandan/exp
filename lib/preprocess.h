

#ifndef EXP_PREPROCESS_H
#define EXP_PREPROCESS_H

#include "header.h"

namespace preprocess {
    void preprocess(string ifpath, string ofpath) {
        ifstream ifs(ifpath.c_str());
        if (!ifs.is_open()) {
            log("open file %s failed!", ifpath.c_str());
            exit(-1);
        }
        //remove preceding comments
        string line;
        ifstream::pos_type pos = ifs.tellg();
        getline(ifs, line);
        while (line[0] == '#') {
            pos = ifs.tellg();
            getline(ifs, line);
        }
        ifs.seekg(pos);

        int N, M, src, dst, minsrc = 200, mindst = 200, maxsrc = 0, maxdst = 0;
        ifs >> N >> M;

        vector<vector<int> > edges(N);
        while (ifs >> src >> dst) {
            minsrc = min(src, minsrc);
            mindst = min(dst, mindst);
            maxsrc = max(src, maxsrc);
            maxdst = max(dst, maxdst);

            edges.resize(max(src, dst) + 1);
            edges[src].push_back(dst);
        }

        ifs.close();
        printf("Graph Summary:N=%d M=%d minsrc=%d mindst=%d maxsrc=%d maxdst=%d", N, M, minsrc, mindst, maxsrc, maxdst);
        //validation
        int minid = min(minsrc, mindst), maxid = max(maxsrc, maxdst);
        int edge_count = 0;
        for (int i = 0; i < edges.size(); ++i)edge_count += edges[i].size();
        if ((maxid - minid) != N || M != edge_count) {
            log("Error summary statistics: minid=%d maxid=%d edge_count=%d N=%d M=%d", minid, maxid, edge_count, N, M);
        }


        for (int i = 0; i < edges.size(); ++i) {
            edges[i].swap(edges[i + minid]);
            for (int j = 0; j < edges[i].size(); ++j) {
                edges[i][j] -= minid;
            }
        }
        edges.resize(edges.size() - minid);

        ofstream ofs(ofpath.c_str(), ios::out | ios::binary);
        if(!ofs.is_open()){
            log("open file %s failed.",ofpath.c_str())
        }

        


    }
}

#endif //EXP_PREPROCESS_H
