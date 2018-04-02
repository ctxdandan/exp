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
    size_t N, M;


    template<typename Vertex, typename Weight>
    void __bfs_labeling(DiGraph<Vertex, Weight> &G, Vertex u, Levels<Vertex> &level, Labels<Vertex> &Lsrc,
                        Labels<Vertex> &Ldst) {
        queue<Vertex> Q;
        set<Vertex> visited;

        for (const auto e: G[u]) if (level[u] < level[e.to]) Q.push(e.to);

        for (; !Q.empty();) {

            Vertex v = Q.front();
            Q.pop();

            if (!visited.insert(v).second) continue;
            Label<Vertex> Lu(Lsrc[u] | Label<Vertex>{u}), Lv(Ldst[v] | Label<Vertex>{v});
            if (((Lsrc[u] | Label<Vertex>{u}) & (Ldst[v] | Label<Vertex>{v})).empty()) {
                Ldst[v].insert(u);
                for (const auto e: G[v]) if (level[u] < level[e.to]) Q.push(e.to);
            }
        }
    }

    template<typename Vertex, typename Weight>
    void init(DiGraph<Vertex, Weight> &G, DiGraph<Vertex, Weight> &rG, Levels<Vertex> &level, Labels<Vertex> &Lin,
              Labels<Vertex> &Lout) {

        for (const auto vid: level) {//iterate with level order
//            log("lvl:%d",vid);
            size_t lvl = level[vid];
            __bfs_labeling(G, vid, level, Lout, Lin);
            __bfs_labeling(rG, vid, level, Lin, Lout);
        }
    }

    void loadGraph(string path) {
        //C:\Users\Admin\CLionProjects\tol\data\twitter_socialDAG_lvl_edgefmt
        ifstream ifs(path);
        if (!ifs) {
            log("file not found.")
        }
        int n,m;
        ifs>>n>>m;

    }

    void TOLIndexQuery() {//6.15s
//        fin.open("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tol1.dat");

        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_edgefmt");
        if (!ifs) {
            log("file not found.")
        }
        size_t N, M;
        ifs >> N >> M;

        DiGraph<size_t, int> G(N), rG(N);
        Levels<size_t> level(N);
        Labels<size_t> Lin(N), Lout(N);

        for (size_t i = 0; i < M; ++i) {

            size_t u, v;
            ifs >> u >> v;

            G[u].emplace_back(v, 1);
            rG[v].emplace_back(u, 1);
        }

        for (size_t i = 0; i < N; ++i) {
            size_t l;
            ifs >> l;
            level.add(i, l);
        }

        butterfly::init(G, rG, level, Lin, Lout);

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
