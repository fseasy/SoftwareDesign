#ifndef QUEUE_H_INCLUDE
#define QUEUE_H_INCLUDE
/**
    **数据结构：队列
    **实现方式：循环数组
    **实现功能：入队，出队，查看队列内元素个数，判空、满
*/


template <class type>
class Queue
{
    public :
    Queue() ;
    Queue(int n) ;
    ~Queue() ;
    void makeNull() ;
    type Front() ;
    bool EnQueue(type x) ;
    bool DeQueue() ;
    bool isEmpty() ;
    bool isFull() ;
    int getCounter() ;
    private:
    type * data ;
    int front ;
    int rear ;
    int size ;
    int counter ;
} ;
template <class type>
Queue<type>::Queue()
{
    size = 100 ;
    data = new type[size] ;
    front = size -1 ;
    rear = size -1 ;
    counter = 0 ;
}
template <class type>
Queue<type>::Queue(int n)
{
    size = n ;
    data = new type[size] ;
    front = size -1 ;
    rear = size -1 ;
    counter = 0 ;
}
template <class type>
Queue<type>::~Queue()
{
    delete [] data ;
}

template <class type>
bool Queue<type>::isEmpty()
{
    if(rear == front)
    return true ;
    else
    return false ;
}
template <class type>
bool Queue<type>::isFull()
{
    if((rear+1)%size == front)
    return true ;
    else
    return false ;
}
template <class type>
void Queue<type>::makeNull()
{
    front = size -1 ;
    rear = size -1 ;
    counter = 0 ;
}
template <class type>
type Queue<type>::Front()
{
    if(isEmpty())
    return NULL ;
    return data[(front+1)%size] ;
}
template <class type>
bool Queue<type>::EnQueue(type x)
{
    if(isFull())
    return false ;
    rear = (rear+1)%size ;
    data[rear] = x ;
    counter++ ;
    return true ;
}
template <class type>
bool Queue<type>::DeQueue()
{
    if(isEmpty())
    return false ;
    front = (front+1)%size ;
    counter -- ;
    return true ;
}
template <class type>
int Queue<type>::getCounter()
{
    return counter ;
}
#endif
