#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "LIST_array.h"
#include "Queue.h"
/**
    **���ݽṹ����
    **ʵ�ַ�ʽ���ڽӱ��ͺͶ��������ͣ������Ա�Ϊ������
    **ʵ�ֹ��ܣ������������Ľ�����ת�����Լ����ֱ������������ĺϲ���ɭ�֣�
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
    std::cout <<"�ڽӱ���\n" ;
    type x ;
    std::cout <<"�����������ڵ���Ϣ('#'��ʾΪ��)\n" ;
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
            while(std::cout <<"������"<<tmp->data<<"�ڵ�ĺ��ӽڵ���Ϣ����#��������")
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
    std::cout <<"������ڵ���Ϣ('#'��ʾΪ��)\n" ;
    type x ;
    std::cin >>x ;
    if(x != '#')
    {
        pos = new CSNode<type>(x) ;
        nodeTree.Insert(pos,nodeTree.getAvail()) ;
        std::cout <<"������ڵ�"<<x<<"�ĵ�һ������\n" ;
        CreateTreeX(pos->firstChild) ;
        std::cout <<"������ڵ�"<<x<<"�����ֵ�\n" ;
        CreateTreeX(pos->rightSib) ;
    }
}
template <class type>
void Tree<type>::listToTree()
{
    if(nodeList.first() == INVALID)
    {
        std::cout <<"��Ϊ��\n" ;
        return ;
    }
    if(nodeTree.first() != INVALID)
    {
        std::cout <<"�����������Ѿ�����\n" ;
        return ;
    }
    for(int i = nodeList.first() ; i<= nodeList.end() ; i++)
    {
        type data = nodeList.Retrieve(i)->data ;
        CSNode<type>* tmp = new CSNode<type>(data) ;
        nodeTree.Insert(tmp,nodeTree.getAvail()) ; //�����ڵ�
    }
    for(int i = nodeList.first() ; i<= nodeList.end() ; i++)
    {
        CTNode * pos = nodeList.Retrieve(i)->firstChild ;
        if(pos != NULL)
        {
            //�����
            int childNum = pos->child ;
            nodeTree.Retrieve(i)->firstChild = nodeTree.Retrieve(childNum) ;
            //���ֵ�
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
        std::cout <<"����������Ϊ��\n" ;
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
        std::cout <<"��Ϊ��\n" ;
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
void Tree<type>::TreeLevelOrder()//����һ��isVisited�������飬ÿ���Ƚ�rightSIb������У���֤ͬһ�㣩���ٷ����һ�����ӣ��ٽ���һ�����ӵ�ȫ��rightSib������У���֤����˳��
{
    Queue<CSNode<type>*> Q ;
    Q.makeNull() ;
    if(nodeTree.first() == INVALID)
    {
        std::cout <<"��Ϊ��\n" ;
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
        std::cout <<"�ڽӱ���Ϊ��\n" ;
        return ;
    }
    for(int i = nodeList.first() ; i<= nodeList.end(); i++)
    {
        std::cout <<"���ڵ���Ϣ��"<<nodeList.Retrieve(i)->data <<"\t���ӽڵ���" ;
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
        std::cout <<"��Ϊ��\n" ;
        return ;
    }
    if(nodeList.first() != INVALID)
    {
        std::cout <<"�ڽӱ����Ѿ�����\n" ;
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
CSNode<type>* Tree<type>::Unoin(Tree<type>* t)//��������߸��ڵ�ָ��
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
                pos = pos->rightSib ;  //��t�ĸ��ڵ���뵽���������߼��ϱ�ʾ���е�����
            }
            pos ->rightSib = tRoot ;
            return nodeTree.Retrieve(nodeTree.first()) ;
        }
    }
}
#endif // TREE_H_INCLUDED
