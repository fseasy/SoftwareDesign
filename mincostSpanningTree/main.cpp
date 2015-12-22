#include "../lib_x/Graph_adjList.h"
using namespace std;

int main()
{
    fstream in("data.txt") ;
    if(in == NULL)
    {
        cout <<"数据文件读取失败\n" ;
        return 0 ;
    }
    Graph x(in) ;
    x.DFSTraverse() ;
    x.printDFN() ;
    x.BFSTraverse() ;
    x.printBFN() ;
    x.Prim() ;
    x.Kruskal() ;
    return 0;
}
