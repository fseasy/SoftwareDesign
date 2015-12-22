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
    cout <<"\t\t���ĸ��ֱ�����ʽ\n\n" ; 
    BTREE BT ;
    string lists ;
    cout <<"\n�Ƚ�������\n" ;
    CreateBTREE(BT,lists) ;
    modifyLists(lists) ;
    string menu = "\n\nѡ������ķ�ʽ��\n1.�ݹ�-�������\t2.�ǵݹ�-�������\n" ;
    menu+="3.�ݹ�-�������\t4.�ǵݹ�-�������\n" ;
    menu+="5.�ݹ�-�������\t6.�ǵݹ�-�������\n" ;
    menu+="7.�������\n8.�˳�\n\n" ;
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
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ݹ���������Ľ������Ϊ��\n\n" ;
            PreOrder(BT) ;
            break ;
        case '2' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ǵݹ���������Ľ������Ϊ��\n\n" ;
            noneRecursive_PreOrder(BT,S) ;
            break ;
        case '3' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ݹ���������Ľ������Ϊ��\n\n" ;
            InOrder(BT) ;
            break ;
        case '4' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ǵݹ���������Ľ������Ϊ��\n\n" ;
            noneRecursive_InOrder(BT,S) ;
            break ;
        case '5' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ݹ��������Ľ������Ϊ��\n\n" ;
            PostOrder(BT) ;
            break ;
        case '6' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n�ǵݹ��������Ľ������Ϊ��\n\n" ;
            noneRecursive_PostOrder(BT,S_PO) ;
            break ; 
        case '7' :
            cout <<"��������Ϊ��"<<lists <<endl ;
            cout <<"\n��������Ľ������Ϊ��\n\n" ;
            LevelOrder(BT,Q) ;
            break ;
        case '8' :
        return 0 ; 
        break ; 
        default:
            cout <<"��Ч��ѡ�\n" ;
            break ;
        }
    }

    return 0;
}
//�ݹ��������
void PreOrder(BTREE BT)
{
    if(BT != NULL)
    {
        cout <<BT->data <<" ";
        PreOrder(BT->lChild) ;
        PreOrder(BT->rChild) ;
    }
}
//�ǵݹ��������
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
//�ݹ��������
void InOrder(BTREE BT )
{
    if(BT != NULL)
    {
        InOrder(BT->lChild) ;
        cout <<BT->data <<" " ;
        InOrder(BT->rChild) ;
    }
}
//�ǵݹ��������
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
//�ݹ�������
void PostOrder(BTREE BT)
{
    if(BT!=NULL)
    {
        PostOrder(BT->lChild) ;
        PostOrder(BT->rChild) ;
        cout <<BT->data<<" " ;
    }
}
//�ǵݹ�������
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
               //һ��Ҫ�Ѱ��Ѿ���ʾ�ҽڵ��ѱ���ȡ�Ľڵ�ȫ��������Pop��
                while(!isEmpty(S)&&isRChildVisited(S))
                {
                    cout <<BT->data <<" " ;
                    Pop(S) ;
                    BT = Top(S) ;
                }
                //����ջ��Ԫ��һ�����ҽڵ�δ�������Ҽ����������ҽڵ�
                if(!isEmpty(S))
                {
                    changeRFlag(S) ;
                    BT = BT->rChild ;
                }

            }


        }
    }
}
//�������
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
