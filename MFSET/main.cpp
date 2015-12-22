#include <iostream>
#include "../lib_x/MFSET.h"
/**
    程序名称：并查集的等价分类
*/
using namespace std;

int main()
{
    Mfset x(20) ;
    x.Equivalence() ;
    x.printMFSET() ;
    return 0;
}
