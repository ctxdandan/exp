//
// Created by admin on 2018/4/1.
//

#ifndef EXP_BUTTERFLY_H
#define EXP_BUTTERFLY_H

#include "header.h"
#include "graph.h"
#include "label.h"
#include "level.h"

using namespace std;

namespace butterfly {
    bool intersection(size_t src, vector<size_t> srcLout, size_t dst, vector<size_t> dstLin) {
        srcLout.push_back(src);
        dstLin.push_back(dst);
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
    }

    size_t N, M;
    vector<vector<size_t>> edges;
    vector<vector<size_t>> redges;
    vector<vector<size_t>> lin;
    vector<vector<size_t>> lout;
    vector<size_t> v2l;
    vector<size_t> l2v;


    void zjh_init() {
        for (size_t l = 0; l < l2v.size(); l++) {
//            if(l%(l2v.size()/100)==0)
            log("proceeding %d",l);
            zjh_bfs_labeling(edges,l2v[l],v2l,lin,lout);
            zjh_bfs_labeling(redges,l2v[l],v2l,lout,lin);
        }
    }
    void TOLIndexQuery() {//4.55s
//        fin.open("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tol1.dat");

//        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_edgefmt");
        ifstream ifs("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG_lvl_edgefmt");

        if (!ifs) {
            log("file not found.")
        }
        ifs >> N >> M;
        edges.resize(N);
        redges.resize(N);
        v2l.resize(N);
        l2v.resize(N);
        lin.resize(N);
        lout.resize(N);

//        DiGraph<size_t, int> G(N), rG(N);
//        Levels<size_t> level(N);
//        Labels<size_t> Lin(N), Lout(N);

        for (size_t i = 0; i < M; ++i) {

            size_t u, v;
            ifs >> u >> v;

            edges[u].push_back(v);
            redges[v].push_back(u);

//            G[u].emplace_back(v, 1);
//            rG[v].emplace_back(u, 1);
        }

        for (size_t i = 0; i < N; ++i) {
            size_t l;
            ifs >> l;
            v2l[i] = l;
            l2v[l] = i;
//            level.add(i, l);
        }
        double starttime = get_current_time();
//        butterfly::init(G, rG, level, Lin, Lout);
        butterfly::zjh_init();

        double endtime = get_current_time();
        log("butterfly consumed %f seconds.", endtime - starttime);

//        for (size_t i = 0; i < N; ++i) {
//
//            cout << char('a' + i) << "(" << level[i] << "):" << endl;
//            cout << "  Lin : ";
//            for (const auto e:  Lin[i]) cout << char('a' + e) << ", ";
//            cout << endl;
//            cout << "  Lout: ";
//            for (const auto e: Lout[i]) cout << char('a' + e) << ", ";
//            cout << endl;
//        }


    }

} // namespace butterfly

#endif //EXP_BUTTERFLY_H
