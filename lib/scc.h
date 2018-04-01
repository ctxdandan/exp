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
        int dfn = 0;
        int low = 0;
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
//                printf("%d ", stack_top + 1);
                vertexes[stack_top].inStack = false;
                vertexes[stack_top].low = vertexes[vid].low;
                stack.pop_back();
                if (stack_top == vid) {
//                    printf("\n");
                    break;
                }
            }
        }
    }

    void example1() {
        ifstream fin("C:\\Users\\Admin\\CLionProjects\\exp\\data\\tarjan_test");
        if (!fin) {
            cerr << "file not found" << endl;
            exit(1);
        }

        int n, m;//n nodes and m edges
        fin >> n >> m;

        vertexes.resize(n);
        edges.resize(n);

        int from, to;
        for (int i = 0; i < m; i++) {
            fin >> from >> to;
            edges[from - 1].push_back(to - 1);
        }
        fin.close();

        for (int i = 0; i < vertexes.size(); i++) {
            if (!vertexes[i].dfn) tarjan(i);
        }

        //assign new vid
        int vid = 0;
        map<int, int> nid;
        for (int i = 0; i < vertexes.size(); i++) {
            if (nid.find(vertexes[i].low) == nid.end()) {
                nid[vertexes[i].low] = vid++;
            }
        }
        int nn = nid.size(), nm=0;
        //reconstruct DAG
        map<int, set<int>> graph;
        for (from = 0; from < edges.size(); ++from) {
            for (to = 0; to < edges[from].size(); ++to) {

                int srcid = nid[vertexes[from].low];
                int dstid = nid[vertexes[edges[from][to]].low];
                if(srcid==dstid)continue;
                graph[srcid].insert(dstid);
            }
        }
        log("reconstruct DAG finished.")
        for (map<int, set<int>>::iterator src = graph.begin(); src != graph.end(); ++src) {
//                if(src->second.size()>100){
            log("before:nm:%d size:%d",nm,src->second.size());
            nm+=src->second.size();
            log("after:nm:%d size:%d",nm,src->second.size());
//                }else
//                    nm+=src->second.size();
            for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {
            }
        }

        log("Anaylysis Finished. There are %d conponents, and the new graph has %d edges.",nn,nm);
        //output DAG
        for (map<int, set<int>>::iterator src = graph.begin(); src != graph.end(); ++src) {
            for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {
                printf("%d %d\n", src->first, *dst);
            }
        }


    }

    void convert_twitter2DAG() {
        //twitter_social total have 38 sccs, which contain total 1810 vertexes, 47.6 vertexes per scc on average
        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_social");
//        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\tarjan_test");
        if (!ifs) {
            log("file not fount");
        }
        string line;
        string word;
        getline(ifs, line);
        getline(ifs, line);

        istringstream iss(line);
        iss >> word;
        int n, m;
        iss >> m >> n;
        log("the graph has %d vertexes and %d edges.", n, m);
        vertexes.resize(n);
        edges.resize(n);
        int from, to;
        for (int i = 0; i < m; i++) {
            getline(ifs, line);
            iss = istringstream(line);

            iss >> from >> to;
            edges[from - 1].push_back(to - 1);
        }
        ifs.close();

        for (int i = 0; i < vertexes.size(); i++) {
            if (!vertexes[i].dfn) tarjan(i);
        }
        log("tarjan Finished.")

        //assign new vid
        int vid = 0;
        map<int, int> nid;
        for (int i = 0; i < vertexes.size(); i++) {
            if (nid.find(vertexes[i].low) == nid.end()) {
                nid[vertexes[i].low] = vid++;
            }
        }
        int nn = nid.size(), nm=0;
        //reconstruct DAG
        map<int, set<int>> graph;
        for (from = 0; from < edges.size(); ++from) {
            for (to = 0; to < edges[from].size(); ++to) {

                int srcid = nid[vertexes[from].low];
                int dstid = nid[vertexes[edges[from][to]].low];
                if(srcid==dstid)continue;
                graph[srcid].insert(dstid);
            }
        }
        log("reconstruct DAG finished.")
        for (map<int, set<int>>::iterator src = graph.begin(); src != graph.end(); ++src) {
            nm+=src->second.size();
            for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {

            }
        }

        log("Anaylysis Finished. There are %d conponents, and the new graph has %d edges.",nn,nm);
        //output DAG
        log("starting writing to file......")
        ofstream ofs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG");
        if (ofs) {
            ofs<<nn<<" "<<nm<<endl;
            for (map<int, set<int>>::iterator src = graph.begin(); src != graph.end(); ++src) {
                for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {
                    ofs<<src->first<<" "<<*dst<<endl;
                }
            }
        } else{
            log("file not opened!");
        }
        ofs.close();
        log("finish writing to file.")


    }

    int test() {
        convert_twitter2DAG();
//        example1();
        return 0;
    }
}


#endif //EXP_SCC_H
