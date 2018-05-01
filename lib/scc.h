//
// Created by admin on 2018/4/1.
//

#ifndef EXP_SCC_H
#define EXP_SCC_H

#include "header.h"

using namespace std;

namespace scc {
    struct vertex {
        vertex() {
            dfn = 0;
            low = 0;
            inStack = false;
        }

        int dfn = 0;
        int low = 0;
        bool inStack = false;
        int newid;
    };

    vector<vertex> vertexes;
    vector<vector<int> > edges;
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

    void norecursivetarjan(int vid) {
        vector<int> vidStack;
        vector<int> nbidxStack;

        vidStack.push_back(vid);
        nbidxStack.push_back(edges[vid].size() - 1);

        time++;
        vertexes[vid].dfn = vertexes[vid].low = time;
        vertexes[vid].inStack = true;
        stack.push_back(vid);


        abc:
        while (!vidStack.empty()) {
            vid = vidStack.back();
            for (int i = nbidxStack.back(); i >= 0; i--) {
                int childvid = edges[vid][i];

                if (!vertexes[childvid].dfn) {
                    nbidxStack.back() = i - 1;

                    vidStack.push_back(childvid);
                    nbidxStack.push_back(edges[childvid].size() - 1);

                    time++;
                    vertexes[childvid].dfn = vertexes[childvid].low = time;
                    vertexes[childvid].inStack = true;
                    stack.push_back(childvid);

                    goto abc;

                    vertexes[vid].low = min(vertexes[vid].low, vertexes[childvid].low);
                } else if (vertexes[childvid].inStack) {
                    vertexes[vid].low = min(vertexes[vid].low, vertexes[childvid].dfn);
                }
            }
            //iterated all neighbors, pop back
            if (vidStack.size() >= 2) {
                vertexes[vidStack[vidStack.size() - 2]].low =
                        min(vertexes[vidStack[vidStack.size() - 2]].low, vertexes[vidStack.back()].low);
            }

            if (vertexes[vid].low == vertexes[vid].dfn) {
                while (true) {
                    int stack_top = stack.back();
//                    printf("%d ", stack_top + 1);
                    vertexes[stack_top].inStack = false;
                    vertexes[stack_top].low = vertexes[vid].low;
                    stack.pop_back();
                    if (stack_top == vid) {
//                        printf("\n");
                        break;
                    }
                }
            }

            vidStack.pop_back();
            nbidxStack.pop_back();

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
            if (!vertexes[i].dfn)
                tarjan(i);
//                norecursivetarjan(i);
        }
    }

    void loadgraph1() {
//        //twitter_social total have 38 sccs, which contain total 1810 vertexes, 47.6 vertexes per scc on average
//        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_social");
////        ifstream ifs("C:\\Users\\Admin\\CLionProjects\\exp\\data\\tarjan_test");
//        if (!ifs) {
//            log("file not fount");
//        }
//        string line;
//        string word;
//        getline(ifs, line);
//        getline(ifs, line);
//
//        istringstream iss(line);
//        iss >> word;
//        int n, m;
//        iss >> m >> n;
//        log("the graph has %d vertexes and %d edges.", n, m);
//        vertexes.resize(n);
//        edges.resize(n);
//        int from, to;
//        for (int i = 0; i < m; i++) {
//            getline(ifs, line);
//            iss = istringstream(line);
//
//            iss >> from >> to;
//            edges[from - 1].push_back(to - 1);
//        }
//        ifs.close();
    }

    void loadgraph2() {
        double starttime = get_current_time();
        //the graph has 11316811 vertexes and 85331845 edges.
        FILE *fp = fopen("E:\\twitter_big\\Twitter-dataset\\data\\edges.csv.bin", "rb");
//        FILE *fp = fopen("D:\\Dataset\\Twitter-dataset\\data\\edges.csv.bin", "rb");
        if (fp == NULL) {
            log("file opened failed.");
        }
        int buffsize = 100000000;
//        int buffsize=2;
        int *x = new int[buffsize];
        size_t count = 0;
        int n = 11316811, m = 85331845;
        vertexes.resize(n);
        edges.resize(n);
        while ((count = fread(x, sizeof(int), buffsize, fp)) > 0) {
            for (int i = 0; i < count; i += 2) {
                edges[x[i] - 1].push_back(x[i + 1] - 1);
            }
            if (feof(fp)) log("count:%d", count);
        }
        log("count:%d", count);
        if (ferror(fp)) log ("Error Writing to myfile.txt\n");//end of the file reached? bug!!!
        if (feof(fp)) log ("End-of-File reached.");
        fclose(fp);
        delete[] x;
        double endtime = get_current_time();
        log("loading Graph consumed %f seconds, the graph has %d vertexes and %d edges.", endtime - starttime, n, m);
    }

