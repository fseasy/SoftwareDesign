#include <iostream>
#include <stdlib.h>
#include <string>
#include "../lib_x/Tree.h"
using namespace std;

int main()
{
    Tree<char> x ;
    cout <<"�Ƚ�������������\n" ;
    x.CreateTree() ;
    system("cls") ;
    cout <<"�����������������\n" ;
    string menus = "1.�����������\n2.���ĺ������\n3.���Ĳ������\n4.�˳�\n" ;
    char choice ;
    while(cout <<menus)
    {
        cin >> choice ;
        switch(choice)
        {
            case '1' :
            {
                cout <<"\n��������������\n\n" ;
                x.TreePreOrder() ;
                break ;
            }
            case '2' :
            {
                cout <<"\n���ĺ���������Ϊ\n\n" ;
                x.TreePostOrder() ;
                break ;
            }
            case '3' :
            {
                cout <<"\n���Ĳ���������Ϊ\n\n" ;
                x.TreeLevelOrder() ;
                break ;
            }
            case '4' :
            {
                return 0 ;
            }
            default :
            cout <<"INVALID CHOICE\n" ;
        }
    }
    x.TreeLevelOrder() ;
    cout <<endl ;
    x.TreePostOrder() ;
    return 0;
}
