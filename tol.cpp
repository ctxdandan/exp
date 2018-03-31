#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <fstream>
#include "header.h"
#include "lib/graph.h"
#include "lib/label.h"
#include "lib/level.h"

using namespace std;

namespace butterfly {

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
            cout << "query " << char('a' + u) << "(" << level[u] << ") -> " << char('a' + v) << "(" << level[v] << ")"
                 << endl;

            Label<Vertex> Lu(Lsrc[u] | Label<Vertex>{u}), Lv(Ldst[v] | Label<Vertex>{v});
            cout << "Label " << char('a' + u) << "(" << level[u] << "): ";
            for (const auto e: Lu) cout << char('a' + e) << ", " << endl;
            cout << "Label " << char('a' + v) << "(" << level[v] << "): ";
            for (const auto e: Lv) cout << char('a' + e) << ", " << endl;
            cout << "  -- intersection --> ";
            for (const auto e: Lu & Lv) cout << char('a' + e) << ", " << endl;

            if (((Lsrc[u] | Label<Vertex>{u}) & (Ldst[v] | Label<Vertex>{v})).empty()) {

                Ldst[v].insert(u);
                cout << char('a' + u) << "(" << level[u] << ") add label to " << char('a' + v) << "(" << level[v] << ")"
                     << endl;

                for (const auto e: G[v]) if (level[u] < level[e.to]) Q.push(e.to);
            }
        }
    }

    template<typename Vertex, typename Weight>
    void init(DiGraph<Vertex, Weight> &G, DiGraph<Vertex, Weight> &rG, Levels<Vertex> &level, Labels<Vertex> &Lin,
              Labels<Vertex> &Lout) {

        for (const auto vid: level) {//iterate with level order

            size_t lvl = level[vid];
            log("start Lin labeling for %c (level: %d)", 'a' + vid, lvl);
            cout << "start Lin labeling for " << char('a' + vid) << "(level: " << lvl << ")" << endl;
            __bfs_labeling(G, vid, level, Lout, Lin);
            log("start Lout labeling for %c (level: %d)", 'a' + vid, lvl);
            cout << "start Lout labeling for " << char('a' + vid) << "(level: " << lvl << ")" << endl;
            __bfs_labeling(rG, vid, level, Lin, Lout);
        }
    }

} // namespace butterfly

int main() {
    streambuf *backup;
    ifstream fin;
    fin.open("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tol1.dat");
    backup = cin.rdbuf();   // back up cin's streambuf
    cin.rdbuf(fin.rdbuf()); // assign file's streambuf to cin
// ... cin will read from file
//    cin.rdbuf(backup);     // restore cin's original streambuf

    size_t N, M;
    cin >> N >> M;

    DiGraph<size_t, int> G(N), rG(N);
    Levels<size_t> level(N);
    Labels<size_t> Lin(N), Lout(N);

    for (size_t i = 0; i < M; ++i) {

        size_t u, v;
        cin >> u >> v;

        G[u].emplace_back(v, 1);
        rG[v].emplace_back(u, 1);
    }

    for (size_t i = 0; i < N; ++i) {
        size_t l;
        cin >> l;
        level.add(i, l);
    }

    butterfly::init(G, rG, level, Lin, Lout);

    for (size_t i = 0; i < N; ++i) {

        cout << char('a' + i) << "(" << level[i] << "):" << endl;
        cout << "  Lin : ";
        for (const auto e:  Lin[i]) cout << char('a' + e) << ", ";
        cout << endl;
        cout << "  Lout: ";
        for (const auto e: Lout[i]) cout << char('a' + e) << ", ";
        cout << endl;
    }

    size_t Query;
    cin >> Query;

    for (; Query--;) {

        size_t u, v;
        cin >> u >> v;

        cout << "query: " << char('a' + u) << " -> " << char('a' + v) << " reachable?" << endl;
        cout << "  --> "
             << (((Lout[u] | Label<size_t>{u}) & (Lin[v] | Label<size_t>{v})).empty() ? "impossible!" : "possible!")
             << endl;
    }

    return 0;
}
