#ifndef MFSET_H_INCLUDED
#define MFSET_H_INCLUDED
/**
    **数据结构：并查集
    **实现方式：树的双亲表示法
    **实现功能：等价类，合并集合，求元素的根元素,查看集合
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
        int count ; //加权
    }* MFSET  ;//下标表示该元素，其father值表示父节点的在MFSET数组的下标
                //规定MFSET数组值为0表示该元素为根，不再有父节点
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
    return tmp ;//返回根的在MFSET数组的下标
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
    std::cout <<"初始化集合\n" ;
    for(int i = 1 ; i< max ; i++ )
    {
        Init(i) ;//是集合i只包含元素i
    }
    int a,b ;
    while(std::cout <<"请输入等价对（输入 0 0 结束）等价对范围1~"<<max-1<<"\n")
    {
        std::cin >>a >>b ;
        if(a== 0 && b == 0)
        break ;
        int rootA = Find(a) ;
        int rootB = Find(b) ;
        std::cout <<"元素"<<a<<"在"<<"集合"<<rootA<<"中，"<<"元素"<<b<<"在集合"<<rootB<<"中\n" ;
        if(rootA != rootB)
        {
            Union(rootA,rootB) ;
            std::cout<<"集合"<<rootA <<"和"<<"集合"<<rootB<<"合并\n" ;
        }
        else
        {
            std::cout <<"集合"<<rootA<<"和"<<"集合"<<rootB<<"已经在一棵树中，不需合并\n" ;
        }
    }

}
void Mfset::printMFSET()
{
    std::cout <<"集合为\n" ;
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
