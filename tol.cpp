#include "lib/butterfly.h"
#include "lib/scc.h"
#include "lib/level_deciding.h"
using namespace std;

double get_current_time()
{
    timeval t;
    gettimeofday(&t, 0);
    return (double)t.tv_sec + (double)t.tv_usec / 1000000;
}


int main() {
    double start_time=get_current_time();

//    scc::test();
    butterfly::TOLIndexQuery();
//    level_decide::test();

    double end_time=get_current_time();
    log("start_time:%f s end_time:%f s duration:%f s",start_time,end_time,end_time-start_time);
    return 0;
}

//[C:\Users\Admin\CLionProjects\tol\tol.cpp.main()#20]
// start_time:1522608723.080438 s end_time:1522608738.064266 s duration:14.983828 s