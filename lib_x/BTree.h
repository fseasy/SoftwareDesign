#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "QUEUE.h"
const int bigger = 1 ;
const int smaller = -1 ;
const int equal = 0 ;
template <class type>
class BTNode
{
public :
    BTNode(int minOrder) ;
    ~BTNode() ;
    int keyNum ;
    type * keys ;
    BTNode ** childs ;
    bool isLeaf ;
} ;
template <class type>
BTNode<type>::BTNode(int minOrder)
{
    keyNum = 0 ;
    keys = new type[minOrder*2 -1] ;//�ؼ��ֵķ�ΧΪminOrder-1~2*minOrder -1(���ڵ�������һ���ؼ���)
    childs = new BTNode *[minOrder *2] ;//���ӽڵ㣨ָ�룩�ķ�ΧΪminOrder ~ 2*minOrder(���ڵ���������������)
    for(int i = 0 ; i < minOrder *2 ; i++ )
    {
        childs[i] = NULL ;
    }
    isLeaf = true ;
}
template <class type>
BTNode<type>::~BTNode()
{
    delete [] keys ;
    for(int i = 0 ; i < keyNum ; i++)
    {
        delete childs[i] ;
    }
    delete [] childs ;

}
template <class type>
class BTree
{
public :
    BTree(int minOrder) ;
    ~BTree() ;
    void virtualDiskWrite(BTNode<type> * tmp) ;
    int keyCompare(type firstKey,type secondKey) ;
    void printBTree() ;

    bool search(type key,BTNode<type> * & node,int &index) ;
    bool searchX(BTNode<type>* pos,type key,BTNode<type>* & node,int & index) ;

    bool btreeInsert(type newKey) ;
    bool insertNotFull(BTNode<type>* current,type newKey) ;
    void splitChild(BTNode<type> * parent,int index , BTNode<type>* fullChild) ;//��Ҫ��֤parent����

