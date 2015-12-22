#ifndef HEAP_MAX_H_INCLUDE
#define HEAP_MAX_H_INCLUDE
/**
    **数据结构：最大堆
    **实现方式：模板类
    **实现功能：判空、满，插入堆，删除优先级（key）最大元素
*/
template <class type>
class Element
{
    public :
    Element()
    {
    }
    Element(int key,type info)
    {
        this->key = key ;
        this->info = info ;
    }
    void setKey(int key)
    {
        this->key = key ;
    }
    void setInfo(type info)
    {
        this->info = info ;
    }
    int getKey()
    {
        return key ;
    }
    type getInfo()
    {
        return info ;
    }
    void operator=(Element<type> val)
    {
        this->key = val.getKey() ;
        this->info = val.getInfo() ;
    }
    private :
    int key ; //优先级
    type info ; //代表具体的事件
} ;
template <class type>
class MaxHeap
{
    public :
    MaxHeap() ;
    MaxHeap(int n) ;
    ~MaxHeap() ;
    bool isHeapFull() ;
    bool isHeapEmpty() ;
    bool Insert(Element<type> val) ;
    Element<type>* DeleteMax() ;
    private :
    Element<type>* data ;
    int elements_num ;
    int max ;
} ;
template <class type>
MaxHeap<type>::MaxHeap()
{
        max = 100 ;
        data = new Element<type>[max+1] ;//数组第0号元素不存放数据
        elements_num = 0 ;
}
template <class type>
MaxHeap<type>::MaxHeap(int n)
{
    max = n ;
    data = new Element<type>[max+1] ;
    elements_num = 0 ;
}
template <class type>
MaxHeap<type>::~MaxHeap()
{
    delete [] data ;
}
template <class type>
bool MaxHeap<type>::isHeapFull()
{
    if(elements_num >=max)
    return true ;
    else
    return false ;
}
template <class type>
bool MaxHeap<type>::isHeapEmpty()
{
    if(elements_num == 0)
    return true ;
    else
    return false ;
}
template <class type>
bool MaxHeap<type>::Insert(Element<type> val)
{
    int pos = elements_num+1 ;
    if(isHeapFull())
    return false ;
    elements_num++ ;
    while(pos != 1 && val.getKey()>data[pos/2].getKey())
    {
        data[pos] = data[pos/2] ;
        pos/=2 ;
    }
   data[pos] = val ;
    return true ;
}
template <class type>
Element<type>* MaxHeap<type>::DeleteMax()
{
    if(isHeapEmpty())
    return NULL ;
    Element<type>* tmp,*max ;
    max = new Element<type>() ;
    *max = data[1] ;
    int parent = 1 ;
    int child = 2 ;
    tmp = &data[elements_num] ;
    elements_num-- ;
    while(child <= elements_num)
    {
        if(child < elements_num && data[child].getKey()<data[child+1].getKey())
        child++ ;
        if(tmp->getKey()>data[child].getKey())
        break ;
        data[parent] = data[child] ;
        parent = child ;
        child = 2*parent ;
    }
    data[parent] = *tmp ;
    return max ;
}
#endif