    void loadgraph3(){
//#define debug2
#ifdef debug2
        FILE * fin=fopen("C:\\\\Users\\\\admin\\\\ClionProjects\\\\exp\\\\data\\\\testdata.bin","rb");
#else
        FILE * fin=fopen("out.twitter_mpi_1.bin","rb");
#endif
        if(fin==NULL){
            log("fin opened failed.")
        }
        int n = 52579682;
        long long int_nums;
        fseek(fin,0,SEEK_END);
        int_nums=ftell(fin)/4;
        rewind(fin);
        log("size of file is %lld 4bytes",int_nums)
        int buffsize = 100000000;
        int *x = new int[buffsize];
        size_t count=0;
        vertexes.resize(n);
        edges.resize(n);

        double start_time=get_current_time();
        while ((count = fread(x, sizeof(int), buffsize, fin)) > 0) {
            for (int i = 0; i < count; i += 2) {
                edges[x[i] - 1].push_back(x[i + 1] - 1);
            }
            if (feof(fin)) log("count:%d", count);
        }
        log("count:%d", count);
        if (ferror(fin)) log ("Error Writing to myfile.txt\n");//end of the file reached? bug!!!
        if (feof(fin)) log ("End-of-File reached.");
        fclose(fin);

        vertexes.shrink_to_fit();
        edges.shrink_to_fit();
        for(int i=0;i<n;i++){
            edges[i].shrink_to_fit();
        }
        log("reading file consumed %f seconds",get_current_time()-start_time)
    }

    void findSCC() {
        log("tarjan start.");
        double starttime = get_current_time();
        for (int i = 0; i < vertexes.size(); i++) {
            if (!vertexes[i].dfn)
//                tarjan(i);
                norecursivetarjan(i);
        }
        double endtime = get_current_time();
        log("tarjan Finished in %f seconds.", endtime - starttime);
    }

    void dumpgraph1() {
        double starttime = get_current_time();
        //assign new vid
        int vid = 0;
        map<int, int> nid; //old id-->new id
        for (int i = 0; i < vertexes.size(); i++) {
            if (nid.find(vertexes[i].low) == nid.end()) {
                nid[vertexes[i].low] = vid;
                vertexes[i].newid=vid;
                vid++;
            }else{
                vertexes[i].newid=nid[vertexes[i].low];
            }
        }
        int nn = nid.size(), nm = 0;
        nid.clear();
        log("Assign new vid finished.")
        //reconstruct DAG
        map<int, set<int> > graph;
        for (int from = 0; from < edges.size(); ++from) {
            for (int to = 0; to < edges[from].size(); ++to) {

                int srcid = vertexes[from].newid;
                int dstid = vertexes[edges[from][to]].newid;
                if (srcid == dstid)continue;
                graph[srcid].insert(dstid);
            }
        }
        log("reconstruct DAG finished.")
        for (map<int, set<int> >::iterator src = graph.begin(); src != graph.end(); ++src) {
            nm += src->second.size();
        }
        log("Anaylysis Finished. There are %d conponents, and the new graph has %d edges.", nn, nm);
        //output DAG C:\Users\admin\CLionProjects\exp\data
        log("starting writing to file......")
        ofstream ofs("C:\\Users\\admin\\CLionProjects\\exp\\data\\twitter_socialDAG");
        if (ofs) {
            ofs << nn << " " << nm << endl;
            for (map<int, set<int> >::iterator src = graph.begin(); src != graph.end(); ++src) {
                for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {
                    ofs << src->first << " " << *dst << endl;
                }
            }
        } else {
            log("file not opened!");
        }
        ofs.close();
        log("finish writing to file.");
        double endtime = get_current_time();
        log("dumpgraph finished in %f seconds.", endtime - starttime);
    }

