#ifndef LIST_CURSOR_H_INCLUDE
#define LIST_CURSOR_H_INCLUDE
#define MAX 100
/**
    **���ݽṹ�����Ա�
    **ʵ�ַ�ʽ����̬����
    **ʵ�ֹ��ܣ����룬ɾ������������ȡ��λ���ƶ�
    **����˵����1.���ص�λ�õ���������Ϊint��
                2.���룬ɾ������ȡ��λ�õĺ�һ��Ԫ�أ���Ӧ�������Լ�first��������Ŀ��
                  Ԫ�ص�ǰһ��Ԫ��λ�á�end����������λ���ƶ�������������λ��
                3.ʹ��ģ����ʵ��
                4.�ڸ���MAX�ռ��¶�̬�ڴ���䣬����Ϣ���������̨
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

    SPACE[1].setNext(-1) ;//��Ϊ��ͷ
    SPACE[MAX-1].setNext(-1) ;//�ܿռ�
    avail = 0 ;
    head = 1 ;
    SPACE[avail].setNext(2) ; //���ڱ�ͷ���洢Ԫ��
}
template <class type>
int ListCursor<type>::getNode()
{
    if(SPACE[avail].getNext() != -1)
    {
        int position = SPACE[avail].getNext() ;
        SPACE[avail].setNext(SPACE[position].getNext()) ;//��ȡ��һ�����ÿ��нڵ�
        std::cout <<"\n---------�ڴ���Ϣ-----------\n\n"
                  <<"��Ԫ�ط����ڴ�,�ռ��СΪ"<<sizeof(SPACE[0])<<"�ֽڣ���ַΪ"
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
    std::cout  <<"\n-----------�ڴ���Ϣ------------\n\n"
               <<"����Ԫ��ռ�õ��ڴ棬�ռ��СΪ"<<sizeof(SPACE[position]) <<"�ֽڣ���ַΪ"
               <<&SPACE[position]
               <<"\n\n-------------------------------\n" ;
}
template <class type>
bool ListCursor<type>::Insert(type val,int position)//��positionλ��֮�����
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
bool ListCursor<type>::Delete(int position)//ɾ��position���Ԫ��
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
int ListCursor<type>::Locate(type x) //����ֵΪx��Ԫ�ص�ǰһ��Ԫ��ָ�룬��insert��delete�Ǻ�
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
type ListCursor<type>::Retrieve(int position)//����position֮���Ԫ�أ���locate��Ӧ
{
  if(position == -1)
  return NULL ;
  int tmp = SPACE[position].getNext() ;
  if(tmp == -1)
  return NULL ;
  return SPACE[tmp].getVal() ;
}
template <class type>
int ListCursor<type>::first() //ͬ�����ص�һ��Ԫ�ص�ǰһ��Ԫ�أ�����ͷ
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
