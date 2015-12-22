#include <iostream>
#include "../lib_x/ThreadedTreeNEW.h"
using namespace std;

int main()
{
    ThreadedTree<char> x ;
    cout <<"���Ƚ���������\n" ;
    x.BTInit() ;
    char* menus = "\n1.���򻯶�����������\n2.����������������������\n3.����������������������\n4.�˳�\n" ;
    int choice ;
    while(cout <<menus)
    {
        cin >> choice ;
        switch(choice)
        {
        case 1:
        {
            cout <<"�������������������Ϊ\n" ;
            x.PreOrder(x.getRoot()) ;
            cout <<endl ;
            cout <<"�Զ�������������������\n" ;
            x.PreOrderTh() ;
            cout <<"�������������\n" ;
            cout <<"������������������Ϊ\n" ;
            x.ThPreOrder() ;
            x.ClearThread() ;
            break ;
        }
        case 2 :
        {
            cout <<"���������������������Ϊ\n" ;
            x.InOrder(x.getRoot()) ;
            cout <<endl ;
            cout <<"�Զ�������������������\n" ;
            x.InOrderTh() ;
            cout <<"�������������\n" ;
            cout <<"������������������Ϊ\n" ;
            x.ThInOrder() ;
            x.ClearThread() ;
            break ;
        }
        case 3 :
        {
            cout <<"�������������������Ϊ\n" ;
            x.PostOrder(x.getRoot()) ;
            cout <<endl ;
            cout <<"�Զ��������к���������\n" ;
            x.PostOrderTh() ;
            cout <<"�������������\n" ;
            cout <<"������������������Ϊ\n" ;
            x.ThPostOrder() ;
            x.ClearThread() ;
            break ;
        }
        case 4 :
            return 0 ;
        default :
            cout <<"��Ч��ѡ��\n" ;
        }
    }
    x.BTInit() ;
    return 0;
}