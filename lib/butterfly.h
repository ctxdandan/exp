//
// Created by admin on 2018/4/1.
//

#ifndef EXP_BUTTERFLY_H
#define EXP_BUTTERFLY_H

#include "header.h"

using namespace std;

namespace butterfly {
    bool intersection(size_t src, vector<size_t> srcLout, size_t dst, vector<size_t> dstLin) {
        srcLout.push_back(src);
        dstLin.push_back(dst);
        sort(srcLout.begin(), srcLout.end());
        sort(dstLin.begin(), dstLin.end());
        vector<size_t> result;
        set_intersection(srcLout.begin(), srcLout.end(), dstLin.begin(), dstLin.end(),
                         inserter(result, result.end()));
        return !result.empty();
    }

    void zjh_bfs_labeling(vector<vector<size_t>> &edge, size_t src, vector<size_t> &v2l, vector<vector<size_t>> &lin,
                          vector<vector<size_t>> &lout) {
        queue<size_t> Q;
        set<size_t> visited;
        for (int i = 0; i < edge[src].size(); i++)if (v2l[src] < v2l[edge[src][i]])Q.push(edge[src][i]);
        while (!Q.empty()) {
            size_t dst = Q.front();
            Q.pop();
            if (visited.insert(dst).second) {
                if (!intersection(src, lout[src], dst, lin[dst])) {
                    lin[dst].push_back(src);
                    for (size_t i = 0; i < edge[dst].size(); i++)
                        if (v2l[src] < v2l[edge[dst][i]])Q.push(edge[dst][i]);
                }
            }
        }
//        log("vertex visited by vid%d level%d:%d", src, v2l[src], visited.size());
    }

    size_t N, M;
    vector<vector<size_t>> edges;
    vector<vector<size_t>> redges;
    vector<vector<size_t>> lin;
    vector<vector<size_t>> lout;
    vector<size_t> v2l;
    vector<size_t> l2v;
    double cur_time = 0;


    void zjh_init() {
        for (size_t l = 0; l < l2v.size(); l++) {
            if (get_current_time() - cur_time > 1) {
                log("start proceeding %d in time %f. outDegree:%d inDegree:%d", l, get_current_time(),
                    edges[l2v[l]].size(), redges[l2v[l]].size());
                cur_time = get_current_time();
            }
            zjh_bfs_labeling(edges, l2v[l], v2l, lin, lout);
            zjh_bfs_labeling(redges, l2v[l], v2l, lout, lin);
        }
    }

    void TOLIndexQuery() {//4.55s
//        fin.open("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tol1.dat");
//        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_edgefmt");
//        ifstream ifs("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG_lvl_edgefmt");
        ifstream ifs("E:\\twitter_big\\out.twitter_mpi_1.DAG.lvl.edgefmt");
//            ifstream ifs("edges_DAG_lvl_edgefmt");

//        ifstream ifs("edges_DAG_lvl_edgefmt");

        if (!ifs) {
            log("file not found.")
        }
        ifs >> N >> M;
        log("The Size of this Graph is (V:%d,E:%d)", N, M);
        edges.resize(N);
        redges.resize(N);
        v2l.resize(N);
        l2v.resize(N);
        lin.resize(N);
        lout.resize(N);

        for (size_t i = 0; i < M; ++i) {
            size_t u, v;
            ifs >> u >> v;

            edges[u].push_back(v);
            redges[v].push_back(u);
        }

        for (size_t i = 0; i < N; ++i) {
            size_t l;
            ifs >> l;
            v2l[i] = l;
            l2v[l] = i;
        }
        double starttime = get_current_time();
        butterfly::zjh_init();

        double endtime = get_current_time();
        log("butterfly consumed %f seconds.", endtime - starttime);

        size_t linsize = 0;
        for (int i = 0; i < lin.size(); i++) {
            linsize += lin[i].size();
        }
        size_t lotsize = 0;
        for (int i = 0; i < lout.size(); i++) {
            lotsize += lout[i].size();
        }

        log("linsize:%d loutsize:%d totalIdxSize:%d", linsize, lotsize, linsize + lotsize);

    }


