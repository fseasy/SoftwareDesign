#include "../lib_x/Graph_adjList.h"

using namespace std;

int main()
{
    fstream in("data.txt") ;
    if(in == NULL)
    {
            cout<<"�����ļ���ȡʧ��\n" ;
            return 0 ;
    }
    Graph x(in) ;
    for(int i = 0 ; i < x.getVertexNum() ; i++)
    {
        x.Dijkstra(i+1) ;
    }
    x.Floyd() ;
    return 0;
}
