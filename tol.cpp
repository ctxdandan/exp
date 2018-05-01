#include "lib/header.h"
//#include "lib/butterfly.h"
#include "lib/scc.h"
#include "lib/level_deciding.h"
#include "lib/DataConversion.h"
using namespace std;


int main() {
    double start_time=get_current_time();
//    dataconversion::convertchartobinarydata();
//    scc::test();
    level_decide::test();
//    butterfly::TOLIndexQuery();

    double end_time=get_current_time();
    log("start_time:%f s end_time:%f s duration:%f s",start_time,end_time,end_time-start_time);
    return 0;
//    sstreamtest();
}

//[C:\Users\Admin\CLionProjects\tol\tol.cpp.main()#20]# old laptop
// start_time:1522608723.080438 s end_time:1522608738.064266 s duration:14.983828 s

//[C:\Users\admin\CLionProjects\exp\tol.cpp.main()#22]# computer in lab
// start_time:1522632450.765156 s end_time:1522632456.914473 s duration:6.149317 s

