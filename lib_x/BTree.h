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
    keys = new type[minOrder*2 -1] ;//关键字的范围为minOrder-1~2*minOrder -1(根节点至少有一个关键字)
    childs = new BTNode *[minOrder *2] ;//孩子节点（指针）的范围为minOrder ~ 2*minOrder(根节点至少有两个孩子)
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
    void splitChild(BTNode<type> * parent,int index , BTNode<type>* fullChild) ;//需要保证parent不满

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
        std::cout <<"叶子节点" ;
    }
    else
    {
        std::cout <<"不是叶子节点" ;
    }
    std::cout <<"\t关键字数为"<<tmp->keyNum <<" " ;
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
    std::cout <<"层序打印结果:\n" ;
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
    搜索，输入搜索关键字，用于保存结果的BTNode指针，关键字索引位置，
    返回是否找到
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
        //线性定位
        index = pos->keyNum -1 ;
        while(index >= 0 && keyCompare(pos->keys[index],key) == bigger)
        {
            index -- ;
        }
        if(keyCompare(pos->keys[index],key) == equal)//找到
        {
            node = pos ;
            return true ;
        }
        index++ ;//向下递归查找
        return searchX(pos->childs[index],key,node,index) ;

    }
}
template <class type>
bool BTree<type>::search(type key,BTNode<type> * & node,int & index)
{
    BTNode <type> * pos = root ;
    if(pos->isLeaf == true)
    {
        //在叶子节点中进行二分查找
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
        if(keyCompare(pos->keys[index],key) == equal)//找到
        {
            node = pos ;
            return true ;
        }
        index++ ;//向下递归查找
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
    //首先判断是否是叶子节点，若是，则要在该节点插入（不用考虑分裂情况）；不是，则选择合适的
    //child指针递归插入（递归之前需考虑child指向的节点是够已满，考虑分裂情况）
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
            current->keys[index] = newKey ;//插入新关键字
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
                if(newKey >current->keys[index+1])//下层分裂后该节点(下层的父亲节点)变化，需要比较新添加的关键字和从下层到该层的关键字大小
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
    newNode->keyNum = minOrder -1 ;//关键字个数为最少的情况
    newNode->isLeaf = fullChild->isLeaf ; //与fullChild同层
    for(int i = 0 ; i < minOrder -1 ; i++)
    {
        newNode->keys[i] = fullChild->keys[minOrder+i] ;//复制关键字
    }
    if(!fullChild->isLeaf)
    {
        for(int i = 0 ; i < minOrder ; i++)
        {
            newNode->childs[i] = fullChild->childs[minOrder+i] ; //复制孩子指针
        }
    }
    fullChild->keyNum = minOrder - 1 ;//更改原来节点的关键字个数
    //调整父亲节点,...C(index),K(index),c(index+1),K(index+1),...;需要在c（index）后插入k(fullChild[minOrder-1]),C（newNode）
    for(int i = parent->keyNum ; i> index+1 ; i--)
    {
        parent->keys[i] = parent->keys[i-1] ;
    }
    parent->keys[index+1] = fullChild->keys[minOrder -1] ; //插入关键字
    for(int i = parent->keyNum +1 ; i> index+2 ; i--)
    {
        parent->childs[i] = parent->childs[i-1] ;
    }
    parent->childs[index+2] = newNode ; //插入
    parent->keyNum++ ;//更改关键字的值
    //virtualDiskWrite(parent) ;
    //virtualDiskWrite(fullChild) ;
    //virtualDiskWrite(newNode) ;
}
/**
    开始删除操作

*/
template <class type>
bool BTree<type>::deleteX(BTNode<type>* &node,type key,BTNode<type>* &result,int &index)
{
    if(result == node)
    {
        //要删除的关键字在该节点内
        if(node->isLeaf == true)
        {
            //是叶节点
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
            //1.看右孩子是否满足条件
            if(rChild->keyNum >= minOrder)
            {
                //满足
                node->keys[index] = rChild->keys[0] ;//最左边关键字代替
                //
                result = rChild ;
                index = 0 ;
                key = rChild->keys[0] ;
                return deleteX(rChild,key,result,index);
            }
            else if(lChild->keyNum >= minOrder)
            {
                //满足
                node->keys[index] = lChild->keys[lChild->keyNum -1] ;
                //
                result = lChild ;
                index = lChild->keyNum -1 ;
                key = lChild->keys[index] ;
                return deleteX(lChild,key,result,index) ;
            }
            else
            {
                //合并，合到左边来
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
        //不在节点内
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
        //先查看是否在该节点内（此即根节点）
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
                //删除作为根的内节点，按从右到左的顺序，看能否用孩子节点中关键字补上该
                //根节点关键字，即把该根节点关键字下推（实际中采用替换的方式）
                //右孩子为childs[index+1],左孩子为index
                if(root->childs[index+1] ->keyNum >= minOrder)
                {
                    //右孩子满足条件，下推根节点关键字，用右孩子的最左边关键字替换该根节点关键字
                    root->keys[index] = root->childs[index+1]->keys[0] ;
                    //现在可以删除该右孩子的最左边关键字
                    result = root->childs[index+1] ;
                    index = 0 ;
                    return deleteX(root->childs[index+1],root->childs[index+1]->keys[0],result,index) ;
                }
                else if(root->childs[index]->keyNum >= minOrder)
                {
                    //右孩子不满足条件，左孩子满足下推条件，下推左孩子最右边关键字
                    BTNode<type>* lChild = root->childs[index] ;
                    root->keys[index] = lChild->keys[lChild->keyNum -1] ;
                    //现在可以删除该左孩子最右边关键字
                    result = lChild ;
                    index = lChild->keyNum -1 ;
                    return deleteX(lChild,lChild->keys[lChild->keyNum-1],result,index) ;
                }
                else
                {
                    //左右孩子都不满足条件，即左右孩子都只有minOrder -1 个关键字
                    //需要进行合并下推
                    //保留左孩子指针，即把该关键字和右孩子的关键字复制到左孩子，释放右孩子
                    //根节点变化
                    BTNode<type> * lChild = root->childs[index] ;
                    BTNode<type> * rChild = root->childs[index+1] ;//保留副本
                    for(int i = index ; i < root->keyNum -1 ; i++ )
                    {
                        root->keys[i] = root->keys[i+1] ;
                        root->childs[i+1] = root->childs[i+2] ;
                    }
                    root->keyNum-- ;//更改关键字数目
                    //左孩子复制工作

                    lChild->keys[lChild->keyNum] = key ;//将父亲节点关键字复制到左孩子
                    for(int i = lChild->keyNum+1 ; i< 2* minOrder -1 ; i++)
                    {
                        lChild->keys[i] = rChild->keys[i-minOrder] ;
                        lChild->childs[i] = rChild->childs[i-minOrder] ;
                    }
                    lChild->childs[2*minOrder -1] = rChild->childs[minOrder -1] ;
                    lChild->keyNum = 2*minOrder -1 ;
                    //delete rChild ;
                    //检查是否根节点已空
                    if(root->keyNum == 0)
                    {
                        root = lChild ;
                    }
                    //开始删除该节点
                    result = lChild ;
                    index = minOrder -1 ;
                    return deleteX(lChild,key,result,index) ;
                }
            }
        }
        else
        {
            //不在根节点内
            int i = root->keyNum - 1;
            while(i>= 0 && keyCompare(root->keys[i],key) == bigger)
            {
                i-- ;
            }
            i++ ;
            //目标锁定为root的第i+1个孩子
            //查看该孩子关键字个数是否>= minOrder
            if(root->childs[i]->keyNum >= minOrder)
            {
                return deleteX(root->childs[i],key,result,index) ;
            }
            else
            {
                //预处理，使要下到的节点关键字数>=minOrder
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
bool BTree<type>::preProcess(BTNode<type>* & parent,int & index)//index指孩子所在的索引
{
    //确保该孩子的关键字数目至少为minOrder个
    //先右后左的顺序
    //把右兄弟最左边关键字推到父亲关键字处，父亲节点关键字推到将要访问的节点处（最右边）
    //最左边关键字对应的孩子指针移动到移动后的待处理孩子的最后一个指针（即父亲关键字对应的指针）
    //注意更改KeyNum的值
    if(index == parent->keyNum)//该孩子在最右端
    {
        BTNode<type> * rChild = parent->childs[index] ;//待处理孩子
        BTNode<type> * lChild = parent->childs[index-1] ;
        if(lChild->keyNum >= minOrder)//足够
        {
            //将左兄弟最右边的关键字推到父亲节点的关键字，原父亲节点的关键字推到推到右孩子的最左边
            leftToParentToRight(lChild,parent,rChild,index-1) ;
            return true ;
        }
        else
        {
            //将左兄弟，父亲节点关键字归并到该孩子节点，注意，保留该孩子节点的指针（向下删除时已经确定了）
            toRightMerge(lChild,parent,rChild,index -1) ;
            index-- ;//索引发生变化,且只有这种情况下改变！！
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
    //右移右孩子元素
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
    //删除父节点的关键字及左指针
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
    //处理父亲节点及右指针
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
