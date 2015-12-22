#ifndef QUEUE_LOOP_ARRAY_H_INCLUDED
#define QUEUE_LOOP_ARRAY_H_INCLUDED
#include "CreateBTREE.h"
#define MAX_SIZE 100
struct QUEUE 
{
     pointer data[MAX_SIZE] ; 
     int rear ; 
     int front ; 
} ; 
void MakeNull(QUEUE & Q)
{
     Q.rear = 1 ; 
     Q.front = 0 ; 
}
bool isEmpty(QUEUE Q)
{
     if((Q.front+1)%MAX_SIZE == Q.rear)
     return true ; 
     else
     return false ; 
}
bool isFull(QUEUE Q)
{
     if((Q.rear+1)%MAX_SIZE == Q.front)
     return true ; 
     else
     return false ; 
}
bool EnQueue(pointer data , QUEUE & Q)
{
     if(isFull(Q))
     return false ; 
     else
     {
          Q.data[Q.rear] = data ; 
          Q.rear = (Q.rear+1)%MAX_SIZE ; 
          return true ; 
     }
}
bool DeQueue(QUEUE & Q)
{
     if(isEmpty(Q))
     return false ; 
     else
     {
          Q.front = (Q.front+1)%MAX_SIZE ; 
     }
}
pointer Front(QUEUE Q)
{
     if(!isEmpty(Q))
     return Q.data[(Q.front+1)%MAX_SIZE] ; 
     else
     return NULL ; 
}

#endif // QUEUE_LOOP_ARRAY_H_INCLUDED
