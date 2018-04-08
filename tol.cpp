#include "lib/butterfly.h"
#include "lib/scc.h"
#include "lib/level_deciding.h"
#include "lib/DataConversion.h"
using namespace std;



void sstreamtest(){
    istringstream iss("I'm a c++ lover.");
    ostringstream oss;
    string s;
    while(iss>>s){
        oss<<s<<" ";
        cout<<s<<endl;
    }
    cout<<oss.str()<<endl;
    printf("%s cstr",oss.str().c_str());
}

void vectorallomemtest(){
    printf("before\n");
    vector<int> bytes;
//    bytes.resize(40000000000u);
    bytes.resize(250000000);
    printf("size of the data: %u\n",bytes.size());
    sleep(10);
    printf("after\n");
}

int main() {
    double start_time=get_current_time();
//    dataconversion::convertchartobinarydata();
//    vectorallomemtest();
    scc::test();
//    butterfly::TOLIndexQuery();
//    level_decide::test();
    double end_time=get_current_time();
    log("start_time:%f s end_time:%f s duration:%f s",start_time,end_time,end_time-start_time);
    return 0;
//    sstreamtest();
}

//[C:\Users\Admin\CLionProjects\tol\tol.cpp.main()#20]# old laptop
// start_time:1522608723.080438 s end_time:1522608738.064266 s duration:14.983828 s

//[C:\Users\admin\CLionProjects\exp\tol.cpp.main()#22]# computer in lab
// start_time:1522632450.765156 s end_time:1522632456.914473 s duration:6.149317 s

