#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "CreateBTREE.h"
#define MAX_SIZE 100
typedef node* pointer ;
struct STACK
{
    pointer data[MAX_SIZE] ;
    int top ;
} ;
void MakeNull(STACK & S)
{
    S.top = -1 ;
}
bool isEmpty(STACK S)
{
    if(S.top == -1)
    return true ;
    else
    return false ;
}
pointer Pop(STACK & S)
{
    pointer tmp = S.data[S.top] ;
    S.top -- ;
    return tmp ;
}
bool Push(pointer data,STACK & S)
{
    if(S.top >= MAX_SIZE -1)
    return false ;
    S.top++ ;
    S.data[S.top] = data ;
    return true ;
}


#endif // STACK_H_INCLUDED
