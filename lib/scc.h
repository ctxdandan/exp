//
// Created by admin on 2018/4/1.
//

#ifndef EXP_SCC_H
#define EXP_SCC_H

#include<cstdio>
#include<algorithm>
#include<cstring>
#include "header.h"

using namespace std;

namespace scc {
    struct vertex {
        int dfn=0;
        int low=0;
        bool inStack = false;
    };
    vector<vertex> vertexes;
    vector<vector<int>> edges;
    vector<int> stack;
    int time = 0;

    void tarjan(int vid) {
        time++;
        vertexes[vid].dfn = vertexes[vid].low = time;
        vertexes[vid].inStack = true;
        stack.push_back(vid);

        for (int i = edges[vid].size() - 1; i >= 0; i--) {
            int childvid = edges[vid][i];
            if (!vertexes[childvid].dfn) {
                tarjan(childvid);
                vertexes[vid].low = min(vertexes[vid].low, vertexes[childvid].low);
            } else if (vertexes[childvid].inStack) {
                vertexes[vid].low = min(vertexes[vid].low, vertexes[childvid].dfn);
            }
        }
        if (vertexes[vid].low == vertexes[vid].dfn) {
            while (true) {
                int stack_top = stack.back();
                printf("%d ", stack_top + 1);
                vertexes[stack_top].inStack = false;
                stack.pop_back();
                if (stack_top == vid) {
                    printf("\n");
                    break;
                }
            }
        }
    }

    int test() {
        ifstream fin("C:\\Users\\Admin\\CLionProjects\\tol\\data\\tarjan_test");
        if (!fin.is_open()) {
            cerr << "file not found" << endl;
            exit(1);
        }

        int n, m;//n nodes and m edges
        fin >> n >> m;
        vertexes.resize(n);
        edges.resize(n);

        int x, y;
        for (int i = 0; i < m; i++) {
            fin >> x >> y;
            edges[x - 1].push_back(y - 1);
        }


        for (int i = 0; i < vertexes.size(); i++) {
            if (!vertexes[i].dfn) tarjan(i);
        }
        return 0;
    }
}


#endif //EXP_SCC_H