    void validation() {
        log("validation begin.")
//        FILE *fp=fopen("E:\\twitter_big\\Twitter-dataset\\data\\result.txt","r");
//        ifstream ifs("E:\\twitter_big\\Twitter-dataset\\data\\result.txt");
        ifstream ifs("E:\\twitter_big\\result");
        if (!ifs.is_open()) {
            log("read file failed.")
            exit(-1);
        }
//        N = 12407621;
        vector<vector<size_t> > in_label(N);
        vector<vector<size_t> > ou_label(N);
        string line;
        size_t minvid = 10, maxvid = 10;
        while (getline(ifs, line)) {
            istringstream iss(line);
            size_t vid;
            string tok;

            iss >> vid;
            iss >> tok;
            //handle in label
            while (iss >> tok) {
                if (tok.at(0) >= '0' && tok.at(0) <= '9')
                    in_label[vid].push_back(atoi(tok.c_str()));
                else break;
            }
            //handle out label
            while (iss >> tok) {
                if (tok.at(0) >= '0' && tok.at(0) <= '9')
                    ou_label[vid].push_back(atoi(tok.c_str()));
            }
        }
        log("finish reading file.")
        //convert the labelidx to ididx
        for (size_t i = 0; i < in_label.size(); ++i) {
            for (size_t j = 0; j < in_label[i].size(); ++j) {
                in_label[i][j] = l2v[in_label[i][j]];
            }
        }
        for (size_t i = 0; i < ou_label.size(); ++i) {
            for (size_t j = 0; j < ou_label[i].size(); ++j) {
                ou_label[i][j] = l2v[ou_label[i][j]];
            }
        }
        log("finish convert labelidx to ididx.")
        //validation
        assert(lin.size() == in_label.size());
        assert(lout.size() == ou_label.size());

        for (size_t i = 0; i < lin.size(); ++i) {
//            assert(lin[i].size()==in_label[i].size());
            sort(lin[i].begin(), lin[i].end());
            sort(in_label[i].begin(), in_label[i].end());
            if (!(lin[i].size() == in_label[i].size())) {
                log("i:%d lin[i].size():%d in_label[i].size():%d", i, lin[i].size(), in_label[i].size());
                vector<size_t> &a = lin[i], &b = in_label[i];
                vector<size_t> diff;

                if (a.size() > b.size()) {
                    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diff));
                } else {
                    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diff));
                }
                printf("{");
                for (int i = 0; i < diff.size(); ++i) {
                    printf("%d,", diff[i]);
                }
                printf("}\n");

                continue;
            }
            for (size_t j = 0; j < lin[i].size(); ++j) {
//                assert(lin[i][j]==in_label[i][j]);
                if (!(lin[i][j] == in_label[i][j])) {
                    printf("lin[%d][%d]:%d==in_label[%d][%d]:%d\n", i, j, lin[i][j], i, j, in_label[i][j]);
                }
            }
        }
        log("finish lin and in_label validation")

        for (size_t i = 0; i < lout.size(); ++i) {
//            assert(lout[i].size()==ou_label[i].size());
            sort(lout[i].begin(), lout[i].end());
            sort(ou_label[i].begin(), ou_label[i].end());
            if (!(lout[i].size() == ou_label[i].size())) {
                log("i:%d lout[i].size():%d ou_label[i].size():%d", i, lout[i].size(), ou_label[i].size());

                vector<size_t> &a = lout[i], &b = ou_label[i];
                vector<size_t> diff;

                if (a.size() > b.size()) {
                    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diff));
                } else {
                    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diff));
                }
                printf("{");
                for (int i = 0; i < diff.size(); ++i) {
                    printf("%d,", diff[i]);
                }
                printf("}\n");

                continue;
            }
            for (size_t j = 0; j < lout[i].size(); ++j) {
                //                assert(lin[i][j]==in_label[i][j]);
                if (!(lout[i][j] == ou_label[i][j])) {
                    printf("lout[%d][%d]:%d==ou_label[%d][%d]:%d\n", i, j, lout[i][j], i, j, ou_label[i][j]);
                }
            }
        }

        log("validation end.");
    }

} // namespace butterfly

#endif //EXP_BUTTERFLY_H
