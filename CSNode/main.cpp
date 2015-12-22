#include <iostream>
#include <stdlib.h>
#include <string>
#include "../lib_x/Tree.h"
using namespace std;

int main()
{
    Tree<char> x ;
    cout <<"先建立二叉链表树\n" ;
    x.CreateTree() ;
    system("cls") ;
    cout <<"二叉链表树建立完成\n" ;
    string menus = "1.树的先序遍历\n2.树的后序遍历\n3.树的层序遍历\n4.退出\n" ;
    char choice ;
    while(cout <<menus)
    {
        cin >> choice ;
        switch(choice)
        {
            case '1' :
            {
                cout <<"\n树的先序遍历结果\n\n" ;
                x.TreePreOrder() ;
                break ;
            }
            case '2' :
            {
                cout <<"\n树的后序遍历结果为\n\n" ;
                x.TreePostOrder() ;
                break ;
            }
            case '3' :
            {
                cout <<"\n树的层序遍历结果为\n\n" ;
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
