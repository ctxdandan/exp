//
// Created by admin on 2018/5/25.
//

#ifndef EXP_GRAPHDIFF_H
#define EXP_GRAPHDIFF_H

#include "header.h"

namespace graphdiff {

    void load_edge_graph(size_t &N, size_t &M, vector<vector<size_t> > &edges, vector<size_t> &v2l) {
        ifstream ifs("E:\\twitter_big\\out.twitter_mpi_1.DAG.lvl.edgefmt");

        if (!ifs) {
            log("file not found.")
        }
        ifs >> N >> M;
        log("The Size of this Graph is (V:%d,E:%d)", N, M);
        edges.resize(N);
        v2l.resize(N);

        for (size_t i = 0; i < M; ++i) {
            size_t u, v;
            ifs >> u >> v;

            edges[u].push_back(v);
        }

        for (size_t i = 0; i < N; ++i) {
            size_t l;
            ifs >> l;
            v2l[i] = l;
        }

        ifs.close();
    }

    void load_vertex_graph(size_t &N, size_t &M, vector<vector<size_t> > &edges, vector<vector<size_t> > &redges,
                           vector<size_t> &v2l) {
        ifstream ifs("E:\\twitter_big\\out.twitter_mpi_1.DAG.lvl.vertexfmt");
        if (!ifs) {
            log("file not found.")
        }
        string line;
        log("start readline.N:%d",N);
        fflush(stdout);
        printf("maxlengh of string:%d\n", line.max_size());
        printf("maxlength of vec:%d\n", edges.max_size());
        while (getline(ifs, line)) {
//            cout<<line<<endl;
            fflush(stdout);
            istringstream iss(line);
            size_t vid, level;
            iss >> vid >> level;
            N = max(N, vid + 1);

            edges.resize(N);
            redges.resize(N);
            v2l.resize(N);

            v2l[vid] = level;

            size_t odeg, oneib;
            iss >> odeg;
            for (size_t i = 0; i < odeg; ++i) {
                iss >> oneib;
                edges[vid].push_back(oneib);
            }

            size_t ideg, ineib;
            iss >> ideg;
            for (size_t i = 0; i < ideg; ++i) {
                iss >> ineib;
                redges[vid].push_back(ineib);
            }

        }
        log("end readline.")

        ifs.close();
    }

    bool vec_diff(vector<size_t> &a, vector<size_t> &b) {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    }

    bool set_diff(vector<size_t> &a, vector<size_t> &b) {
        if (a.size() != b.size())
            return false;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return vec_diff(a, b);
    }

    void graphdiff() {
        log("graph diff begin.")
        size_t eN, vN, eM, vM;
        vector<vector<size_t> > egraph, vgraph, vrgraph, vvrgraph;
        vector<size_t> ev2l, vv2l;

        log("load edge graph.");
        load_edge_graph(eN, eM, egraph, ev2l);
        log("load vertex graph.");
        load_vertex_graph(vN, vM, vgraph, vrgraph, vv2l);
        log("load vertex graph end.");
        if (egraph.size() != vgraph.size()) log("egraph.size:%d, vgraph.size:%d", egraph.size(), vgraph.size())
        for (size_t vid = 0; vid < egraph.size(); ++vid) {
            if (!set_diff(egraph[vid], vgraph[vid])) log("vid:%d neighbors present difference.")
        }
        if (!vec_diff(ev2l, vv2l)) log("level present difference.")

        vvrgraph.resize(vrgraph.size());
//        for (size_t vid = 0; vid < vrgraph.size(); ++vid) {
//            for (size_t i = 0; i < vrgraph[vid].size(); ++i) {
//                vvrgraph[vrgraph[vid][i]].push_back(vid);
//            }
//        }
//
//        if (vgraph.size() != vvrgraph.size()) log("inneib.size and ouneib.size presents difference.")
//        for (size_t vid = 0; vid < vgraph.size(); ++vid) {
//            if (!set_diff(vgraph[vid], vvrgraph[vid])) log("vid:%d neighbors present difference.")
//        }


        log("graph diff end.")
    }
}


#endif //EXP_GRAPHDIFF_H
