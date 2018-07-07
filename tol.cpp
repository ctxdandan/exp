#include "lib/DAGgenerator.h"
#include "lib/header.h"
#include "lib/butterfly.h"
#include "lib/preprocess.h"
#include "lib/scc.h"
#include "lib/level_deciding.h"
#include "lib/DataConversion.h"
#include "lib/GraphDiff.h"
#include "lib/IOtest.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>

using namespace std;

inline void usage(int exit_value = 0) {
    cerr << "exp help" << endl << endl;
    cerr << "-h\tshow help" << endl;
    cerr << "-a\tselect algorithm:tol(tol index alg), scc, pre, etc.." << endl;
    cerr << "-i\tinput file" << endl;
    cerr << "-o\toutput file" << endl;
    exit(exit_value);
}


int main(int argc, char *argv[]) {
    string alg;
    string ifpath;
    string ofpath;

    for (int i = 1; i < argc; ++i) {
        char *pchar = argv[i];
        switch (pchar[0]) {
            case '-': {
                switch (pchar[1]) {
                    case 'h':
                        usage();
                    case 'a':
                        alg = argv[++i];
                        break;
                    case 'i':
                        ifpath = argv[++i];
                        break;
                    case 'o':
                        ofpath = argv[++i];
                        break;
                    default:
                        cerr << ":error:unrecognition option -:" << pchar << endl;
                        usage(-1);
                }
                break;
            }
            default:
                cout << "arg: " << pchar << " is neglect!" << endl;
        }
    }

    cout << "alg: " << alg << endl
         << "ifpath: " << ifpath << endl
         << "ofpath: " << ofpath << endl;

    if (alg == "tol") {
        if (ifpath.size() == 0)
            usage(-1);
        butterfly::TOLIndexQuery(ifpath);
    } else if (alg == "pre") {
        if (ifpath.size() == 0 || ofpath.size() == 0) {
            fprintf(stderr, "missing argument: ifpath and ofpath\n");
            usage(-1);
        }
        preprocess::preprocess(ifpath, ofpath);
    } else if (alg == "scc") {
        if (ifpath.size() == 0 || ofpath.size() == 0) {
            fprintf(stderr, "missing argument: ifpath and ofpath\n");
            usage(-1);
        }
        scc::scc(ifpath, ofpath);

    }




//    dataconversion::convertchartobinarydata();
//    scc::scc();
//    level_decide::test();
//    butterfly::TOLIndexQuery();
//    butterfly::validation();
//    test();
//    daggenerator::test();
//    graphdiff::graphdiff();
//    iotest::writetest();
//    log("good?")








    return 0;
}


