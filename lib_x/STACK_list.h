#ifndef STACK_LIST_H_INCLUDED
#define STACK_LIST_H_INCLUDED
/**
    **数据结构：栈
    **实现方式：链表
    **使用模板类
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
        next = NULL ;
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
        this->next = next ;
    }
    private :
    type data ;
    Node * next ;
} ;
template <class type>
class Stack
{
    public :
    Stack() ;
    ~Stack() ;
    bool isEmpty() ;
    void makeNull() ;
    type pop() ;
    bool push(type val) ;
    type Top() ;
    private :
    Node<type> * head ;
} ;
template <class type>
Stack<type>::Stack()
{
    head = new Node<type>() ;
}
template <class type>
Stack<type>::~Stack()
{
    Node<type> * pre = head->getNext() ;
    Node<type> * later = head ;
    while(pre != NULL)
    {
        delete later ;
        later = pre ;
        pre = pre->getNext() ;
    }
    delete later ;
}
template <class type>
bool Stack<type>::isEmpty()
{
    if(head->getNext() == NULL)
    return true ;
    else
    return false ;
}
template <class type>
void Stack<type>::makeNull()
{
    if(isEmpty())
    return ;
    Node<type> * later = head->getNext() ;
    Node<type> * pre = later->getNext() ;
    while(pre != NULL)
    {
        delete later ;
        later = pre ;
        pre = pre->getNext() ;
    }
    delete later ;
    head->setNext(NULL) ;
}
template <class type>
type Stack<type>::pop()
{
    if(isEmpty())
    return NULL ;
    Node<type>* pos = head->getNext() ;
    head->setNext(pos->getNext()) ;
    type data = pos->getData() ;
    delete pos ;
    pos = NULL ;
    return data ;
}
template <class type>
bool Stack<type>::push(type data)
{
    Node<type>* tmp =new Node<type>(data) ;
    tmp->setNext(head->getNext()) ;
    head->setNext(tmp) ;
    tmp = NULL ;
    return true ;
}
template <class type>
type Stack<type>::Top()
{
    if(isEmpty())
    return NULL ;
    return head->getNext()->getData() ;
}
#endif // STACK_LIST_H_INCLUDED
