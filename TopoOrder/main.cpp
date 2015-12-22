#include "diGraph_adjList.h"

using namespace std;

//使用邻接矩阵和邻接表的拓扑排序序列不同，因为拓扑排序不唯一
int main()
{
    fstream in("data.txt") ;
    if(in == NULL)
    {
        cout <<"数据文件读入失败\n" ;
        return 0 ;
    }
    DiGraph x(in) ;
    x.TopoOrder() ;
    return 0;
}