    bool deleteX(BTNode<type>* &node,type key,BTNode<type>* & result,int & index) ;
    bool btreeDelete(type key) ;
    bool leftToParentToRight(BTNode<type>* left,BTNode<type>* parent,BTNode<type>* right,int location) ;
    bool rightToParentToLeft(BTNode<type>* right,BTNode<type>* parent,BTNode<type>* left,int location) ;
    bool toLeftMerge(BTNode<type> * left,BTNode<type>* & parent,BTNode<type>* right,int location) ;
    bool toRightMerge(BTNode<type> * left,BTNode<type>* & parent,BTNode<type>* right,int location) ;
    bool preProcess(BTNode<type>* & parent,int &index) ;

private :
    int minOrder ;
    BTNode<type> * root ;
} ;
template <class type>
BTree<type>::BTree(int minOrder)
{
    this->minOrder = minOrder ;
    root = new BTNode<type>(minOrder) ;
}
template <class type>
BTree<type>::~BTree()
{
    delete root ;
}
template <class type>
void BTree<type>::virtualDiskWrite(BTNode<type> * tmp)
{
    if(tmp->isLeaf == true)
    {
        std::cout <<"Ҷ�ӽڵ�" ;
    }
    else
    {
        std::cout <<"����Ҷ�ӽڵ�" ;
    }
    std::cout <<"\t�ؼ�����Ϊ"<<tmp->keyNum <<" " ;
    for(int i = 0 ; i < 2* minOrder -1 ; i++)
    {
        std::cout <<tmp->childs[i] <<" "<< tmp->keys[i] <<" ";
    }
    std::cout << tmp->childs[2*minOrder -1] <<"\n\n" ;
}
template <class type>
int BTree<type>::keyCompare(type firstKey,type secondKey)
{
    if(firstKey > secondKey)
        return bigger ;
    else if(firstKey < secondKey)
        return smaller ;
    else
        return equal ;
}
template <class type>
void BTree<type>::printBTree()
{
    std::cout <<"�����ӡ���:\n" ;
    Queue<BTNode<type>*> Q ;
    Q.makeNull() ;
    Q.EnQueue(root) ;
    while(!Q.isEmpty())
    {
        BTNode<type> * tmp = Q.Front() ;
        Q.DeQueue() ;
        for(int i = 0 ; i < tmp->keyNum ; i++)
        {
            std::cout <<tmp->keys[i] <<" " ;
        }
        std::cout <<"\n" ;
        if(tmp->isLeaf == false)
        {
            for(int i = 0 ; i < tmp->keyNum+1 ; i++)
            {
                Q.EnQueue(tmp->childs[i]) ;
            }
        }

    }
}
/**
    ���������������ؼ��֣����ڱ�������BTNodeָ�룬�ؼ�������λ�ã�
    �����Ƿ��ҵ�
*/
template <class type>
bool BTree<type>::searchX(BTNode<type>* pos,type key,BTNode<type>* & node,int &index)
{
    if(pos ->isLeaf == true)
    {
        int low = 0,high = pos->keyNum-1 ;
        int mid ;
        while(low <= high)
        {
            mid = (low+high)/2 ;
            if(keyCompare(pos->keys[mid],key) == equal)
            {
                index = mid ;
                node = pos ;
                return true ;
            }
            else if(keyCompare(pos->keys[mid],key) == smaller)
            {
                low = mid+1 ;
            }
            else
            {
                high = mid -1 ;
            }
        }
        return false ;
    }
    else
    {
        //���Զ�λ
        index = pos->keyNum -1 ;
        while(index >= 0 && keyCompare(pos->keys[index],key) == bigger)
        {
            index -- ;
        }
        if(keyCompare(pos->keys[index],key) == equal)//�ҵ�
        {
            node = pos ;
            return true ;
        }
        index++ ;//���µݹ����
        return searchX(pos->childs[index],key,node,index) ;

    }
}
template <class type>
bool BTree<type>::search(type key,BTNode<type> * & node,int & index)
{
    BTNode <type> * pos = root ;
    if(pos->isLeaf == true)
    {
        //��Ҷ�ӽڵ��н��ж��ֲ���
        int low = 0,high = pos->keyNum-1 ;
        int mid ;
        while(low <= high)
        {
            mid = (low+high)/2 ;
            if(keyCompare(pos->keys[mid],key) == equal)
            {
                index = mid ;
                node = pos ;
                return true ;
            }
            else if(keyCompare(pos->keys[mid],key) == smaller)
            {
                low = mid+1 ;
            }
            else
            {
                high = mid -1 ;
            }
        }
        return false ;
    }
    else
    {
        index = pos->keyNum -1 ;
        while(index >= 0 && keyCompare(pos->keys[index],key) == bigger)
        {
            index -- ;
        }
        if(keyCompare(pos->keys[index],key) == equal)//�ҵ�
        {
            node = pos ;
            return true ;
        }
        index++ ;//���µݹ����
        return searchX(pos->childs[index],key,node,index) ;
    }
}
template <class type>
bool BTree<type>::btreeInsert(type newKey)
{
    if(root->keyNum == 2*minOrder -1)
    {
        BTNode<type> * tmp = new BTNode<type>(minOrder) ;
        tmp->keyNum = 0 ;
        tmp->isLeaf =false ;
        tmp->childs[0] = root ;
        splitChild(tmp,-1,root) ;
        root = tmp ;
        insertNotFull(root,newKey) ;
    }
    else
    {
        insertNotFull(root,newKey) ;
    }
    return true ;
}
template <class type>
bool BTree<type>::insertNotFull(BTNode<type>* current,type newKey)
{
    //�����ж��Ƿ���Ҷ�ӽڵ㣬���ǣ���Ҫ�ڸýڵ���루���ÿ��Ƿ�������������ǣ���ѡ����ʵ�
    //childָ��ݹ���루�ݹ�֮ǰ�迼��childָ��Ľڵ��ǹ����������Ƿ��������
    if(current->isLeaf)
    {
        int index = current->keyNum -1 ;
        while(index >= 0 && keyCompare(current->keys[index],newKey) == bigger)
        {
            index-- ;
        }
        if(keyCompare(current->keys[index],newKey) == equal)
        {
            return false ;
        }
        else
        {
            index++ ;
            for(int i = current->keyNum ; i > index ; i--)
            {
                current->keys[i] = current->keys[i-1] ;
            }
            current->keys[index] = newKey ;//�����¹ؼ���
            current->keyNum++ ;
            //virtualDiskWrite(current) ;
            return true ;
        }
    }
    else
    {
        int index = current->keyNum -1 ;
        while(index>= 0 && keyCompare(current->keys[index],newKey) == bigger)
        {
            index-- ;
        }
        if(keyCompare(current->keys[index],newKey) == equal)
        {
            return false ;
        }
        else
        {
            if(current->childs[index+1]->keyNum == 2*minOrder -1)
            {
                splitChild(current,index,current->childs[index+1]) ;
                if(newKey >current->keys[index+1])//�²���Ѻ�ýڵ�(�²�ĸ��׽ڵ�)�仯����Ҫ�Ƚ�����ӵĹؼ��ֺʹ��²㵽�ò�Ĺؼ��ִ�С
                {
                    insertNotFull(current->childs[index+2],newKey) ;
                }
                else
                {
                    insertNotFull(current->childs[index+1],newKey) ;
                }
            }
            else
            {
                insertNotFull(current->childs[index+1],newKey) ;
            }
            return true ;
        }
    }

}
template <class type>
void BTree<type>::splitChild(BTNode<type> * parent,int index , BTNode<type> * fullChild)
{
    BTNode<type> * newNode = new BTNode<type>(minOrder) ;
    newNode->keyNum = minOrder -1 ;//�ؼ��ָ���Ϊ���ٵ����
    newNode->isLeaf = fullChild->isLeaf ; //��fullChildͬ��
    for(int i = 0 ; i < minOrder -1 ; i++)
    {
        newNode->keys[i] = fullChild->keys[minOrder+i] ;//���ƹؼ���
    }
    if(!fullChild->isLeaf)
    {
        for(int i = 0 ; i < minOrder ; i++)
        {
            newNode->childs[i] = fullChild->childs[minOrder+i] ; //���ƺ���ָ��
        }
    }
    fullChild->keyNum = minOrder - 1 ;//����ԭ���ڵ�Ĺؼ��ָ���
    //�������׽ڵ�,...C(index),K(index),c(index+1),K(index+1),...;��Ҫ��c��index�������k(fullChild[minOrder-1]),C��newNode��
    for(int i = parent->keyNum ; i> index+1 ; i--)
    {
        parent->keys[i] = parent->keys[i-1] ;
    }
    parent->keys[index+1] = fullChild->keys[minOrder -1] ; //����ؼ���
    for(int i = parent->keyNum +1 ; i> index+2 ; i--)
    {
        parent->childs[i] = parent->childs[i-1] ;
    }
    parent->childs[index+2] = newNode ; //����
    parent->keyNum++ ;//���Ĺؼ��ֵ�ֵ
    //virtualDiskWrite(parent) ;
    //virtualDiskWrite(fullChild) ;
    //virtualDiskWrite(newNode) ;
}
/**
    ��ʼɾ������

*/
template <class type>
bool BTree<type>::deleteX(BTNode<type>* &node,type key,BTNode<type>* &result,int &index)
{
    if(result == node)
    {
        //Ҫɾ���Ĺؼ����ڸýڵ���
        if(node->isLeaf == true)
        {
            //��Ҷ�ڵ�
            for(int i = index ; i < node->keyNum -1 ; i++ )
            {
                node->keys[i] = node->keys[i+1] ;
            }
            node->keyNum-- ;
            return true ;
        }
        else
        {
            BTNode<type>* lChild = node->childs[index] ;
            BTNode<type>* rChild = node->childs[index+1] ;
            //1.���Һ����Ƿ���������
            if(rChild->keyNum >= minOrder)
            {
                //����
                node->keys[index] = rChild->keys[0] ;//����߹ؼ��ִ���
                //
                result = rChild ;
                index = 0 ;
                key = rChild->keys[0] ;
                return deleteX(rChild,key,result,index);
            }
            else if(lChild->keyNum >= minOrder)
            {
                //����
                node->keys[index] = lChild->keys[lChild->keyNum -1] ;
                //
                result = lChild ;
                index = lChild->keyNum -1 ;
                key = lChild->keys[index] ;
                return deleteX(lChild,key,result,index) ;
            }
            else
            {
                //�ϲ����ϵ������
                lChild->keyNum = 2* minOrder -1 ;
                lChild->keys[minOrder -1] = node->keys[index] ;
                for(int i = minOrder ; i < 2* minOrder -1 ; i++)
                {
                    lChild->keys[i] = rChild->keys[i-minOrder] ;
                    lChild->childs[i] = rChild->childs[i-minOrder] ;
                }
                lChild->childs[2*minOrder -1] = rChild->childs[minOrder -1] ;
                //delete rChild ;
                for(int i = index ; i< node->keyNum -1 ; i++)
                {
                    node->keys[i] = node->keys[i+1] ;
                    node->childs[i+1] =node->childs[i+2] ;
                }
                node->keyNum -- ;
                result = lChild ;
                index = minOrder -1 ;
                return deleteX(lChild,key,result,index) ;
            }
        }
    }
    else
    {
        //���ڽڵ���
        int i = node->keyNum -1 ;
        while(i >= 0 && keyCompare(node->keys[i],key) == bigger)
        {
            i-- ;
        }
        i++ ;
        if(node->childs[i]->keyNum >= minOrder)
        {
            return deleteX(node->childs[i],key,result,index) ;
        }
        else
        {
            preProcess(node,i) ;
            return deleteX(node->childs[i],key,result,index) ;
        }

    }
}
template <class type>
bool BTree<type>::btreeDelete(type key)
{
    BTNode<type>* result ;
    int index ;
    if(search(key,result,index) == true)
    {
        //�Ȳ鿴�Ƿ��ڸýڵ��ڣ��˼����ڵ㣩
        if(result == root)
        {
            if(root ->isLeaf == true)
            {
                for(int i = index ; i < root->keyNum -1 ; i++)
                {
                    root->keys[i] = root->keys[i+1] ;
                }
                root->keyNum -- ;
                return true ;
            }
            else
            {
                //ɾ����Ϊ�����ڽڵ㣬�����ҵ����˳�򣬿��ܷ��ú��ӽڵ��йؼ��ֲ��ϸ�
                //���ڵ�ؼ��֣����Ѹø��ڵ�ؼ������ƣ�ʵ���в����滻�ķ�ʽ��
                //�Һ���Ϊchilds[index+1],����Ϊindex
                if(root->childs[index+1] ->keyNum >= minOrder)
                {
                    //�Һ����������������Ƹ��ڵ�ؼ��֣����Һ��ӵ�����߹ؼ����滻�ø��ڵ�ؼ���
                    root->keys[index] = root->childs[index+1]->keys[0] ;
                    //���ڿ���ɾ�����Һ��ӵ�����߹ؼ���
                    result = root->childs[index+1] ;
                    index = 0 ;
                    return deleteX(root->childs[index+1],root->childs[index+1]->keys[0],result,index) ;
                }
                else if(root->childs[index]->keyNum >= minOrder)
                {
                    //�Һ��Ӳ����������������������������������������ұ߹ؼ���
                    BTNode<type>* lChild = root->childs[index] ;
                    root->keys[index] = lChild->keys[lChild->keyNum -1] ;
                    //���ڿ���ɾ�����������ұ߹ؼ���
                    result = lChild ;
                    index = lChild->keyNum -1 ;
                    return deleteX(lChild,lChild->keys[lChild->keyNum-1],result,index) ;
                }
                else
                {
                    //���Һ��Ӷ������������������Һ��Ӷ�ֻ��minOrder -1 ���ؼ���
                    //��Ҫ���кϲ�����
                    //��������ָ�룬���Ѹùؼ��ֺ��Һ��ӵĹؼ��ָ��Ƶ����ӣ��ͷ��Һ���
                    //���ڵ�仯
                    BTNode<type> * lChild = root->childs[index] ;
                    BTNode<type> * rChild = root->childs[index+1] ;//��������
                    for(int i = index ; i < root->keyNum -1 ; i++ )
                    {
                        root->keys[i] = root->keys[i+1] ;
                        root->childs[i+1] = root->childs[i+2] ;
                    }
                    root->keyNum-- ;//���Ĺؼ�����Ŀ
                    //���Ӹ��ƹ���

                    lChild->keys[lChild->keyNum] = key ;//�����׽ڵ�ؼ��ָ��Ƶ�����
                    for(int i = lChild->keyNum+1 ; i< 2* minOrder -1 ; i++)
                    {
                        lChild->keys[i] = rChild->keys[i-minOrder] ;
                        lChild->childs[i] = rChild->childs[i-minOrder] ;
                    }
                    lChild->childs[2*minOrder -1] = rChild->childs[minOrder -1] ;
                    lChild->keyNum = 2*minOrder -1 ;
                    //delete rChild ;
                    //����Ƿ���ڵ��ѿ�
                    if(root->keyNum == 0)
                    {
                        root = lChild ;
                    }
                    //��ʼɾ���ýڵ�
                    result = lChild ;
                    index = minOrder -1 ;
                    return deleteX(lChild,key,result,index) ;
                }
            }
        }
        else
        {
            //���ڸ��ڵ���
            int i = root->keyNum - 1;
            while(i>= 0 && keyCompare(root->keys[i],key) == bigger)
            {
                i-- ;
            }
            i++ ;
            //Ŀ������Ϊroot�ĵ�i+1������
            //�鿴�ú��ӹؼ��ָ����Ƿ�>= minOrder
            if(root->childs[i]->keyNum >= minOrder)
            {
                return deleteX(root->childs[i],key,result,index) ;
            }
            else
            {
                //Ԥ����ʹҪ�µ��Ľڵ�ؼ�����>=minOrder
                BTNode<type>* tmp = root ;
                preProcess(root,i) ;
                if(tmp == root)
                    return deleteX(root->childs[i],key,result,index) ;
                else
                    return deleteX(root,key,result,index) ;
            }


        }
    }
    else
    {
        return false ;
    }
}
template <class type>
bool BTree<type>::preProcess(BTNode<type>* & parent,int & index)//indexָ�������ڵ�����
{
    //ȷ���ú��ӵĹؼ�����Ŀ����ΪminOrder��
    //���Һ����˳��
    //�����ֵ�����߹ؼ����Ƶ����׹ؼ��ִ������׽ڵ�ؼ����Ƶ���Ҫ���ʵĽڵ㴦�����ұߣ�
    //����߹ؼ��ֶ�Ӧ�ĺ���ָ���ƶ����ƶ���Ĵ������ӵ����һ��ָ�루�����׹ؼ��ֶ�Ӧ��ָ�룩
    //ע�����KeyNum��ֵ
    if(index == parent->keyNum)//�ú��������Ҷ�
    {
        BTNode<type> * rChild = parent->childs[index] ;//��������
        BTNode<type> * lChild = parent->childs[index-1] ;
        if(lChild->keyNum >= minOrder)//�㹻
        {
            //�����ֵ����ұߵĹؼ����Ƶ����׽ڵ�Ĺؼ��֣�ԭ���׽ڵ�Ĺؼ����Ƶ��Ƶ��Һ��ӵ������
            leftToParentToRight(lChild,parent,rChild,index-1) ;
            return true ;
        }
        else
        {
            //�����ֵܣ����׽ڵ�ؼ��ֹ鲢���ú��ӽڵ㣬ע�⣬�����ú��ӽڵ��ָ�루����ɾ��ʱ�Ѿ�ȷ���ˣ�
            toRightMerge(lChild,parent,rChild,index -1) ;
            index-- ;//���������仯,��ֻ����������¸ı䣡��
            return true ;
        }
    }
    else
    {
        BTNode<type>* lChild = parent->childs[index] ;
        BTNode<type>* rChild = parent->childs[index+1] ;
        if(rChild->keyNum >= minOrder)
        {
            rightToParentToLeft(rChild,parent,lChild,index) ;
            return true ;
        }
        else
        {
            toLeftMerge(lChild,parent,rChild,index) ;
            return true ;
        }
    }
}
template <class type>
bool BTree<type>::leftToParentToRight(BTNode<type>* left,BTNode<type>* parent,BTNode<type>* right,int location)
{
    right->keyNum++ ;
    for(int i = right->keyNum -1 ; i >0 ; i--)
    {
        right->keys[i] = right->keys[i-1] ;
        right->childs[i+1] = right->childs[i] ;
    }
    right->childs[1] = right->childs[0] ;
    right->keys[0] = parent->keys[location] ;//!!!
    //
    parent->keys[location] = left->keys[left->keyNum-1] ;
    //
    right->childs[0] = left->childs[left->keyNum] ;
    left->keyNum-- ;
    //virtualDiskWrite(parent) ;
    //virtualDiskWrite(left) ;
    //virtualDiskWrite(right) ;
    return true ;
}
template <class type>
bool BTree<type>::rightToParentToLeft(BTNode<type>* right,BTNode<type>* parent,BTNode<type>* left,int location)
{
    left->keyNum++ ;
    left->keys[left->keyNum -1] = parent->keys[location] ;
    left->childs[left->keyNum] = right->childs[0] ;
    //
    parent->keys[location] = right->keys[0] ;
    //
    right->keyNum-- ;
    for(int i = 0 ; i < right->keyNum ; i++)
    {
        right->keys[i] = right->keys[i+1] ;
        right->childs[i] = right->childs[i+1] ;
    }
    right->childs[right->keyNum] = right->childs[right->keyNum +1] ;
    //virtualDiskWrite(parent) ;
    //virtualDiskWrite(left) ;
    //virtualDiskWrite(right) ;
    return true ;
}
template <class type>
bool BTree<type>::toRightMerge(BTNode<type> * left,BTNode<type>* & parent,BTNode<type>* right,int location)
{
    right->keyNum = 2*minOrder -1 ;
    //�����Һ���Ԫ��
    for(int i = 0 ; i < minOrder -1 ; i++)
    {
        right->keys[2*minOrder -2 -i] = right->keys[minOrder -2 -i] ;
        right->childs[2*minOrder -1 -i] = right->childs[minOrder -1-i] ;
    }
    right->childs[minOrder] = right->childs[0] ;
    //
    right->keys[minOrder-1] = parent->keys[location] ;
    //
    for(int i = 0 ; i < minOrder -1 ; i++)
    {
        right->keys[i] = left->keys[i] ;
        right->childs[i] = left->childs[i] ;
    }
    right->childs[minOrder -1] = left->childs[minOrder -1] ;
    //ɾ�����ڵ�Ĺؼ��ּ���ָ��
    //delete left ;
    for(int i = location ; i< parent->keyNum -1 ; i++)
    {
        parent->keys[i] = parent->keys[i+1] ;
        parent->childs[i] = parent->childs[i+1] ;
    }
    parent->childs[parent->keyNum-1] = parent->childs[parent->keyNum] ;
    parent->keyNum -- ;
    if(parent->keyNum == 0)
    {
        parent = right ;
    }
    virtualDiskWrite(parent) ;
    virtualDiskWrite(right) ;
    return true ;
}
template <class type>
bool BTree<type>::toLeftMerge(BTNode<type>* left,BTNode<type>* &parent,BTNode<type>* right,int location)
{
    left->keyNum = 2* minOrder -1 ;
    left->keys[minOrder -1] = parent->keys[location] ;
    for(int i = 0 ; i < minOrder -1; i++)
    {
        left->keys[minOrder+i] = right->keys[i] ;
        left->childs[minOrder+i] = right->childs[i] ;
    }
    left->childs[2*minOrder -1] = right->childs[minOrder-1] ;
    //�����׽ڵ㼰��ָ��
   // delete right ;
    for(int i = location ; i< parent->keyNum -1 ; i++)
    {
        parent->keys[i] = parent->keys[i+1] ;
        parent->childs[i+1] = parent->childs[i+2] ;
    }
    parent->keyNum -- ;
    if(parent->keyNum == 0)
    {
        parent = left ;
    }
    virtualDiskWrite(parent) ;
    virtualDiskWrite(left) ;
    return true ;
}
#endif // BTREE_H_INCLUDED
