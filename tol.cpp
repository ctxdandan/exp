#include "lib/DAGgenerator.h"
#include "lib/header.h"
#include "lib/butterfly.h"
//#include "lib/scc.h"
//#include "lib/level_deciding.h"
//#include "lib/DataConversion.h"
#include "lib/GraphDiff.h"

using namespace std;

void setdifftest() {
    vector<int> a = {1, 2, 3};
    vector<int> b = {3,2, 3, 4};
    vector<int> r;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(r));
    for (int i = 0; i < r.size(); ++i) {
        printf("%d,",r[i]);
    }
}


int main() {
//    dataconversion::convertchartobinarydata();
//    scc::test();
//    level_decide::test();
//    butterfly::TOLIndexQuery();
//    butterfly::validation();
//    setdifftest();
//    daggenerator::test();
    graphdiff::graphdiff();


    return 0;
//    sstreamtest();
}


