#ifndef MFSET_H_INCLUDED
#define MFSET_H_INCLUDED
/**
    **���ݽṹ�����鼯
    **ʵ�ַ�ʽ������˫�ױ�ʾ��
    **ʵ�ֹ��ܣ��ȼ��࣬�ϲ����ϣ���Ԫ�صĸ�Ԫ��,�鿴����
*/
class Mfset
{
    public :
    Mfset() ;
    Mfset(int n) ;
    ~Mfset() ;
    void Init(int x) ;
    int Find(int x) ;
    void Union(int a,int b) ;
    bool isEquivalence(int a , int b) ;
    void Equivalence() ;
    void printMFSET() ;
    private :
    int max ;
    struct Node
    {
        int father ;
        int count ; //��Ȩ
    }* MFSET  ;//�±��ʾ��Ԫ�أ���fatherֵ��ʾ���ڵ����MFSET������±�
                //�涨MFSET����ֵΪ0��ʾ��Ԫ��Ϊ���������и��ڵ�
} ;
Mfset::Mfset()
{
    max = 11 ;
    MFSET = new Node[max] ;
}
Mfset::Mfset(int n)
{
    max = n+1 ;
    MFSET = new Node[max] ;
}
Mfset::~Mfset()
{
    delete [] MFSET ;
}
void Mfset::Init(int x)
{
    MFSET[x].father = 0 ;
    MFSET[x].count = 1 ;
}
int Mfset::Find(int x)
{
    int tmp = x ;
    while(MFSET[tmp].father != 0)
    {
        tmp =MFSET[tmp].father ;
    }
    return tmp ;//���ظ�����MFSET������±�
}
void Mfset::Union(int a,int b)
{
    if(MFSET[a].count>MFSET[b].count)
    {
        MFSET[b].father = a ;
        MFSET[a].count+=MFSET[b].count ;
    }
    else
    {
        MFSET[a].father = b ;
        MFSET[b].count+=MFSET[a].count ;
    }
}
bool Mfset::isEquivalence(int a , int b)
{
    if(Find(a) == Find(b))
    return true ;
    else
    return false ;
}
void Mfset::Equivalence()
{
    std::cout <<"��ʼ������\n" ;
    for(int i = 1 ; i< max ; i++ )
    {
        Init(i) ;//�Ǽ���iֻ����Ԫ��i
    }
    int a,b ;
    while(std::cout <<"������ȼ۶ԣ����� 0 0 �������ȼ۶Է�Χ1~"<<max-1<<"\n")
    {
        std::cin >>a >>b ;
        if(a== 0 && b == 0)
        break ;
        int rootA = Find(a) ;
        int rootB = Find(b) ;
        std::cout <<"Ԫ��"<<a<<"��"<<"����"<<rootA<<"�У�"<<"Ԫ��"<<b<<"�ڼ���"<<rootB<<"��\n" ;
        if(rootA != rootB)
        {
            Union(rootA,rootB) ;
            std::cout<<"����"<<rootA <<"��"<<"����"<<rootB<<"�ϲ�\n" ;
        }
        else
        {
            std::cout <<"����"<<rootA<<"��"<<"����"<<rootB<<"�Ѿ���һ�����У�����ϲ�\n" ;
        }
    }

}
void Mfset::printMFSET()
{
    std::cout <<"����Ϊ\n" ;
    bool isPrint[max] ;
    for(int i = 0 ; i < max ; i++)
    {
        isPrint[i] =  false ;
    }
    for(int i = 1 ; i< max ; i++)
    {
        if(isPrint[i]==false)
        {
            std::cout <<"{ " ;
            int root = Find(i) ;
            for(int k = 1 ; k< max; k++)
            {
                if(isPrint[k]== false&&Find(k) == root)
                {
                    std::cout <<k <<" " ;
                    isPrint[k] = true ;
                }
            }
            std::cout <<"} \n" ;
        }
    }
}
#endif // MFSET_H_INCLUDED
