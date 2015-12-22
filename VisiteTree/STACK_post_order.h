#ifndef STACK_POST_ORDER_H_INCLUDED
#define STACK_POST_ORDER_H_INCLUDED
#include "CreateBTREE.h"
#define MAX_SIZE 100
typedef node* pointer ;
struct cellType
{
    pointer val ;
    bool lFlag ;
    bool rFlag ; 
} ;
struct STACK_PO
{
    cellType data[MAX_SIZE] ;
    int top ;
} ;
void MakeNull(STACK_PO &S)
{
    S.top = -1 ;
    for(int i = 0 ; i < MAX_SIZE ; i++)
    {
        S.data[i].lFlag = false ;
        S.data[i].rFlag = false ; 
    }
}
bool isEmpty(STACK_PO S)
{
    if(S.top == -1)
    return true ;
    else
    return false ;
}
void changeLFlag(STACK_PO &S)
{
    S.data[S.top].lFlag = true ;
}
void changeRFlag(STACK_PO &S)
{
     S.data[S.top].rFlag = true ; 
}
bool getLFlag(STACK_PO S)
{
    return S.data[S.top].lFlag ;
}
bool isRChildVisited(STACK_PO S)
{
     return S.data[S.top].rFlag ; 
}
bool Push(pointer val,STACK_PO & S)
{
    if(S.top >= MAX_SIZE -1)
    return false ;
    S.top ++ ;
    S.data[S.top].val = val ;
    S.data[S.top].lFlag = false ;
    S.data[S.top].rFlag = false ;
    return true ;
}
pointer Pop(STACK_PO & S)
{
     if(isEmpty(S))
     return NULL ; 
    pointer tmp = S.data[S.top].val ;
    S.top -- ;
    return tmp ;
}
pointer Top(STACK_PO S)
{
     if(!isEmpty(S))
     return S.data[S.top].val ; 
     else
     return NULL ; 
}


#endif // STACK_POST_ORDER_H_INCLUDED
