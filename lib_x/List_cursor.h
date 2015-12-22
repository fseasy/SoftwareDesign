#ifndef LIST_CURSOR_H_INCLUDE
#define LIST_CURSOR_H_INCLUDE
#define MAX 100
/**
    **数据结构：线性表
    **实现方式：静态链表
    **实现功能：插入，删除，搜索，读取，位置移动
    **特殊说明：1.返回的位置的数据类型为int型
                2.插入，删除，读取是位置的后一个元素，相应的搜索以及first（）返回目标
                  元素的前一个元素位置。end（）函数及位置移动函数正常返回位置
                3.使用模板类实现
                4.在给定MAX空间下动态内存分配，有信息输出到控制台
*/
template <class type>
class data
{
public :
    data()
    {

    }
    void setVal(type val)
    {
        this->val = val ;
    }
    void setNext(int next)
    {
        this->next = next ;
    }
    type getVal()
    {
        return val ;
    }
    int getNext()
    {
        return next ;
    }
private :
    type val ;
    int next ;
} ;
template <class type>
class ListCursor
{
public :
    ListCursor() ;
    int getNode() ;
    void freeNode(int position) ;
    bool Insert(type val,int position) ;
    bool Delete(int position) ;
    int Locate(type x) ;
    type Retrieve(int position) ;
    int first() ;
    int end() ;
    int previous(int position) ;
    int next(int position) ;
private :
    data<type> * SPACE ;
    int avail ;
    int head;
} ;
template <class type>
ListCursor<type>::ListCursor()
{
    SPACE = new data<type>[MAX] ;
    for(int i = 0 ; i < MAX ; i++)
    {
        SPACE[i].setNext(i+1) ;

    }

    SPACE[1].setNext(-1) ;//作为表头
    SPACE[MAX-1].setNext(-1) ;//总空间
    avail = 0 ;
    head = 1 ;
    SPACE[avail].setNext(2) ; //由于表头不存储元素
}
template <class type>
int ListCursor<type>::getNode()
{
    if(SPACE[avail].getNext() != -1)
    {
        int position = SPACE[avail].getNext() ;
        SPACE[avail].setNext(SPACE[position].getNext()) ;//获取下一个可用空闲节点
        std::cout <<"\n---------内存信息-----------\n\n"
                  <<"给元素分配内存,空间大小为"<<sizeof(SPACE[0])<<"字节，地址为"
                  <<&SPACE[position]
                  <<"\n\n----------------------------\n" ;

        return position ;
    }
    return -1 ;

}
template <class type>
void ListCursor<type>::freeNode(int position)
{
    if(position == -1)
    return ;
    SPACE[position].setNext(SPACE[avail].getNext()) ;
    SPACE[avail].setNext(position) ;
    std::cout  <<"\n-----------内存信息------------\n\n"
               <<"回收元素占用的内存，空间大小为"<<sizeof(SPACE[position]) <<"字节，地址为"
               <<&SPACE[position]
               <<"\n\n-------------------------------\n" ;
}
template <class type>
bool ListCursor<type>::Insert(type val,int position)//在position位置之后插入
{
    int newNode = getNode() ;
    if(newNode == -1)
    return false ;
    else
    {
        SPACE[newNode].setVal(val) ;
        SPACE[newNode].setNext(SPACE[position].getNext()) ;
        SPACE[position].setNext(newNode) ;
        return true ;
    }
}
template <class type>
bool ListCursor<type>::Delete(int position)//删除position后的元素
{
    if(position == -1)
    return false ;
    else
    {
        int next = SPACE[position].getNext() ;
        if(next == -1)
        return false ;
        else
        {
            SPACE[position].setNext(SPACE[next].getNext()) ;
            freeNode(next) ;
            return true ;
        }

    }
}
template <class type>
int ListCursor<type>::Locate(type x) //返回值为x的元素的前一个元素指针，与insert和delete吻合
{
    int pos = head ;
    while(SPACE[pos].getNext() != -1)
    {
        int tmp = SPACE[pos].getNext() ;
        if(SPACE[tmp].getVal() == x)
        return pos ;
        else
        pos = tmp ;
    }
    return -1 ;
}
template <class type>
type ListCursor<type>::Retrieve(int position)//返回position之后的元素，与locate对应
{
  if(position == -1)
  return NULL ;
  int tmp = SPACE[position].getNext() ;
  if(tmp == -1)
  return NULL ;
  return SPACE[tmp].getVal() ;
}
template <class type>
int ListCursor<type>::first() //同样返回第一个元素的前一个元素，即表头
{
    if(SPACE[head].getNext() == -1)
    return -1 ;
    else
    return head ;
}
template <class type>
int ListCursor<type>::end()
{
    int pos = head ;
    if(SPACE[pos].getNext() == -1)
    return head;
    while(SPACE[pos].getNext() != -1)
    {
        pos = SPACE[pos].getNext() ;
    }
    return pos ;
}
template <class type>
int ListCursor<type>::previous(int position)
{
    if(position < 2)
    return -1 ;
    int pos = head ;
    while(SPACE[pos].getNext() != -1)
    {
        if(SPACE[pos].getNext() == position)
        {
            return pos ;
        }
        pos = SPACE[pos].getNext() ;
    }
    return -1 ;
}
template <class type>
int ListCursor<type>::next(int position)
{
    if(position < 1)
    return -1 ;
    else
    return SPACE[position].getNext() ;
}
#endif
