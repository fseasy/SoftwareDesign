#include "diGraph_adjList.h"

using namespace std;

//ʹ���ڽӾ�����ڽӱ�������������в�ͬ����Ϊ��������Ψһ
int main()
{
    fstream in("data.txt") ;
    if(in == NULL)
    {
        cout <<"�����ļ�����ʧ��\n" ;
        return 0 ;
    }
    DiGraph x(in) ;
    x.TopoOrder() ;
    return 0;
}
