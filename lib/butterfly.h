//
// Created by admin on 2018/4/1.
//

#ifndef EXP_BUTTERFLY_H
#define EXP_BUTTERFLY_H

#include "header.h"

using namespace std;
#define buglevel 2411

namespace butterfly {
    bool debug = false;

    inline bool intersection(vector<size_t> &srcLout, vector<size_t> &dstLin) {
        vector<size_t>::iterator b1 = srcLout.begin(), e1 = srcLout.end(), b2 = dstLin.begin(), e2 = dstLin.end();
        for (; b1 != e1 && b2 != e2;) {
            if (*b1 < *b2)b1++;
            else if (*b1 > *b2)b2++;
            else return true;
        }
        return false;
//        vector<size_t> result;
//        set_intersection(srcLout.begin(), srcLout.end(), dstLin.begin(), dstLin.end(),
//                         inserter(result, result.end()));
//        return !result.empty();
    }

    void zjh_bfs_labeling(vector<vector<size_t> > &edge, size_t src, vector<size_t> &v2l, vector<vector<size_t> > &lin,
                          vector<vector<size_t> > &lout) {
        queue<size_t> Q;
        set<size_t> visited;
        for (int i = 0; i < edge[src].size(); i++) {
            if (v2l[src] < v2l[edge[src][i]]) {
                Q.push(edge[src][i]);
            }
        }
        while (!Q.empty()) {
            size_t dst = Q.front();
            Q.pop();
            if (visited.insert(dst).second) {
                if (!intersection(lout[src], lin[dst])) {
                    lin[dst].push_back(src);
                    sort(lin[dst].begin(), lin[dst].end());
                    for (size_t i = 0; i < edge[dst].size(); i++)
                        if (v2l[src] < v2l[edge[dst][i]]) {
                            Q.push(edge[dst][i]);
                        }
                }
            }
        }
//        log("vertex visited by vid%d level%d:%d", src, v2l[src], visited.size());
    }


    void
    zjh_bfs_level_labeling(vector<vector<size_t> > &edge, size_t src, vector<size_t> &v2l, vector<vector<size_t> > &lin,
                           vector<vector<size_t> > &lout) {
        queue<size_t> Q;
        set<size_t> visited;
        size_t srclvl = v2l[src];
        for (int i = 0; i < edge[src].size(); i++) {
            if (srclvl < v2l[edge[src][i]]) {
                Q.push(edge[src][i]);
            }
        }
        while (!Q.empty()) {
            size_t dst = Q.front();
            Q.pop();
            if (visited.insert(dst).second) {
                if (!intersection(lout[src], lin[dst])) {
                    lin[dst].push_back(srclvl);
                    for (size_t i = 0; i < edge[dst].size(); i++)
                        if (srclvl < v2l[edge[dst][i]]) {
                            Q.push(edge[dst][i]);
                        }
                }
            }
        }
//        log("vertex visited by vid%d level%d:%d", src, v2l[src], visited.size());
    }

    void
    zjh_bfs_level_bitvisit_labeling(vector<vector<size_t> > &edge, size_t src, vector<size_t> &v2l,
                                    vector<vector<size_t> > &lin,
                                    vector<vector<size_t> > &lout, vector<bool> &visitedbitmap) {
        queue<size_t> Q;
        vector<size_t> visited;
        size_t srclvl = v2l[src];
        for (int i = 0; i < edge[src].size(); i++) {
            if (srclvl < v2l[edge[src][i]]) {
                Q.push(edge[src][i]);
            }
        }
        while (!Q.empty()) {
            size_t dst = Q.front();
            Q.pop();
            if (!visitedbitmap[dst]) {
                visitedbitmap[dst] = true;
                visited.push_back(dst);
                if (!intersection(lout[src], lin[dst])) {
                    lin[dst].push_back(srclvl);
                    for (size_t i = 0; i < edge[dst].size(); i++)
                        if (srclvl < v2l[edge[dst][i]]) {
                            Q.push(edge[dst][i]);
                        }
                }
            }
        }
        for (vector<size_t>::iterator it = visited.begin(); it != visited.end(); it++) {
            visitedbitmap[*it] = false;
        }
    }

    size_t N, M;
    vector<vector<size_t> > edges;
    vector<vector<size_t> > redges;
    vector<vector<size_t> > lin;
    vector<vector<size_t> > lout;
    vector<size_t> v2l;
    vector<size_t> l2v;
    double cur_time = 0;


    void zjh_init() {
        vector<bool> visitedbitmap(l2v.size(), false);
        for (size_t l = 0; l < l2v.size(); l++) {
            if (get_current_time() - cur_time > 1) {
                log("start proceeding %d in time %f. outDegree:%d inDegree:%d", l, get_current_time(),
                    edges[l2v[l]].size(), redges[l2v[l]].size());
                cur_time = get_current_time();
            }
//            zjh_bfs_level_labeling(edges, l2v[l], v2l, lin, lout);
//            zjh_bfs_level_labeling(redges, l2v[l], v2l, lout, lin);
            zjh_bfs_level_bitvisit_labeling(edges, l2v[l], v2l, lin, lout, visitedbitmap);
            zjh_bfs_level_bitvisit_labeling(redges, l2v[l], v2l, lout, lin, visitedbitmap);

        }
    }