    void dumpgraph2() {
        double starttime = get_current_time();
        //assign new vid
        int vid = 0;
        map<int, int> nid; //old id-->new id
        for (int i = 0; i < vertexes.size(); i++) {
            if (nid.find(vertexes[i].low) == nid.end()) {
                nid[vertexes[i].low] = vid;
                vertexes[i].newid=vid;
                vid++;
            }else{
                vertexes[i].newid=nid[vertexes[i].low];
            }
        }
        int nn = nid.size(), nm = 0;
        nid.clear();
        log("Assign new vid finished.")
        //reconstruct DAG
        map<int, set<int> > graph;
        for (int from = 0; from < edges.size(); ++from) {
            for (int to = 0; to < edges[from].size(); ++to) {

                int srcid = vertexes[from].newid;
                int dstid = vertexes[edges[from][to]].newid;
                if (srcid == dstid)continue;
                graph[srcid].insert(dstid);
            }
        }
        log("reconstruct DAG finished.")
        for (map<int, set<int> >::iterator src = graph.begin(); src != graph.end(); ++src) {
            nm += src->second.size();
        }
        log("Anaylysis Finished. There are %d conponents, and the new graph has %d edges.", nn, nm);
        //output DAG
        log("starting writing to file......")
        //E:\twitter_big\Twitter-dataset\data\edges_DAG.csv.bin
        FILE * fp=fopen("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG.csv.bin","wb");
        if (fp == NULL) {
            log("file opened failed.");
        } else{
            fwrite(&nn, sizeof(int),1,fp);
            fwrite(&nm, sizeof(int),1,fp);
            for (map<int, set<int> >::iterator src = graph.begin(); src != graph.end(); ++src) {
                for (set<int>::iterator dst = src->second.begin(); dst != src->second.end(); ++dst) {
                    fwrite(&(src->first), sizeof(int),1,fp);
                    fwrite(&(*dst), sizeof(int),1,fp);
                }
            }
        }
        fclose(fp);
        log("finish writing to file.");
        double endtime = get_current_time();
        log("dumpgraph finished in %f seconds.", endtime - starttime);
    }

    void dumpgraph3() {
        double starttime = get_current_time();
        //assign new vid
        int vid = 0;
        map<int, int> nid; //old id-->new id
        for (int i = 0; i < vertexes.size(); i++) {
            if (nid.find(vertexes[i].low) == nid.end()) {
                nid[vertexes[i].low] = vid;
                vertexes[i].newid=vid;
                vid++;
            }else{
                vertexes[i].newid=nid[vertexes[i].low];
            }
        }
        int nn = nid.size(), nm = 0;
        nid.clear();
        log("Assign new vid finished.")
        //reconstruct DAG
        vector<set<int> > graph;
        graph.resize(nn);
        for (int from = 0; from < edges.size(); ++from) {
            for (int to = 0; to < edges[from].size(); ++to) {
                int srcid = vertexes[from].newid;
                int dstid = vertexes[edges[from][to]].newid;
                if (srcid == dstid)continue;
                graph[srcid].insert(dstid);
            }
        }
        log("reconstruct DAG finished.")
        for (vector<set<int> >::iterator src = graph.begin(); src != graph.end(); ++src) {
            nm += src->size();
        }
        log("Anaylysis Finished. There are %d conponents, and the new graph has %d edges.", nn, nm);
        //output DAG
        log("starting writing to file......")
        //E:\twitter_big\Twitter-dataset\data\edges_DAG.csv.bin
        FILE * fp=fopen("out.twitter_mpi_1.DAG.bin","wb");
        if (fp == NULL) {
            log("file opened failed.");
        } else{
//            fwrite(&nn, sizeof(int),1,fp);
//            fwrite(&nm, sizeof(int),1,fp);
            for(int src=0;src<graph.size();++src){
                for (set<int>::iterator dst=graph[src].begin();dst!=graph[src].end();++dst){
                    fwrite(&src, sizeof(int),1,fp);
                    fwrite(&(*dst), sizeof(int),1,fp);
                }
            }
        }
        fclose(fp);
        log("finish writing to file.");
        double endtime = get_current_time();
        log("dumpgraph finished in %f seconds.", endtime - starttime);
    }

    int test() {
        loadgraph3();
//        loadgraph2();
//        loadgraph1();
        findSCC();
//        dumpgraph1();
        dumpgraph3();
//        dumpgraph2();
//        example1();
        return 0;
    }
}


#endif //EXP_SCC_H
