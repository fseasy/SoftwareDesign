#ifndef CREATEBTREE_H_INCLUDED
#define CREATEBTREE_H_INCLUDED
#include <iostream>
#include <string>

using namespace std ;

typedef char type ;
struct node
{
    type data ;
    node * lChild ;
    node * rChild ;
} ;
typedef node * BTREE ;

void CreateBTREE(BTREE & BT ,string & lists)
{
    cout <<"\n������ڵ���Ϣ����#����ʾΪ�գ�\n" ;
    type data ;
    cin >> data  ;
    lists+=data ;
    if(data == '#')
    {
        BT = NULL ;
    }
    else
    {
        BT = new node ;
        BT->data = data ;
        lists+="("  ;
        cout <<"\n����"<<data <<"����ڵ㣺\n" ;
        CreateBTREE(BT->lChild,lists) ;
        lists+="," ;
        cout <<"\n����"<<data<<"���ҽڵ㣺\n" ;
        CreateBTREE(BT->rChild,lists) ;
        lists+=")" ;
    }
}
void modifyLists(string & lists)
{
    int position ;
    while((position = lists.find("(#,#)"))!= -1)
    {
        lists.erase(position,5) ;
    }
}
#endif // CREATEBTREE_H_INCLUDED