    void TOLIndexQuery() {//4.55s
//        fin.open("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tol1.dat");
//        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_edgefmt");
//        ifstream ifs("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG_lvl_edgefmt");
//        ifstream ifs("E:\\twitter_big\\out.twitter_mpi_1.DAG.lvl.edgefmt");
//            ifstream ifs("edges_DAG_lvl_edgefmt");

//        ifstream ifs("edges_DAG_lvl_edgefmt");
        ifstream ifs("E:/WEBSPAM-UK2007/graph/uk-2007-05.dag.edge.lvl.bin");

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
            if (l == buglevel) log("the vid of level %d is:%d", buglevel, i)
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
                if (tok.at(0) >= '0' && tok.at(0) <= '9') {
                    in_label[vid].push_back(atoi(tok.c_str()));
                } else break;
            }
            //handle out label
            while (iss >> tok) {
                if (tok.at(0) >= '0' && tok.at(0) <= '9') {
                    ou_label[vid].push_back(atoi(tok.c_str()));
                }
            }
            if (v2l[vid] == buglevel) {
                printf("DEBUG:%s\n", line.c_str());
                printf("in_label:");
                for (size_t i = 0; i < in_label[vid].size(); ++i) {
                    printf("%d, ", in_label[vid][i]);
                }
                printf(" ou_label:");
                for (size_t i = 0; i < ou_label[vid].size(); ++i) {
                    printf("%d, ", ou_label[vid][i]);
                }
                printf("\n");

                printf("lin:");
                for (size_t i = 0; i < lin[vid].size(); ++i) {
                    printf("%d, ", lin[vid][i]);
                }
                printf(" lout:");
                for (size_t i = 0; i < lout[vid].size(); ++i) {
                    printf("%d, ", lout[vid][i]);
                }
                printf("\n");
            }
        }
        log("finish reading file.")
        //convert the labelidx to ididx
//        for (size_t i = 0; i < in_label.size(); ++i) {
//            for (size_t j = 0; j < in_label[i].size(); ++j) {
//                in_label[i][j] = l2v[in_label[i][j]];
//            }
//        }
//        for (size_t i = 0; i < ou_label.size(); ++i) {
//            for (size_t j = 0; j < ou_label[i].size(); ++j) {
//                ou_label[i][j] = l2v[ou_label[i][j]];
//            }
//        }
        for (size_t i = 0; i < lin.size(); ++i) {
            for (size_t j = 0; j < lin[i].size(); ++j) {
                lin[i][j] = v2l[lin[i][j]];
            }
        }
        for (size_t i = 0; i < lout.size(); ++i) {
            for (size_t j = 0; j < lout[i].size(); ++j) {
                lout[i][j] = v2l[lout[i][j]];
            }
        }
        log("finish convert labelidx to ididx.")
        //validation
        assert(lin.size() == in_label.size());
        assert(lout.size() == ou_label.size());

        size_t min_diff = 12407621;
        for (size_t i = 0; i < lin.size(); ++i) {
            sort(lin[i].begin(), lin[i].end());
            sort(in_label[i].begin(), in_label[i].end());
            if (!(lin[i].size() == in_label[i].size())) {
                printf("vid:%d lvl:%d lin[i].size():%d in_label[i].size():%d", i, v2l[i], lin[i].size(),
                       in_label[i].size());
                vector<size_t> &a = lin[i], &b = in_label[i];
                vector<size_t> diff;

                if (a.size() > b.size()) {
                    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diff));
                } else {
                    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diff));
                }
                printf("{");
                for (int i = 0; i < diff.size(); ++i) {
                    min_diff = min(min_diff, diff[i]);
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


        for (size_t vid2 = 0; vid2 < lout.size(); ++vid2) {
//            assert(lout[vid2].size()==ou_label[vid2].size());

            sort(lout[vid2].begin(), lout[vid2].end());
            sort(ou_label[vid2].begin(), ou_label[vid2].end());


            if (!(lout[vid2].size() == ou_label[vid2].size())) {
                printf("vid:%d lvl:%d lout[vid2].size():%d ou_label[vid2].size():%d", vid2, v2l[vid2],
                       lout[vid2].size(),
                       ou_label[vid2].size());

                vector<size_t> &a = lout[vid2], &b = ou_label[vid2];
                vector<size_t> diff;

                if (a.size() > b.size()) {
                    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diff));
                } else {
                    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diff));
                }

                printf("{");
                for (int i = 0; i < diff.size(); ++i) {
                    min_diff = min(min_diff, diff[i]);
                    printf("%d,", diff[i]);
                }
                printf("}\n");

                continue;
            }
            for (size_t j = 0; j < lout[vid2].size(); ++j) {
                //                assert(lin[vid2][j]==in_label[vid2][j]);
                if (!(lout[vid2][j] == ou_label[vid2][j])) {
                    printf("lout[%d][%d]:%d==ou_label[%d][%d]:%d\n", vid2, j, lout[vid2][j], vid2, j,
                           ou_label[vid2][j]);
                }
            }
        }
        log("min_diff is: %d", min_diff);
        log("validation end.");
    }

} // namespace butterfly

#endif //EXP_BUTTERFLY_H
