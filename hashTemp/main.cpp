#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#define EMPTY -1
#define DELETED -2
#define INVALID -3
#define MODHASH 1
#define GETINTHASH 2
#define A 0.618

using namespace std;
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
struct Node
{
    StaffInfo data ;
    Node * next ;
} ;
class HashTable_open //��ɢ��
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
        pos = pos->next ;
    }
    insTimes++ ;
    tmp->next = hashTable[hashCode] ;
    hashTable[hashCode] = tmp ; //���뵽hash���һ��λ��
    return true ;
}
int HashTable_open::Search(int key)
{
    seaTimes++ ;
    int hashCode = hash(key) ;
    cout << hashCode <<" " ;
    Node * pos = hashTable[hashCode] ;
    while(pos != NULL)
    {
        if(pos->data.id == key)
        {
            return hashCode ;
        }
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
int main()
{
    const int small = 200 ;
    const int big = 10000 ;
    int randomNum_small[small] ;//С��ģ�����������
    int randomNum_big[big] ;//���ģ�����������
    int searchArraySmall[small] ;//��ӦС��ģ�Ĳ���Դ���ݣ�һ�����Բ������ݣ�hash���п϶����ڣ���һ���ٴ��������
    int searchArrayBig[big] ;//��Ӧ���ģ��������Դ


    //����α���������Χ0~2^16 -1
    srand(time(0)) ;
    for(int i = 0 ; i < small ; i++)
    {
        randomNum_small[i] = rand() ;
    }
    for(int i = 0 ; i < big ; i++)
    {
        randomNum_big[i] = rand() ;
    }
    //������������Դ
    for(int i = 0 ; i < small/2 ; i++)
    {
        searchArraySmall[i] = randomNum_small[i] ;
    }
    for(int i = small/2 ; i< small ; i++)
    {
        searchArraySmall[i] = rand() ;
    }
    for(int i = 0 ; i < big/2 ; i++)
    {
        searchArrayBig[i] = randomNum_big[i] ;
    }
    for(int i = big/2 ; i < big ; i++)
    {
        searchArrayBig[i] = rand() ;
    }
     HashTable_open x2(small*2) ;
    //test(x2,small,randomNum_small,searchArraySmall,"��ɢ�з�������׼����",rear) ;
    for(int i = 0 ; i < small ;i++)
    {
        StaffInfo tmp ;
        tmp.id = randomNum_small[i] ;
        tmp.name = tmp.id+"'s name" ;
        x2.Insert(tmp) ;
    }
    for(int i = 0 ; i < small ; i++)
    {
        x2.Search(searchArraySmall[i]) ;
    }
    return 0;
}
