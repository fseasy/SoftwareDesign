#ifndef QUEUE_LIST_H_INCLUDED
#define QUEUE_LIST_H_INCLUDED
/**
    **数据结构：队列
    **实现方式：链表
    **实现功能：入队，出队，查看队列内元素个数，判空、满
*/
template <class type>
class Node
{
    public :
    Node()
    {
        next = NULL ;
    }
    Node(type data)
    {
        this->data = data ;
    }
    type getData()
    {
        return data ;
    }
    Node * getNext()
    {
        return next ;
    }
    void setData(type data)
    {
        this->data = data ;
    }
    void setNext(Node * next)
    {
        this->next =next ;
    }
    private :
    type data ;
    Node * next ;
} ;
template <class type>
class Queue
{
    public :
    Queue() ;
    bool isEmpty() ;
    bool isFull() ;
    void makeNull() ;
    type Front() ;
    bool EnQueue(type data) ;
    bool DeQueue() ;
    int getCounter() ;
    private :
    Node<type> * head ;
    Node<type> * rear ;
    int counter ;
} ;
template <class type>
Queue<type>::Queue()
{
    head = new Node<type>() ;
    head->setNext(head) ;
    rear = head ;
    counter = 0 ;
}
template <class type>
bool Queue<type>::isEmpty()
{
    if(head == rear)
    return true ;
    else
    return false ;
}
template <class type>
bool Queue<type>::isFull()
{
    return true ;
}
template <class type>
void Queue<type>::makeNull()
{
    while(DeQueue()) ;
}
template <class type>
bool Queue<type>::EnQueue(type data)
{
    Node<type> * tmp = new Node<type>(data) ;
    tmp->setNext(rear->getNext()) ;
    rear->setNext(tmp) ;
    rear = tmp ;
    counter++ ;
    return true ;
}
template <class type>
bool Queue<type>::DeQueue()
{
    if(isEmpty())
    return false ;
    Node<type>* pos = head->getNext() ;
    head->setNext(pos->getNext()) ;
    delete pos ;
    if(pos == rear)
    {
        rear = head ;//把rear指向的空间删除了，所以要重置rear值
    }
    counter-- ;
    return true ;
}
template <class type>
type Queue<type>::Front()
{
    if(isEmpty())
    return NULL ;
    return head->getNext()->getData() ;
}
template <class type>
int Queue<type>::getCounter()
{
    return counter ;
}
#endif // QUEUE_LIST_H_INCLUDED
