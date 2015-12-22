#ifndef STACK_ARRAY_H_INCLUDE
#define STACK_ARRAY_H_INCLUDE
/**
  **  用数组实现的栈结构
  **  使用模板类
*/
template <class type>
class Stack
{
    public :
    Stack() ;
    Stack(int n) ;
    ~Stack() ;
    bool isEmpty() ;
    void makeNull() ;
    bool push(type val) ;
    type pop() ;
    type Top() ;
    private:
    int top ;
    int max_size ;
    type* data ;
} ;
template <class type>
    Stack<type>::Stack()
    {
        top = -1 ;
        max_size = 100 ;
        data = new type[max_size] ;
    }
template <class type>
    Stack<type>::Stack(int n)
    {
        top = -1 ;
        max_size = n ;
        data = new type[max_size] ;
    }
template <class type>
    Stack<type>::~Stack()
    {
        delete [] data ;
    }
template <class type>
    void Stack<type>::makeNull()
    {
        top = -1 ;
    }
template <class type>
    bool Stack<type>::isEmpty()
    {
        if(top == -1)
        return true ;
        else
        return false ;
    }
template <class type>
    bool Stack<type>::push(type val)
    {
        if(top == max_size)
        return false ; // when the stack is full ,return false ;
        top++ ;
        data[top] = val ;
        return true ;
    }
template <class type>
    type Stack<type>::pop()
    {
        if(isEmpty())
        return NULL;
        top-- ;
        return data[top+1] ;
    }
template <class type>
    type Stack<type>:: Top()
    {
        if(isEmpty())
        return NULL;
        else
        return data[top] ;
    }

#endif
