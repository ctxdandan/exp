

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
        //load graph
        int N, M, src, dst, minsrc = 200, mindst = 200, maxsrc = 0, maxdst = 0;
        ifs >> N >> M;
        vector<vector<int> > edges(N);
        while (ifs >> src >> dst) {
            minsrc = min(src, minsrc);
            mindst = min(dst, mindst);
            maxsrc = max(src, maxsrc);
            maxdst = max(dst, maxdst);

            edges.resize(max(maxsrc, maxdst) + 1);
            edges[src].push_back(dst);
        }
        ifs.close();
        printf("Graph Summary:N=%d M=%d minsrc=%d mindst=%d maxsrc=%d maxdst=%d\nh", N, M, minsrc, mindst, maxsrc,
               maxdst);

        //validation
        int minid = min(minsrc, mindst), maxid = max(maxsrc, maxdst);
        int edge_count = 0;
        for (int i = 0; i < edges.size(); ++i)edge_count += edges[i].size();
        if (M != edge_count) {
            log("Error summary statistics: minid=%d maxid=%d edge_count=%d N=%d M=%d", minid, maxid, edge_count, N, M);
        }

        //conversion
        vector<int> oid_nid(maxid + 1, -1); //to store map of old id to new id

        for (int i = 0; i < edges.size(); ++i) {
            for (int j = 0; j < edges[i].size(); ++j) {//detect all exist vertexes
                oid_nid[i] = 0;
                oid_nid[edges[i][j]] = 0;
            }
        }

        int id = 0;
        for (int i = 0; i < oid_nid.size(); ++i) {// assign new ids
            if (oid_nid[i] == 0) {
                oid_nid[i] = id++;
            }
        }
        int newN = id;
        vector<vector<int> > nedges(newN);//new Graph


        for (int i = 0; i < edges.size(); ++i) {
            for (int j = 0; j < edges[i].size(); ++j) {//construct new graph according new id
                nedges[oid_nid[i]].push_back(oid_nid[edges[i][j]]);
            }
        }

        log("newN=%d", newN)


        //dump graph
        FILE *of = fopen(ofpath.c_str(), "wb");
        if (of == NULL) {
            log("open file %s failed.", ofpath.c_str())
        }

        fwrite(&newN, sizeof(newN), 1, of);
        fwrite(&M, sizeof(M), 1, of);
        for (int i = 0; i < nedges.size(); ++i) {
            for (int j = 0; j < nedges[i].size(); ++j) {
                fwrite(&i, sizeof(i), 1, of);
                fwrite(&nedges[i][j], sizeof(nedges[i][j]), 1, of);
            }
        }

        fclose(of);


    }
}

#endif //EXP_PREPROCESS_H
