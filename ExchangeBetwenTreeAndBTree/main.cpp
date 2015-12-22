#include <iostream>
#include <stdlib.h>
#include <string>
#include "../lib_x/Tree.h"
/**
    **程序名称：邻接表树于二叉链表树的建立、相互转换，森林
    **数据结构：树（包含邻接表型和二叉链表型）
*/
using namespace std;

int main()
{
    Tree<char>* x = NULL ;
    string menus = "\t邻接表树于二叉链表树的建立、相互转换，森林\n" ;
    menus+="1.建立邻接表树\n2.建立二叉链表树\n3.将树合并为森林\n4.退出\n" ;
    char choice ;
    while(cout << menus)
    {
        cin >> choice ;
        switch(choice)
        {
        case '1' :
        {
            x = new Tree<char>() ;
            x->CreateListTree() ;
            cout <<"邻接表树创建成功\n" ;
            string menusSec = "\n1.查看邻接表树\n2.将邻接表型转换为二叉链表型树\n" ;
            menusSec+="3.查看转换的二叉链表树\n4.返回主菜单\n" ;
            char choiceSec = '0' ;
            while(choiceSec != '4' && cout << menusSec)
            {
                cin >> choiceSec ;
                switch(choiceSec)
                {
                case '1':
                {
                    x->listOrder() ;
                    break ;
                }
                case '2':
                {
                    x->listToTree() ;
                    cout <<"\n转换完成\n" ;
                    break ;
                }
                case '3' :
                {
                    cout <<"\n先序遍历结果为\n\n" ;
                    x->TreePreOrder() ;
                    break ;
                }
                case '4' :
                {
                    system("cls") ;
                    break ;
                }
                default :
                    cout <<"INVALID CHOICE\n" ;
                }
            }
            delete x ;
            break ;
        }
        case '2' :
        {
            x = new Tree<char>() ;
            x->CreateTree() ;
            cout <<"二叉链表树建立成功\n" ;
            string menusSec = "1.先序查看二叉链表树\n2.将二叉链表树转换为邻接表型树\n" ;
            menusSec+="3.查看转换的邻接表树\n4.返回主菜单\n" ;
            char choiceSec = '0' ;
            while(choiceSec != '4' && cout <<menusSec  )
            {
                cin >> choiceSec ;
                switch(choiceSec)
                {
                case '1' :
                {
                    cout <<"先序遍历的结果为\n\n" ;
                    x->TreePreOrder() ;
                    break ;
                }
                case '2' :
                {
                    x->treeToList() ;
                    cout <<"转换完成\n" ;
                    break ;
                }
                case '3' :
                {
                    x->listOrder() ;
                    break ;
                }
                case '4' :
                    system("cls") ;
                    break ;
                default :
                    cout <<"INVALID CHOICE\n" ;
                }
            }
        }
        case '3' :
        {
            int num ;
            cout <<"请输入树个棵树\n" ;
            cin >> num ;
            if(num < 1)
            {
                cout <<"INVALID INPUTS\n" ;
                break ;
            }
            Tree<char>* trees[num] ;
            for(int i = 1 ; i<= num ; i++)
            {
                cout <<"\n建立第"<<i<<"棵树\n\n" ;
                trees[i-1] = new Tree<char>() ;
                trees[i-1]->CreateTree() ;
                cout <<"第"<<i<<"棵树建立完成\n" ;
            }
            cout <<"\n开始合并为森林\n\n" ;
            for(int i = 2 ; i<= num ; i++)
            {
                trees[0]->Unoin(trees[i-1]) ;
                cout <<"合并第一棵和"<<i<<"棵树...\n" ;
            }
            cout <<"合并完成\n合并后森林的先序序列为\n\n" ;
            trees[0]->TreePreOrder() ;
        }
        case '4' :
            return 0 ;
        default :
            cout <<"INVALID CHOICE\n" ;
        }
    }

    return 0;
}
