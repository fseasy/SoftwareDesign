#include "AOEKeyPath_adjList.h"

using namespace std;

int main()
{
    fstream in("data.txt") ;
    if(in == NULL)
    {
        cout <<"�����ļ�����ʧ��\n" ;
        return 0 ;
    }
    AOE x(in) ;
    x.getKeyPath() ;
    return 0;
}
