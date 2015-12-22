#ifndef THREADEDTREE_H_INCLUDED
#define THREADEDTREE_H_INCLUDED

#include "QUEUE.h"
template <class type>
class Node
{
public :
    Node()
    {
        lChild = NULL ;
        rChild = NULL ;
        lIsChild = false ;
        rIsChild = false ;
    }
    Node(type info)
    {
        this->info = info ;
        lChild = NULL ;
        rChild = NULL ;
        lIsChild = false ;
        rIsChild = false ;
    }
    Node* getLChild()
    {
        return lChild ;
    }
    Node** getLChildAdress()
    {
        return &lChild ;
    }
    Node** getRChildAdress()
    {
        return &rChild ;
    }
    Node* getRChild()
    {
        return rChild ;
    }
    bool getLIsChild()
    {
        return lIsChild ;
    }
    bool getRIsChild()
    {
        return rIsChild ;
    }
    type getInfo()
    {
        return info ;
    }
    void setLChild(Node *lChild)
    {
        this->lChild = lChild ;
    }
    void setRChild(Node * rChild)
    {
        this->rChild = rChild ;
    }
    void setLIsChild(bool lIsChild)
    {
        this->lIsChild = lIsChild ;
    }
    void setRIsChild(bool rIsChild)
    {
        this->rIsChild = rIsChild ;
    }
    void setInfo(type info)
    {
        this->info = info ;
    }

private :
    Node<type> * lChild ;
    Node<type> * rChild ;
    bool lIsChild ;
    bool rIsChild ;
    type info ;
} ;
template <class type>
class ThreadedTree
{
public :
    ThreadedTree() ;
    ~ThreadedTree() ;
    Node<type> * getHead() ;
    Node<type> * getRoot() ;
    bool isThreadedTreeEmpty() ;
    Node<type> * InNext(Node<type> * p) ;
    Node<type> * InPre(Node<type> * p) ;
    void ThInOrder() ;
    void RInsert(Node<type> * x, Node<type> * r) ;
    void LInsert(Node<type> * x, Node<type> * r) ;
    Node<type> * Retrieve(type info) ;
    void CreateBTree(Node<type>* &p) ;
    void BTInit() ;
    void InOrder(Node<type> * pos) ;
    void PreOrder(Node<type> * pos) ;
    void PostOrder(Node<type> * pos) ;
    void InOrderTh() ;
    void InOrderThX(Node<type>* pos,Node<type>* &pre) ;//递归需要每次都改变pre的值，所以传引用
    Node<type>* PreNext(Node<type>* pos) ;
    void ThPreOrder() ;
    void PreOrderTh() ;
    void PreOrderThX(Node<type>* pos,Node<type>* & pre) ;
    void PostOrderTh() ;
    Node<type>* PostNext(Node<type>* pos) ;
    void ThPostOrder() ;
    void PostOrderThX(Node<type>* pos,Node<type>* & pre) ;
    void ClearThread() ;
private :
    Node<type> * head ;
    Node<type> * root ;
} ;
template <class type>
ThreadedTree<type>::ThreadedTree()
{
    head  =  new Node<type>() ;
    head->setLChild(head) ;
    head->setRChild(head) ;
    head->setRIsChild(true) ;
    root = NULL ;
}
template <class type>
ThreadedTree<type>::~ThreadedTree()
{
        Queue<Node<type>*> x ;
        x.makeNull() ;//        层序遍历释放内存
        if(root != NULL)
        {
            x.EnQueue(root) ;
            Node<type>* pos = NULL ;
            while(!x.isEmpty())
            {
                pos = x.Front() ;
                if(pos->getLIsChild() == true)
                {
                    x.EnQueue(pos->getLChild()) ;
                }
                if(pos->getRIsChild() == true)
                {
                    x.EnQueue(pos->getRChild()) ;
                }
                x.DeQueue() ;
                if(pos != NULL)
                delete pos ;
            }
        }
        delete head ;
}
template <class type>
Node<type>* ThreadedTree<type>::getHead()
{
    return head ;
}
template <class type>
Node<type>* ThreadedTree<type>::getRoot()
{
    return root ;
}
template <class type>
bool ThreadedTree<type>::isThreadedTreeEmpty()
{
    if(head->getLChild() == head)
        return true ;
    else
        return false ;
}
template <class type>
Node<type> * ThreadedTree<type>::InNext(Node<type> * p)
{
    if(p->getRIsChild() == true)
    {
        Node<type> * pos = p->getRChild() ;
        while(pos->getLIsChild() == true)
        {
            pos = pos->getLChild() ;
        }
        return pos ;

    }
    else
    {
        return p->getRChild() ;
    }

}
template <class type>
Node<type> * ThreadedTree<type>::InPre(Node<type> * p)
{
    if(p->getLIsChild() == true)
    {
        Node<type> * pos = p->getLChild() ;
        while(pos->getRIsChild() == true)
        {
            pos = pos->getRChild() ;
        }
        return pos ;
    }
    else
    {
        return p->getLChild() ;
    }

}
template <class type>
void ThreadedTree<type>::ThInOrder()
{
    Node<type>* pos = InNext(head) ;
    if(pos == head)
    {
        std::cout <<"树为空\n" ;
        return ;
    }
    else
    {
        while(pos != head)
        {
            std::cout <<pos->getInfo() <<" \t" ;
            pos = InNext(pos) ;
        }
        std::cout <<"\n\n" ;
        return ;
    }

}
template <class type>
void ThreadedTree<type>::RInsert(Node<type>* x,Node<type>* r)
{
    x->setLChild(r) ;
    x->setLIsChild(false) ;
    x->setRChild(r->getRChild()) ;
    x->setRIsChild(r->getRIsChild()) ;
    r->setRChild(x) ;
    r->setRIsChild(true) ;
    if(x->getRIsChild() == true)
    {
        Node<type>* tmp = InNext(x) ;
        tmp->setLChild(x) ;
    }
}
template <class type>
void ThreadedTree<type>::LInsert(Node<type>* x,Node<type> * r)
{
    x->setRChild(r) ;
    x->setRIsChild(false) ;
    x->setLChild(r->getLChild()) ;
    x->setLIsChild(r->getLIsChild()) ;
    r->setLChild(x) ;
    r->setLIsChild(true) ;
    if(x->getLIsChild() == true)
    {
        Node<type>* tmp = InPre(x) ;
        tmp->setRChild(tmp) ;
    }
}
template <class type>
Node<type>* ThreadedTree<type>::Retrieve(type info)
{
    Node<type>* pos = InNext(head) ;
    if(pos == head)
        return NULL ;
    else
    {
        while(pos!= head)
        {
            if(pos->getInfo() == info)
                return pos ;
            else
                pos = InNext(pos) ;
        }
        return NULL ;
    }
}
template <class type>
void ThreadedTree<type>::CreateBTree(Node<type>* &p)
{
    type val ;
    std::cout <<"请输入节点数据('#'表示为空)\n" ;
    std::cin >> val ;
    if(val == '#')
    {
        p = NULL ;
    }
    else
    {
        p = new Node<type>(val) ;
        std::cout <<"请输入节点"<< val <<"的左孩子\n" ;
        CreateBTree(*p->getLChildAdress()) ;
        std::cout <<"请输入节点"<< val <<"的右孩子\n" ;
        CreateBTree(*p->getRChildAdress()) ;
    }
}
template <class type>
void ThreadedTree<type>::BTInit()
{
    CreateBTree(root) ;
}
template <class type>
void ThreadedTree<type>::InOrder(Node<type>* BT)
{
    if(BT!= NULL)
    {
        InOrder(BT->getLChild()) ;
        std::cout <<BT->getInfo() <<"\t" ;
        InOrder(BT->getRChild()) ;
    }
}
template <class type>
void ThreadedTree<type>::InOrderTh()
{
    Node<type>* pre = head ;
    Node<type>* pos = root ;
    head->setLChild(root) ;
    head->setLIsChild(true) ;
    InOrderThX(pos,pre) ;
}
template <class type>
void ThreadedTree<type>::InOrderThX(Node<type>* pos,Node<type>* &pre)
{
    if(pos != NULL)
    {


        if(pos->getLChild() != NULL)
        {
            pos->setLIsChild(true) ;
        }
        if(pos->getRChild() != NULL)
        {
            pos->setRIsChild(true) ;
        }
        if(pos->getLIsChild() == true) ;
        InOrderThX(pos->getLChild(),pre) ;
        if(pre != NULL)
        {
            if(pre->getRIsChild() == false)
            {
                pre->setRChild(pos) ;
            }
            if(pos->getLIsChild() == false)
            {
                pos->setLChild(pre) ;
            }
        }
        pre = pos ;
        InOrderThX(pos->getRChild(),pre) ;

        if(pre->getRChild() == NULL)
        {
            pre->setRChild(head) ;//最后一个节点的右孩子要指向head节点
        }
    }
}
template <class type>
Node<type>* ThreadedTree<type>::PreNext(Node<type> * pos)
{
    if(pos == NULL)
        return NULL ;
    else
    {
        if(pos->getLIsChild() == true)
            return pos->getLChild() ;
        else
            return pos->getRChild() ;
    }
}
template <class type>
void ThreadedTree<type>::ThPreOrder()
{
    Node<type>* pos  = root ;
    while(pos != NULL)
    {
        std::cout <<pos->getInfo() <<"\t" ;
        pos = PreNext(pos) ;
    }
}
template <class type>
void ThreadedTree<type>::PreOrderTh()
{
    Node<type>* pos = root ;
    Node<type>* pre = NULL ;
    PreOrderThX(pos,pre) ;

}
template <class type>
void ThreadedTree<type>::PreOrderThX(Node<type>* pos,Node<type>* & pre)
{
    if(pos!= NULL)
    {
        if(pos->getLChild() != NULL)
        {
            pos->setLIsChild(true) ;
        }
        if(pos->getRChild()!= NULL)
        {
            pos->setRIsChild(true) ;
        }
        if(pre != NULL)
        {
            if(pre->getRIsChild() ==false)
            {
                pre->setRChild(pos) ;
            }
            if(pos->getLIsChild() == false)
            {
                pos->setLChild(pre) ;
            }
        }
        pre = pos ;
        if(pos->getLIsChild() == true)
        {
            PreOrderThX(pos->getLChild(),pre) ;
        }
        if(pos->getRIsChild() == true)
        {
            PreOrderThX(pos->getRChild(),pre) ;
        }

    }
}
template <class type>
void ThreadedTree<type>::PreOrder(Node<type>* pos)
{
    if(pos != NULL)
    {
        std::cout <<pos->getInfo() ;
        PreOrder(pos->getLChild()) ;
        PreOrder(pos->getRChild()) ;
    }

}
template <class type>
void ThreadedTree<type>::PostOrder(Node<type> * pos)
{
    if(pos!= NULL)
    {
        PostOrder(pos->getLChild()) ;
        PostOrder(pos->getRChild()) ;
        std::cout <<pos->getInfo() <<"\t" ;
    }
}
template <class type>
Node<type>* ThreadedTree<type>::PostNext(Node<type>* pos)
{
   if(pos == NULL)
   return NULL ;
   else
   {
       if(pos->getRIsChild() == true)
       {
            Queue<Node<type>*> x ;
            x.EnQueue(root) ;
            Node<type>* parent = NULL;
            while(parent!= NULL ||!x.isEmpty())
            {
                parent = x.Front() ;
                x.DeQueue() ;
                if(parent->getLIsChild() == true)
                {
                    if(parent->getLChild() == pos)
                    break ;
                    else
                    x.EnQueue(parent->getLChild()) ;
                }
                if(parent->getRIsChild() == true)
                {
                    if(parent->getRChild() == pos)
                    break ;
                    else
                    x.EnQueue(parent->getRChild()) ;
                }
            }
            if(parent->getRIsChild() == false)
            return parent ;
            else
            pos = parent->getRChild() ;
            while(pos->getLIsChild()== true || pos->getRIsChild() == true)
            {
                if(pos->getLIsChild() == true)
                {
                    pos = pos->getLChild() ;
                }
                else
                {
                    pos = pos->getRChild() ;
                }
            }
            return pos ;
       }
       else
       {
           return pos->getRChild() ;
       }
   }
}
template <class type>
void ThreadedTree<type>::ThPostOrder()
{
    Node<type>* pos = PostNext(head) ;
    while(pos != root)
    {
        std::cout <<pos->getInfo() <<"\t" ;
        pos = PostNext(pos) ;
    }
    std::cout <<root->getInfo() ;

}
template <class type>
void ThreadedTree<type>::PostOrderTh()
{
    head->setRIsChild(false) ;
    Node<type>* pos = root ;
    Node<type>* pre = head ;
    PostOrderThX(pos,pre) ;
}
template <class type>
void ThreadedTree<type>::PostOrderThX(Node<type>* pos,Node<type>* & pre)
{
    if(pos != NULL)
    {
        if(pos->getLChild() != NULL)
    pos->setLIsChild(true) ;
    if(pos->getRChild() != NULL)
    pos->setRIsChild(true) ;
    if(pos->getLIsChild() == true)
    PostOrderThX(pos->getLChild(),pre) ;
    if(pos->getRIsChild() == true)
    PostOrderThX(pos->getRChild(),pre) ;
    if(pre != NULL)
    {
        if(pre->getRIsChild() == false)
        {
            pre->setRChild(pos) ;
        }
        if(pos->getLIsChild() == false)
        {
            pos->setLChild(pre) ;
        }
    }
    pre = pos ;
    }
}
template <class type>
void ThreadedTree<type>::ClearThread()
{
    Queue<Node<type>*> x ;
    x.makeNull() ;
    if(root != NULL)
    {
        Node<type>* pos = root ;
        x.EnQueue(pos) ;
        while(!x.isEmpty())
        {
            pos = x.Front() ;
            if(pos->getLIsChild() == true)
            {
                x.EnQueue(pos->getLChild()) ;
            }
            else
            {
                pos->setLChild(NULL) ;
            }
            if(pos->getRIsChild() == true)
            {
                x.EnQueue(pos->getRChild()) ;
            }
            else
            {
                pos->setRIsChild(NULL) ;
            }
            x.DeQueue() ;
        }
    }
        head->setLChild(head) ;
    head->setRChild(head) ;
    head->setRIsChild(true) ;
    head->setLIsChild(false) ;
}
#endif // THREADEDTREE_H_INCLUDED
