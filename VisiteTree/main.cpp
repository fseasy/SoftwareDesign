#include <iostream>
#include "CreateBTREE.h"
#include "STACK.h"
#include "STACK_post_order.h"
#include "QUEUE_loop_array.h"
using namespace std;
void PreOrder(BTREE BT) ;
void noneRecursive_PreOrder(BTREE BT ,STACK & S) ;
void InOrder(BTREE BT ) ;
void noneRecursive_InOrder(BTREE BT , STACK& S) ;
void PostOrder(BTREE BT) ;
void noneRecursive_PostOrder(BTREE BT,STACK_PO & S) ;
void LevelOrder(BTREE BT,QUEUE & Q) ; 
int main()
{
    cout <<"\t\t树的各种遍历方式\n\n" ; 
    BTREE BT ;
    string lists ;
    cout <<"\n先建立树：\n" ;
    CreateBTREE(BT,lists) ;
    modifyLists(lists) ;
    string menu = "\n\n选择遍历的方式：\n1.递归-先序遍历\t2.非递归-先序遍历\n" ;
    menu+="3.递归-中序遍历\t4.非递归-中序遍历\n" ;
    menu+="5.递归-后序遍历\t6.非递归-后序遍历\n" ;
    menu+="7.层序遍历\n8.退出\n\n" ;
    STACK S ;
    STACK_PO S_PO ;
    QUEUE Q ; 
    while(cout <<menu)
    {
        char choice ;
        cin >>choice ;
        switch(choice)
        {
        case '1' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n递归先序遍历的结果序列为：\n\n" ;
            PreOrder(BT) ;
            break ;
        case '2' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n非递归先序遍历的结果序列为：\n\n" ;
            noneRecursive_PreOrder(BT,S) ;
            break ;
        case '3' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n递归中序遍历的结果序列为：\n\n" ;
            InOrder(BT) ;
            break ;
        case '4' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n非递归中序遍历的结果序列为：\n\n" ;
            noneRecursive_InOrder(BT,S) ;
            break ;
        case '5' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n递归后序遍历的结果序列为：\n\n" ;
            PostOrder(BT) ;
            break ;
        case '6' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n非递归后序遍历的结果序列为：\n\n" ;
            noneRecursive_PostOrder(BT,S_PO) ;
            break ; 
        case '7' :
            cout <<"建立的树为："<<lists <<endl ;
            cout <<"\n层序遍历的结果序列为：\n\n" ;
            LevelOrder(BT,Q) ;
            break ;
        case '8' :
        return 0 ; 
        break ; 
        default:
            cout <<"无效的选项。\n" ;
            break ;
        }
    }

    return 0;
}
//递归先序遍历
void PreOrder(BTREE BT)
{
    if(BT != NULL)
    {
        cout <<BT->data <<" ";
        PreOrder(BT->lChild) ;
        PreOrder(BT->rChild) ;
    }
}
//非递归先序遍历
void noneRecursive_PreOrder(BTREE BT ,STACK & S)
{
    MakeNull(S) ;
    while(BT!= NULL || !isEmpty(S))
    {
        if(BT!= NULL)
        {
            cout <<BT->data <<" " ;
            Push(BT,S) ;
            BT = BT->lChild ;
        }
        else
        {
            if(!isEmpty(S))
            {
                BT = Pop(S) ;
                BT = BT->rChild ;
            }
        }
    }
}
//递归中序遍历
void InOrder(BTREE BT )
{
    if(BT != NULL)
    {
        InOrder(BT->lChild) ;
        cout <<BT->data <<" " ;
        InOrder(BT->rChild) ;
    }
}
//非递归中序遍历
void noneRecursive_InOrder(BTREE BT , STACK& S)
{
    MakeNull(S) ;
    while(BT!= NULL || !isEmpty(S))
    {
        if(BT!= NULL)
        {
            Push(BT,S) ;
            BT = BT->lChild ;
        }
        else
        {
            if(!isEmpty(S))
            {
                BT = Pop(S) ;
                cout <<BT->data <<" " ;
                BT = BT->rChild ;
            }
        }
    }
}
//递归后序遍历
void PostOrder(BTREE BT)
{
    if(BT!=NULL)
    {
        PostOrder(BT->lChild) ;
        PostOrder(BT->rChild) ;
        cout <<BT->data<<" " ;
    }
}
//非递归后序遍历
void noneRecursive_PostOrder(BTREE BT,STACK_PO & S)
{
    MakeNull(S) ;
    while(BT!= NULL || !isEmpty(S))
    {

        if(BT!= NULL)
        {
            Push(BT,S) ;
            BT = BT->lChild ;
        }
        else
        {
            if(!isEmpty(S))
            {
                BT = Top(S) ;
               //一定要把把已经标示右节点已被读取的节点全部读出并Pop掉
                while(!isEmpty(S)&&isRChildVisited(S))
                {
                    cout <<BT->data <<" " ;
                    Pop(S) ;
                    BT = Top(S) ;
                }
                //现在栈顶元素一定是右节点未被访问且即将访问其右节点
                if(!isEmpty(S))
                {
                    changeRFlag(S) ;
                    BT = BT->rChild ;
                }

            }


        }
    }
}
//层序遍历
void LevelOrder(BTREE BT,QUEUE & Q)
{
     MakeNull(Q) ; 
     if(BT != NULL)
     {
          cout <<BT->data <<" " ; 
          EnQueue(BT,Q) ; 
          while(!isEmpty(Q))
          {
               BT = Front(Q) ; 
               DeQueue(Q) ; 
               if(BT->lChild!= NULL)
               {
                    cout <<BT->lChild->data <<" " ; 
                    EnQueue(BT->lChild,Q) ; 
               }
               if(BT->rChild!= NULL)
               {
                    cout <<BT->rChild->data <<" " ; 
                    EnQueue(BT->rChild,Q) ; 
               }
               
               
          }
     }
}
