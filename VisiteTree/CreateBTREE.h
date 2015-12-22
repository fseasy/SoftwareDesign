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
    cout <<"\n请输入节点信息（‘#’表示为空）\n" ;
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
        cout <<"\n输入"<<data <<"的左节点：\n" ;
        CreateBTREE(BT->lChild,lists) ;
        lists+="," ;
        cout <<"\n输入"<<data<<"的右节点：\n" ;
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
