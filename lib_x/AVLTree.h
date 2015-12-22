#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include "Queue.h"
/**
    **数据结构:AVL树
    **实现功能：添加，查找，遍历（尚未有删除操作）
*/
template <class type>
class AVLNode
{
    public :
    AVLNode()
    {
        lChild = NULL ;
        rChild = NULL ;
        bf = 0 ;
    }
    AVLNode(type data)
    {
        this->data = data ;
        lChild = NULL ;
        rChild = NULL ;
        bf = 0 ;
    }
    type data ;
    AVLNode * lChild ;
    AVLNode * rChild ;
    int bf ;
} ;
template <class type>
class AVLTree
{
    public :
    AVLTree() ;
    void InOrder() ;
    void InOrderX(AVLNode<type>* pos) ;
    void PreOrder() ;
    void PreOrderX(AVLNode<type>* pos) ;
    void LevelOrder() ;
    AVLNode<type> * Search(type x) ;
    bool Insert(AVLNode<type> x) ;
    void InsertX(AVLNode<type> * & pos,AVLNode<type> x , bool & isInserted ) ;
    void LeftRotation(AVLNode<type>* & pos) ;
    void RightRotation(AVLNode<type>* & pos) ;
    private :
    AVLNode<type>* root ;
    bool unbalanced ;
} ;
template <class type>
AVLTree<type>::AVLTree()
{
    root = NULL ;
    unbalanced = false ;
}
template <class type>
void AVLTree<type>::InOrder()
{
    if(root == NULL)
    {
        std::cout <<"平衡树为空\n" ;
        return ;
    }
    else
    {
        InOrderX(root) ;
    }
}
template <class type>
void AVLTree<type>::InOrderX(AVLNode<type>* pos)
{
    if(pos != NULL)
    {
        InOrderX(pos->lChild) ;
        std:: cout <<pos->data <<"\t" ;
        InOrderX(pos->rChild) ;
    }
}
template <class type>
void AVLTree<type>::PreOrder()
{
    if(root == NULL)
    {
        std::cout <<"平衡树为空\n" ;
        return ;
    }
    else
    {
        PreOrderX(root) ;
    }
}
template <class type>
void AVLTree<type>::PreOrderX(AVLNode<type>* pos)
{
    if(pos != NULL)
    {
        std:: cout <<pos->data <<"\t" ;
        PreOrderX(pos->lChild) ;
        PreOrderX(pos->rChild) ;
    }
}
template <class type>
void AVLTree<type>::LevelOrder()
{
    Queue<AVLNode<type>*> Q ;
    Q.makeNull() ;
    if(root == NULL)
    {
        std::cout <<"AVL树为空\n" ;
        return ;
    }
    AVLNode<type>* pos = root ;
    Q.EnQueue(pos) ;
    while(! Q.isEmpty())
    {
        pos = Q.Front() ;
        Q.DeQueue() ;
        std::cout <<pos->data <<"\t" ;
        if(pos->lChild != NULL)
        {
            Q.EnQueue(pos->lChild) ;
        }
        if(pos->rChild != NULL)
        {
            Q.EnQueue(pos->rChild) ;
        }
    }
}
template <class type>
AVLNode<type>* AVLTree<type>::Search(type x)
{
    AVLNode<type>* pos = root ;
    while(pos != NULL)
    {
        if(pos ->data == x)
        {
            return pos ;
        }
        else if(x > pos->data)
        {
            pos = pos->rChild ;
        }
        else
        {
            pos = pos->lChild ;
        }
    }
    return NULL ;
}
template <class type>
bool AVLTree<type>::Insert(AVLNode<type> x)
{
    unbalanced = false ;
    bool isInserted = false ;
    InsertX(root,x,isInserted) ;
    return isInserted ;
}
template <class type>
void AVLTree<type>::InsertX(AVLNode<type>* & pos , AVLNode<type> x , bool &isInserted)
{
        if(pos == NULL)
        {
            unbalanced = true ;
            pos = new AVLNode<type>(x.data) ;
            isInserted = true ;
        }
        else if( x.data < pos->data)
        {
            InsertX(pos->lChild , x , isInserted) ;
            if(unbalanced == true)
            {
                switch(pos->bf)
                {
                    case -1 :
                    {
                        pos->bf = 0 ;
                        unbalanced = false ;
                        break ;
                    }
                    case 0 :
                    {
                        pos->bf = 1 ;
                        break ;
                    }
                    case 1 :
                    {
                        LeftRotation(pos) ;
                    }
                }
            }
        }
        else if(x.data > pos-> data)
        {
            InsertX(pos->rChild , x, isInserted) ;
            if(unbalanced == true)
            {
                switch(pos->bf)
                {
                    case -1 :
                    {
                        RightRotation(pos) ;
                        break ;
                    }
                    case 0 :
                    {
                        pos-> bf =  -1 ;
                        break ;
                    }
                    case 1 :
                    {
                        pos->bf = 0 ;
                        unbalanced = false ;
                    }
                }
            }
        }
        else
        {
            unbalanced = false ;
        }
}
template <class type>
void AVLTree<type>::LeftRotation(AVLNode<type>* & pos)
{
    AVLNode<type>* posLChild = pos->lChild ;
    if(posLChild->bf == 1)//LL
    {
        pos->lChild = posLChild ->rChild ;
        posLChild -> rChild = pos ;
        pos->bf = 0 ;
        posLChild->bf = 0 ;
        pos = posLChild ;
        unbalanced = false ;
    }
    else //posLChild->bf = -1    LR
    {
        AVLNode<type>* posLChildRChild = posLChild->rChild ;
        pos->lChild = posLChildRChild->rChild ;
        posLChildRChild ->rChild = pos ;
        posLChild->rChild = posLChildRChild->lChild ;
        posLChildRChild -> lChild = posLChild ;
        switch(posLChildRChild ->bf)
        {
            case 0 :
            {
                pos->bf = 0 ;
                posLChild->bf = 0 ;
                break ;
            }
            case 1 :
            {
                pos->bf = -1 ;
                posLChild -> bf = 0 ;
                break ;
            }
            case -1 :
            {
                pos->bf = 0 ;
                posLChild ->bf = 1 ;
                break ;
            }
        }
        pos = posLChildRChild ;
        pos->bf = 0 ;
        unbalanced = false ;
    }
}
template <class type>
void AVLTree<type>::RightRotation(AVLNode<type>* & pos)
{
    AVLNode<type>* posRChild = pos->rChild ;
    if(posRChild->bf == -1)//RR
    {
        pos->rChild = posRChild->lChild ;
        posRChild ->lChild = pos ;
        pos ->bf = 0 ;
        posRChild ->bf = 0 ;
        pos = posRChild ;
        unbalanced = false ;
    }
    else //posRChild -> bf = 1
    {
        AVLNode<type> * posRChildLChild = posRChild ->lChild ;
        pos->rChild = posRChildLChild ->lChild ;
        posRChildLChild->lChild = pos ;
        posRChild->lChild = posRChildLChild->rChild ;
        posRChildLChild -> rChild = posRChild ;
        switch(posRChildLChild ->bf)
        {
            case 1 :
            pos -> bf = 0 ;
            posRChild -> bf = -1 ;
            break ;
            case 0 :
            pos->bf = 0 ;
            posRChild -> bf = 0 ;
            break ;
            case -1 :
            pos->bf = 1 ;
            posRChild = 0 ;
            break ;
        }
        pos = posRChildLChild ;
        pos->bf = 0 ;
        unbalanced = false ;
    }
}
#endif // AVLTREE_H_INCLUDED
