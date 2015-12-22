#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "LIST_array.h"
#include "Queue.h"
/**
    **数据结构：树
    **实现方式：邻接表型和二叉链表型（以线性表为基础）
    **实现功能：两种类型树的建立、转换，以及三种遍历方法；树的合并（森林）
*/
class CTNode
{
public :
    int child ;
    CTNode * next ;
    CTNode()
    {
        next = NULL ;
    }
} ;
template <class type>
class CTBox
{
public:

    CTBox(type data)
    {
        this->data = data ;
        firstChild = NULL ;
    }
    CTBox()
    {
        firstChild = NULL ;
    }
    type data ;
    CTNode * firstChild ;
} ;
template <class type>
class CSNode
{
public :
    type data ;
    CSNode<type> * firstChild ;
    CSNode<type> * rightSib ;
    CSNode(type data)
    {
        this->data = data ;
        firstChild = NULL ;
        rightSib = NULL ;
    }
    CSNode()
    {
        firstChild = NULL ;
        rightSib = NULL ;
    }
} ;
template <class type>
class Tree
{
public :
    void CreateListTree() ;
    void CreateTree() ;
    void CreateTreeX(CSNode<type>* & pos) ;
    void listToTree() ;
    void treeToList() ;
    void TreePreOrder() ;
    void TreePostOrder() ;
    void TreeLevelOrder() ;
    void TreePreOrderX(CSNode<type>* pos) ;
    void TreePostOrderX(CSNode<type>* pos) ;
    void listOrder() ;
    CSNode<type>* getRoot() ;
    CSNode<type>* Unoin(Tree<type>* t) ;
private :
    List<CTBox<type>*> nodeList ;
    List<CSNode<type>*> nodeTree ;
} ;
template <class type>
void Tree<type>::CreateListTree()
{
    std::cout <<"邻接表建树\n" ;
    type x ;
    std::cout <<"请输入树根节点信息('#'表示为空)\n" ;
    std::cin >>x ;
    if(x == '#')
        return ;
    else
    {
        CTBox<type> * tmp = new CTBox<type>(x) ;
        nodeList.Insert(tmp,nodeList.getAvail()) ;
        Queue<CTBox<type>*> Q ;
        Q.makeNull() ;
        Q.EnQueue(tmp) ;
        while(!Q.isEmpty())
        {
            tmp = Q.Front() ;
            Q.DeQueue() ;
            while(std::cout <<"请输入"<<tmp->data<<"节点的孩子节点信息（‘#’结束）")
            {
                std :: cin >> x ;
                if(x == '#')
                    break ;
                else
                {
                    CTBox<type>* p = new CTBox<type>(x) ;
                    nodeList.Insert(p,nodeList.getAvail()) ;
                    Q.EnQueue(p) ;
                    CTNode * tmpNode = new CTNode ;
                    tmpNode->child = nodeList.end() ;
                    CTNode * pos = tmp->firstChild ;
                    if(pos == NULL)
                    {
                        tmpNode->next = tmp->firstChild ;
                        tmp->firstChild = tmpNode ;
                    }
                    else
                    {
                        while(pos->next != NULL)
                        {
                            pos = pos->next ;
                        }
                        pos->next = tmpNode ;
                        tmpNode->next = NULL ;
                    }
                }
            }
        }

    }
}
template <class type>
void Tree<type>::CreateTree()
{
    CSNode<type>* head ;
    CreateTreeX(head) ;
}
template <class type>
void Tree<type>::CreateTreeX(CSNode<type>* &pos)
{
    std::cout <<"请输入节点信息('#'表示为空)\n" ;
    type x ;
    std::cin >>x ;
    if(x != '#')
    {
        pos = new CSNode<type>(x) ;
        nodeTree.Insert(pos,nodeTree.getAvail()) ;
        std::cout <<"请输入节点"<<x<<"的第一个孩子\n" ;
        CreateTreeX(pos->firstChild) ;
        std::cout <<"请输入节点"<<x<<"的右兄弟\n" ;
        CreateTreeX(pos->rightSib) ;
    }
}
template <class type>
void Tree<type>::listToTree()
{
    if(nodeList.first() == INVALID)
    {
        std::cout <<"树为空\n" ;
        return ;
    }
    if(nodeTree.first() != INVALID)
    {
        std::cout <<"二叉链表树已经存在\n" ;
        return ;
    }
    for(int i = nodeList.first() ; i<= nodeList.end() ; i++)
    {
        type data = nodeList.Retrieve(i)->data ;
        CSNode<type>* tmp = new CSNode<type>(data) ;
        nodeTree.Insert(tmp,nodeTree.getAvail()) ; //建立节点
    }
    for(int i = nodeList.first() ; i<= nodeList.end() ; i++)
    {
        CTNode * pos = nodeList.Retrieve(i)->firstChild ;
        if(pos != NULL)
        {
            //左儿子
            int childNum = pos->child ;
            nodeTree.Retrieve(i)->firstChild = nodeTree.Retrieve(childNum) ;
            //右兄弟
            CTNode* posNext = pos->next ;
            while(posNext != NULL)
            {
                nodeTree.Retrieve(pos->child)->rightSib = nodeTree.Retrieve(posNext->child) ;
                pos = posNext ;
                posNext = pos->next ;
            }
        }

    }
}
template <class type>
void Tree<type>::TreePreOrder()
{
    if(nodeTree.first() == INVALID)
    {
        std::cout <<"二叉链表树为空\n" ;
        return ;
    }
    TreePreOrderX(nodeTree.Retrieve(nodeTree.first())) ;
    std::cout <<"\n" ;
}
template <class type>
void Tree<type>::TreePreOrderX(CSNode<type>* pos)
{
    if(pos != NULL)
    {
        std::cout <<pos->data<<"\t" ;
        TreePreOrderX(pos->firstChild) ;
        TreePreOrderX(pos->rightSib) ;

    }
}
template <class type>
void Tree<type>::TreePostOrder()
{
    if(nodeTree.first() == INVALID)
    {
        std::cout <<"树为空\n" ;
        return  ;
    }
    TreePostOrderX(nodeTree.Retrieve(nodeTree.first())) ;
    std::cout <<"\n" ;
}
template <class type>
void Tree<type>::TreePostOrderX(CSNode<type>* pos)
{
    if(pos != NULL)
    {
        TreePostOrderX(pos->firstChild) ;
        std::cout <<pos->data <<"\t" ;
        TreePostOrderX(pos->rightSib) ;
    }
}
template <class type>
void Tree<type>::TreeLevelOrder()//定义一个isVisited辅助数组，每次先将rightSIb放入队列（保证同一层），再放入第一个孩子，再将第一个孩子的全部rightSib放入队列（保证遍历顺序）
{
    Queue<CSNode<type>*> Q ;
    Q.makeNull() ;
    if(nodeTree.first() == INVALID)
    {
        std::cout <<"树为空\n" ;
        return ;
    }
    Q.EnQueue(nodeTree.Retrieve(nodeTree.first())) ;
    CSNode<type>* pos = NULL ;
    bool isVisited[nodeTree.end()+1] ;
    for(int i = 2 ; i<= nodeTree.end() ; i++)
    {
        isVisited[i] = false ;
    }
    while(!Q.isEmpty())
    {
        pos = Q.Front() ;
        Q.DeQueue() ;
        std::cout <<pos->data <<"\t" ;
        if(pos->rightSib != NULL)
        {
            CSNode<type>* sibPos = pos->rightSib ;
            int childNum = nodeTree.Locate(sibPos) ;
            if(isVisited[childNum] != true)
            {
                while(sibPos != NULL )
                {
                    childNum = nodeTree.Locate(sibPos) ;
                    isVisited[childNum] = true ;
                    Q.EnQueue(sibPos) ;
                    sibPos = sibPos->rightSib ;
                }
            }
        }
        if(pos->firstChild != NULL)
        {
            Q.EnQueue(pos->firstChild) ;
            isVisited[nodeTree.Locate(pos->firstChild)] = true ;
            pos = pos->firstChild ;
            if(pos->rightSib != NULL)
            {
                pos = pos->rightSib ;
                int childNum = nodeTree.Locate(pos) ;
                if(isVisited[childNum] != true)
                {
                    while(pos != NULL)
                    {
                        childNum = nodeTree.Locate(pos) ;
                        isVisited[childNum] = true ;
                        Q.EnQueue(pos) ;
                        pos = pos->rightSib ;
                    }
                }
            }
        }
    }
    std::cout <<"\n" ;
}
template <class type>
void Tree<type>::listOrder()
{
    if(nodeList.first() == INVALID)
    {
        std::cout <<"邻接表树为空\n" ;
        return ;
    }
    for(int i = nodeList.first() ; i<= nodeList.end(); i++)
    {
        std::cout <<"根节点信息是"<<nodeList.Retrieve(i)->data <<"\t孩子节点是" ;
        CTNode * pos = nodeList.Retrieve(i)->firstChild ;
        while(pos != NULL)
        {
            std::cout <<nodeList.Retrieve(pos->child)->data <<" " ;
            pos = pos->next ;
        }
        std::cout <<" ^ \n" ;
    }
}
template <class type>
void Tree<type>::treeToList()
{
    if(nodeTree.first() == INVALID)
    {
        std::cout <<"树为空\n" ;
        return ;
    }
    if(nodeList.first() != INVALID)
    {
        std::cout <<"邻接表树已经存在\n" ;
        return ;
    }
    for(int i = nodeTree.first() ; i <= nodeTree.end() ; i++ )
    {
        type x = nodeTree.Retrieve(i)->data ;
        CTBox<type>* tmp = new CTBox<type>(x) ;
        nodeList.Insert(tmp,nodeList.getAvail()) ;
    }
    for(int i = nodeTree.first() ; i<= nodeTree.end() ; i++ )
    {
        CSNode<type>* pos = nodeTree.Retrieve(i)->firstChild ;
        if(pos != NULL)
        {
            int childNum = nodeTree.Locate(pos) ;
            CTNode * tmpNode = new CTNode ;
            tmpNode->child = childNum ;
            nodeList.Retrieve(i)->firstChild = tmpNode ;
            //rightSib
            while(pos->rightSib != NULL)
            {
                pos = pos->rightSib ;
                childNum = nodeTree.Locate(pos) ;
                CTNode * tmpNodeNext = new CTNode ;
                tmpNodeNext ->child = childNum ;
                tmpNode->next = tmpNodeNext ;
                tmpNode = tmpNodeNext ;
            }
        }
    }
}
template <class type>
CSNode<type>* Tree<type>::getRoot()
{
    if(nodeTree.first() == INVALID)
        return NULL ;
    else
        return nodeTree.Retrieve(nodeTree.first()) ;
}
template <class type>
CSNode<type>* Tree<type>::Unoin(Tree<type>* t)//返回最左边根节点指针
{
    CSNode<type>* tRoot = t->getRoot() ;
    if(tRoot == NULL)
        return NULL ;
    else
    {
        if(nodeTree.first() == INVALID)
            return NULL ;
        else
        {
            CSNode<type>* pos = nodeTree.Retrieve(nodeTree.first()) ;
            while(pos->rightSib != NULL)
            {
                pos = pos->rightSib ;  //把t的根节点加入到右子树（逻辑上表示并列的树）
            }
            pos ->rightSib = tRoot ;
            return nodeTree.Retrieve(nodeTree.first()) ;
        }
    }
}
#endif // TREE_H_INCLUDED
