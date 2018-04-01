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

namespace scc{
    struct vertex{
        int DFN;
        int LOW;
        bool visited= false;
    };
    vector<vertex> vertexes;
    vector<vector<int>> edges;
    vector<int> new_stack;
    int time=0;

    void tarjan2(int vid){
        time++;
        vertexes[vid].DFN=vertexes[vid].LOW=time;
        vertexes[vid].visited=true;
        new_stack.push_back(vid);

        for(int i=edges[vid].size()-1;i>=0;i--){
            int childvid=edges[vid][i];
            if(!vertexes[childvid].DFN){//如果没访问过
                tarjan2(childvid);
                vertexes[vid].LOW=min(vertexes[vid].LOW,vertexes[childvid].LOW);
            } else if(vertexes[childvid].visited){//如果访问过，并且还在栈里。
                vertexes[vid].LOW=min(vertexes[vid].LOW,vertexes[childvid].DFN);
            }
        }
        if(vertexes[vid].LOW==vertexes[vid].DFN){
            while(true){
                int stack_top=new_stack.back();
                printf("%d ",stack_top+1);
                vertexes[stack_top].visited=false;
                new_stack.pop_back();
                if(stack_top==vid){
                    printf("\n");
                    break;
                }
            }
        }
    }

    int test()
    {
        streambuf *backup;
        ifstream fin;
        fin.open("C:\\Users\\Admin\\CLionProjects\\exp\\data\\tarjan_test");
        if(!fin.is_open()){
            cerr<<"file not found"<<endl;
            exit(1);
        }
        backup = cin.rdbuf();   // back up cin's streambuf
        cin.rdbuf(fin.rdbuf()); // assign file's streambuf to cin
// ... cin will read from file
//    cin.rdbuf(backup);     // restore cin's original streambuf

        int n,m;//n nodes and m edges
        cin>>n>>m;
        vertexes.resize(n);
        edges.resize(n);

        int x,y;
        for(int i=0;i<m;i++)
        {
            cin>>x>>y;
            edges[x-1].push_back(y-1);
        }


        for(int i=0;i<vertexes.size();i++){
            if(!vertexes[i].DFN) tarjan2(i);
        }
        return 0;
    }
}




#endif //EXP_SCC_H
