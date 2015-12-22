#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <string>
#include <cmath>
#define EMPTY -1
#define DELETED -2
#define INVALID -3
#define MODHASH 1
#define GETINTHASH 2
#define A 0.618
//����ɢ�к���
/*
    һ���ǳ��෨��MODHASH
    ����һ�������ȡ������GETINTHASH
    ���ȡ������
    ȡA = 0.618������5��1 ����2���ƽ������
    Ȼ����KEY����A�����ȡ��С�����֣�
    Ȼ����Ͱ������MAX���Ը�С����ǿ��ת��Ϊ�����󷵻�
*/
/**
    **���ݽṹ��Hash��
    **ʵ�ֹ��ܣ����룬ɾ��������
    **ʵ�ַ�ʽ����ɢ�У���ɢ�У�����������ɢ��
*/
using namespace std ;
bool isPrimeNum(int n)
{
    if(n % 2 == 0)
        return false ;
    int sqrtN = static_cast<int>(sqrt(n)) ;
    for(int i = 3 ; i < sqrtN +1 ; i+=2)
    {
        if(n % i == 0)
            return false ;
    }
    return true ;
}
int getMaxPrimeNum(int n )
{
    for(int i = n ; i > 0 ; i--)
    {
        if(isPrimeNum(i))
            return i ;
    }
    return INVALID ;
}


