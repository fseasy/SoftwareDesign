#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include "../lib_x/hashTable.h"
/**
    程序名称：散列结构性能测试程序
    实现功能：内散列，外散列，带溢出表的内散列的基准（填充因子0.5，数据规模小，插入数据随机
              查找数据一般是插入数据，一般是随机数据，散列函数为除余法）测试，满填充因子测试
             （填充因子为 1），改变散列函数测试（相乘取整法），增大数据规模（big）测试，改变
              查找数据分布（全部为插入的数据）测试。
    结论 ： 采用内散列法，当填充因子很大时（测试程序为1），插入查找次数巨大，效率低
            采用外散列法，当数据规模较大时，耗时较多（可能是由于频繁取址操作导致）
            采用带溢出表的内散列法，平均性能最好，（应该较外散列法在表不满时更耗空间）
*/
struct Info
{
    string type ;
    double times ;
    double insertRate ;
    double searchRate ;
    Info * next ;
} ;
void printResult(string type,int totalData,int sucInsert,int sucSearch,int insertTimes,int searchTimes,double times) ;
void test(Hash & x,int totalData,int insArray[] ,int seaArray[],string type,Info * & rear) ;
void printTotalInfo(Info * head) ;
int main()
{
    const int small = 300 ;
    const int big = 100000 ;
    int randomNum_small[small] ;//小规模随机插入数据
    int randomNum_big[big] ;//大规模随机插入数据
    int searchArraySmall[small] ;//对应小规模的查找源数据，一半来自插入数据（hash表中肯定存在），一半再次随机产生
    int searchArrayBig[big] ;//对应大规模查找数据源
    Info * head = new Info ;
    head->next = NULL ;
    Info * rear = head ;
    //产生伪随机数，范围0~2^16 -1
    srand(time(0)) ;
    for(int i = 0 ; i < small ; i++)
    {
        randomNum_small[i] = rand() ;
    }
    for(int i = 0 ; i < big ; i++)
    {
        randomNum_big[i] = rand() ;
    }
    //产生查找数据源
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
    //基准hash
    HashTable_inner x(small*2) ;
    test(x,small,randomNum_small,searchArraySmall,"内散列法—— 基准测试",rear) ;
    //改变填充因子
    HashTable_inner xFactorFull(small) ;
    test(xFactorFull,small,randomNum_small,searchArraySmall,"内散列法——改变填充因子",rear) ;
    //改变散列函数
    HashTable_inner xGETINTHASH(small*2,GETINTHASH) ;
    test(xGETINTHASH,small,randomNum_small,searchArraySmall,"内散列法——改变散列函数",rear) ;
    //改变数据规模
    HashTable_inner xBig(big*2) ;
    test(xBig,big,randomNum_big,searchArrayBig,"内散列法——改变数据规模",rear) ;
    //改变查找数据的分布（用添加的数据直接查找）
    HashTable_inner xDistribution(small*2) ;
    test(xDistribution,small,randomNum_small,randomNum_small,"内散列法——改变数据分布",rear) ;
    //外散列
    //基准测试
    HashTable_open x2(small*2) ;
    test(x2,small,randomNum_small,searchArraySmall,"外散列法——基准测试",rear) ;
    //改变填充因子
    HashTable_open x2FactorFull(small) ;
    test(x2FactorFull,small,randomNum_small,searchArraySmall,"外散列法——改变填充因子",rear) ;
    //改变散列函数
    HashTable_open x2GETINTHASH(small*2) ;
    test(x2GETINTHASH,small,randomNum_small,searchArraySmall,"外散列法——改变散列函数",rear) ;
    //改变数据规模
    HashTable_open x2Big(big*2) ;
    test(x2Big,big,randomNum_big,searchArrayBig,"外散列法——改变数据规模",rear) ;
    //改变查找数据分布
    HashTable_open x2Distribution(small*2) ;
    test(x2Distribution,small,randomNum_small,searchArraySmall,"外散列法—— 改变数据分布     ",rear) ;
    //带溢出表的内散列
    //基准测试
    HashTable_overflow x3(small*2) ;
    test(x3,small,randomNum_small,searchArraySmall,"带溢出表的内散列法——基准测试",rear) ;
    //改变填充因子
    HashTable_overflow x3FactorFull(small) ;
    test(x3FactorFull,small,randomNum_small,searchArraySmall,"带溢出表的内散列法——改变填充因子",rear) ;
    //改变散列函数
    HashTable_overflow x3GETINTHASH(small*2) ;
    test(x3GETINTHASH,small,randomNum_small,searchArraySmall,"带溢出表达的内散列法——改变散列函数",rear) ;
    //改变数据规模
    HashTable_overflow x3Big(big*2) ;
    test(x3Big,big,randomNum_big,searchArrayBig,"带溢出表的内散列法——改变数据规模",rear) ;
    //改变查找数据分布
    HashTable_overflow x3Distribution(small*2) ;
    test(x3Distribution,small,randomNum_small,randomNum_small,"带溢出表的内散列法——改变数据分布",rear) ;
    //输出汇总信息
    printTotalInfo(head) ;
    return 0;
}
void test(Hash & x,int totalData,int insArray[] ,int seaArray[],string type,Info * & rear)
{
    int sucInsTimes = 0 ;
    int sucSeaTimes = 0 ;
    clock_t startTime ;
    clock_t finishTime ;
    startTime = clock() ;
    for(int i = 0 ; i <totalData ; i++)
    {
        StaffInfo tmp ;
        tmp.id = insArray[i] ;
        tmp.name = tmp.id+"'s name" ;
        if(x.Insert(tmp))
        {
            sucInsTimes++ ;
        }
    }
    for(int i = 0 ; i < totalData ; i++)
    {
        if(x.Search(seaArray[i]) != INVALID)
        {
            sucSeaTimes++ ;
        }
    }
    finishTime = clock() ;
    Info * tmpInfo ;
    tmpInfo = new Info ;
    tmpInfo->type = type ;
    tmpInfo->times = (double)(finishTime-startTime)/CLOCKS_PER_SEC ;
    tmpInfo->searchRate = ((double)x.getSeaTimes()/totalData) ;
    tmpInfo->insertRate = ((double)x.getInsTimes()/totalData) ;
    tmpInfo->next = NULL ;
    rear->next = tmpInfo ;
    rear = tmpInfo ;
    printResult(type,totalData,sucInsTimes,sucSeaTimes,x.getInsTimes(),x.getSeaTimes(),rear->times) ;
}
void printResult(string type,int totalData,int sucInsert,int sucSearch,int insertTimes,int searchTimes,double time)
{
    cout <<"\n\t\t" <<type <<"信息"<<endl ;
    cout <<"插入总数据量为 "<<totalData <<"\n成功插入的数据量为"<<sucInsert <<",其余 "<<totalData-sucInsert<<" 个数据为重复数据\n" ;
    cout <<"查找总数据量为 "<<totalData <<"\n成功查找的数据量为 "<<sucSearch <<"，总数据中至少有 "<<totalData/2<<" 个数据肯定存在\n" ;
    cout <<"总的插入次数为 "<<insertTimes <<" ,"<<"与总插入数据量比为 " <<(double)insertTimes/totalData <<endl ;
    cout <<"总的查找次数为 "<<searchTimes <<" ,"<<"与总查找数据量比为 " <<(double)searchTimes/totalData <<endl ;
    cout <<"插入与查找耗时为 "<<time <<"s" <<endl ;
}
void printTotalInfo(Info * head)
{
    Info * pos = head->next ;
    delete head ;
    cout <<"\n\t\t\t\t测试信息汇总\n\n\n\t类型\t\t\t\t耗时(s)\t插入次数/输入量\t查找次数/输入量\t\n" ;
    while(pos != NULL)
    {

        cout  <<left <<setw(35)<<pos->type <<"\t" <<pos->times <<"\t\t" <<pos->insertRate <<"\t\t" <<pos->searchRate<<endl ;
        Info * tmp = pos ;
        pos = pos->next ;
        delete tmp ;
    }
}
