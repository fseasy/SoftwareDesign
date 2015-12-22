#ifndef LIST_ARRAY_H_INCLUDE
#define LIST_ARRAY_H_INCLUDE
#define INVALID -1
#define MAX 100
/**
    ���ݽṹ �� ���Ա����飩
    ʵ�ֹ��ܣ����룬ɾ������ȡ��һ�������һ����
              ָ��λ��ǰһ������һ��Ԫ��λ�ã���ȡ
              ָ��λ�õ�Ԫ��ֵ
    ʵ�ַ�ʽ �� �������ͣ�ģ����
*/
template <class type>
class List
{
public :
    List() ;
    List(int n) ;
    int first() ;
    int end() ;
    int getAvail() ;
    bool Insert(type x,int position) ;
    bool Delete(int position) ;
    int Locate(type x) ;
    type Retrieve(int position) ;
    int previous(int position) ;
    int next(int postion) ;
private :
    int last ; //���ݸ���
    int max ; //���Ա�����
    type * data ;
} ;
template <class type>
List<type>::List()
{
    max = MAX ;
    data = new type[max] ;
    last = 0 ;
}
template <class type>
List<type>::List(int n)
{
    max = n ;
    data = new type[max] ;
    last = 0 ;
}
template <class type>
int List<type>::first()
{
    if(last >= 1)
        return 1 ;
    else
        return INVALID ;
}
template <class type>
int List<type>::end()
{
    if(last >= 1)
        return last ;
    else
        return INVALID ;
}
template <class type>
int List<type>::getAvail()
{
    return last+1 ;
}
template <class type>
bool List<type>::Insert(type x,int position)
{
    if(last>=max-1) //����
        return false ;
    else if(position >last+1 || position < 1)//λ�ò��Ϸ���Ҫ�����Ա�������
        return false ;
    else
    {
        for(int i = last+1 ; i >position ; i--)
        {
            data[i] = data[i-1] ;
        }
        data[position] = x ;
        last++ ;
        return true ;
    }

}
template <class type>
bool List<type>::Delete(int position)
{
    if(position < 1 || position > last)
    return false ;
    else
    {
     for(int i = position ; i < last -1 ; i++)
     {
      data[i] = data[i+1] ;
     }
     last-- ;
     return true ;

    }
}
template <class type>
int List<type>::Locate(type x)
{
    for(int i = 1 ; i <= last ; i++)
    {
            if(data[i] == x)
            return i ;
    }
    return INVALID ;

}
template <class type>
type List<type>::Retrieve(int position)
{
    if(position < 1 || position > last)
    {
     return NULL ;
    }
    else
    {
     return data[position] ;

    }
}
template <class type>
int List<type>::previous(int position)
{
    if(position <= 1)
    return INVALID ;
    else
    return position-1 ;
}
template <class type>
int List<type>::next(int position)
{
    if(position < last && position >= 0)
    return position+1 ;
    else
    return INVALID ;

}

#endif