struct StaffInfo
{
    int id ; //ͬʱ��Ϊkey�ͱ�ʶΪ�ջ�DELETED��Ԫ��
    string name ;
} ;
class Hash //���ں����󶨣��ø���ָ��ָʾ�����ࣩ
{
public :
    virtual int Search(int key) = 0  ;
    virtual bool Insert(StaffInfo records)=0 ;
    virtual bool Delete(int key) = 0 ;
    virtual int getInsTimes()=0 ;
    virtual int getSeaTimes()=0;

} ;
class HashTable_inner :  public Hash//��ɢ�б�
{
public :
    HashTable_inner(int n) ;
    HashTable_inner(int n,int type) ;
    int Search(int key ) ;
    bool Insert(StaffInfo records) ;
    bool Delete(int key) ;
    StaffInfo Retrieve(int key) ;
    int getSeaTimes() ;
    int getInsTimes() ;
private :
    int hash(int key) ;
    int max ;
    StaffInfo * hashTable ;
    int primeNum ;
    int InsertTimes ;
    int searchTimes ;
    int HASHTYPE ;
} ;
struct Node
{
    StaffInfo data ;
    Node * next ;
} ;
//----------------------------------
class HashTable_open : public Hash//��ɢ��
{
public :
    HashTable_open(int n) ;
    HashTable_open(int n , int HASHTYPE) ;
    bool Insert(StaffInfo val) ;
    int Search(int key) ;
    bool Delete(int key) ;
    StaffInfo Retrieve(int key) ;
    int getInsTimes() ;
    int getSeaTimes() ;
private :
    int hash(int key) ;
    int max ;
    Node ** hashTable ;//ɢ�б���ֻ��ָ��
    int insTimes ;
    int seaTimes ;
    int primeNum ;
    int HASHTYPE ;
} ;
//----------------------------------------
class HashTable_overflow : public Hash //����������ɢ��
{
public :
    HashTable_overflow(int n) ;
    HashTable_overflow(int n , int HASHTYPE) ;
    int Search(int k) ;
    bool Insert(StaffInfo records) ;
    bool Delete(int key) ;
    int getInsTimes() ;
    int getSeaTimes() ;
private :
    int hash(int key) ;
    Node * hashTable ;
    int primeNum ;
    int insTimes ;
    int seaTimes ;
    int max ;
    int HASHTYPE ;
} ;
HashTable_inner::HashTable_inner(int n)
{
    max = n ;
    hashTable = new StaffInfo[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i].id = EMPTY ;
    }
    primeNum = getMaxPrimeNum(max) ;
    searchTimes = 0 ;
    InsertTimes = 0 ;
    HASHTYPE = MODHASH ;
}
HashTable_inner::HashTable_inner(int n, int type)
{
    max = n ;
    hashTable = new StaffInfo[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i].id = EMPTY ;
    }
    primeNum = getMaxPrimeNum(max) ;
    searchTimes = 0 ;
    InsertTimes = 0 ;
    if(type == MODHASH)
    {
        HASHTYPE = MODHASH ;
    }
    else
    {
        HASHTYPE = GETINTHASH ;
    }
}
int HashTable_inner::hash(int key)
{
    if(HASHTYPE == MODHASH)
    {
        return key%primeNum ; //ɢ�к������������෨
    }
    else
    {
        double x = key * A ;
        double xFloat = x- static_cast<int>(x) ;
        return static_cast<int>(max*xFloat) ;
    }
}
bool HashTable_inner::Insert(StaffInfo records)
{
    int reHash = 0 ;
    int counter = 1 ;
    int first = hash(records.id) ;
    int hashCode = first ;
    while(counter < max && hashTable[hashCode].id != records.id)
    {
        InsertTimes++ ;
        hashCode = (first+reHash) % max ;
        if(hashTable[hashCode].id == EMPTY || hashTable[hashCode].id == DELETED)
        {
            hashTable[hashCode].id = records.id ;
            hashTable[hashCode].name = records.name ;
            return true ;
        }
        else
        {
            reHash+=(counter*counter) ;
            counter++ ;
        }

        if(counter >= max)
        {
            return false ;
        }

    }
    return false ;
}
int HashTable_inner::Search(int key)
{
    int first = hash(key) ;
    int counter = 0 ;
    int reHash = 0 ;
    int hashCode = first ;
    while(counter < max && hashTable[hashCode].id != EMPTY)
    {
        searchTimes++ ;
        if(hashTable[hashCode].id == key)
        {
            return hashCode ;
        }
        else
        {
            counter++ ;
            reHash = counter*counter ;
            hashCode = (hashCode + reHash)% max ;
        }
    }
    return INVALID ;
}
bool HashTable_inner::Delete(int key)
{
    int location = Search(key) ;
    if(location  != INVALID )
    {
        hashTable[location].id = DELETED ;
        return true ;
    }
    else
    {
        return false ;
    }
}
int HashTable_inner::getSeaTimes()
{
    return searchTimes ;
}
int HashTable_inner::getInsTimes()
{
    return InsertTimes ;
}
//------------------------------------------
HashTable_open::HashTable_open(int n)
{
    max = n ;
    hashTable = new Node*[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i] = NULL ;
    }
    insTimes = 0 ;
    seaTimes = 0 ;
    HASHTYPE = MODHASH ;
    primeNum = getMaxPrimeNum(max) ;

}
HashTable_open::HashTable_open(int n , int HASHTYPE)
{
    max = n ;
    hashTable = new Node * [max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i] = NULL ;
    }
    this->HASHTYPE = HASHTYPE ;
    primeNum = getMaxPrimeNum(max) ;
}
int HashTable_open::hash(int key)
{
    if(HASHTYPE == MODHASH)
    {
        return key%primeNum ;
    }
    else
    {
        double x = key * A ;
        double xFloat = x - (int)x ;
        return (int)(xFloat* max) ;
    }
}
bool HashTable_open::Insert(StaffInfo val)
{

    int hashCode = hash(val.id) ;
    Node * tmp = new Node ;
    tmp->data.id = val.id ;
    tmp->data.name = val.name ;
    Node * pos = hashTable[hashCode] ;
    while(pos != NULL)
    {
        if(pos->data.id == val.id)
        {
            return false ; //�ظ�������,������
        }
        insTimes++ ;
        pos = pos->next ;
    }

    tmp->next = hashTable[hashCode] ;
    hashTable[hashCode] = tmp ; //���뵽hash���һ��λ��
    insTimes++ ;
    return true ;
}
int HashTable_open::Search(int key)
{
    seaTimes++ ;
    int hashCode = hash(key) ;
    Node * pos = hashTable[hashCode] ;
    while(pos != NULL)
    {
        if(pos->data.id == key)
        {
            return hashCode ;
        }
        seaTimes++ ;
        pos = pos->next ;
    }
    return INVALID ;
}
bool HashTable_open::Delete(int key)
{
    int hashCode  = hash(key) ;
    Node * pos = hashTable[hashCode] ;
    if(pos != NULL)
    {
        if(pos->data.id == key)
        {
            delete pos ;
            pos = NULL ;
            return true ;
        }
        else
        {
            Node * posNext = pos->next ;
            while(posNext != NULL)
            {
                if(posNext->data.id == key)
                {
                    pos->next = posNext->next ;
                    delete posNext ;
                    return true ;
                }
            }
            return false ;
        }
    }
    return false ;
}
int HashTable_open::getInsTimes()
{
    return insTimes ;
}
int HashTable_open::getSeaTimes()
{
    return seaTimes ;
}
//---------------------------------
HashTable_overflow::HashTable_overflow(int n)
{
    max = n ;
    hashTable = new Node[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i].data.id = EMPTY ;
        hashTable[i].next = NULL ;
    }
    primeNum = getMaxPrimeNum(max) ;
    insTimes = 0 ;
    seaTimes = 0 ;
    HASHTYPE = MODHASH ;
}
HashTable_overflow::HashTable_overflow(int n,int HASHTYPE)
{
    max = n ;
    hashTable = new Node[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        hashTable[i].data.id = EMPTY ;
        hashTable[i].next = NULL ;
    }
    this->HASHTYPE = HASHTYPE ;
    insTimes = 0 ;
    seaTimes = 0 ;
    primeNum = getMaxPrimeNum(max) ;
}
int HashTable_overflow::hash(int key)
{
    if(HASHTYPE == MODHASH)
    {
        return key%primeNum ;
    }
    else
    {
        double x = key * A ;
        double xFloat =x - (int)x ;
        return (int)(xFloat*max) ;
    }
}
bool HashTable_overflow::Insert(StaffInfo records)
{
    int hashCode = hash(records.id) ;
    if(hashTable[hashCode].data.id == EMPTY)
    {
        insTimes++ ;
        hashTable[hashCode].data.id = records.id ;
        hashTable[hashCode].data.name = records.name ;
        return true ;
    }
    else if(hashTable[hashCode].data.id == records.id)
    {
        insTimes++ ;
        return false ;
    }
    else
    {
        Node * pos = hashTable[hashCode].next ;
        while(pos != NULL)
        {
            if(pos->data.id == records.id)
            {
                insTimes++ ;
                return false ;
            }
            insTimes++ ;
            pos = pos->next ;
        }
        pos = new Node ;
        pos->data.id =records.id ;
        pos->data.name = records.name ;
        pos->next = hashTable[hashCode].next ;
        hashTable[hashCode].next = pos ;//���뵽����֮��
        insTimes++ ;
        return true ;
    }
}
int HashTable_overflow::Search(int key)
{
    int hashCode = hash(key) ;
    seaTimes++ ;
    if(hashTable[hashCode].data.id == EMPTY)
    {
        return INVALID ;
    }
    else if(hashTable[hashCode].data.id == key)
    {
        return hashCode ;
    }
    else
    {
        Node * pos = hashTable[hashCode].next ;
        while(pos != NULL)
        {
            if(pos->data.id == key)
            {
                seaTimes++ ;
                return hashCode ;
            }
            seaTimes++ ;
            pos = pos->next ;
        }
        return INVALID ;
    }
}
bool HashTable_overflow::Delete(int key)
{
    int hashCode = hash(key) ;
    if(hashTable[hashCode].data.id == EMPTY)
    {
        return false ;
    }
    else if(hashTable[hashCode].data.id == key)
    {
        if(hashTable[hashCode].next == NULL)
        {
            hashTable[hashCode].data.id = EMPTY ;
            return true ;
        }
        else
        {
            Node * pos = hashTable[hashCode].next ;
            hashTable[hashCode].data.id = pos->data.id ;
            hashTable[hashCode].data.name = pos->data.name ;
            hashTable[hashCode].next = pos->next ;
            delete pos ;
            pos = NULL ;
            return true ;
        }
    }
    else
    {
        Node * pos = &hashTable[hashCode] ;
        while(pos->next != NULL)
        {
            if(pos->next->data.id == key)
            {
                Node * tmp = pos->next ;
                pos->next = tmp->next ;
                delete pos->next ;
                return true ;
            }
            pos = pos->next ;
        }
        return false ;
    }
}
int HashTable_overflow::getInsTimes()
{
    return insTimes ;
}
int HashTable_overflow::getSeaTimes()
{
    return seaTimes ;
}
#endif // HASHTABLE_H_INCLUDED
