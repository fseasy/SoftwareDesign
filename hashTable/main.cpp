#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include "../lib_x/hashTable.h"
/**
    �������ƣ�ɢ�нṹ���ܲ��Գ���
    ʵ�ֹ��ܣ���ɢ�У���ɢ�У�����������ɢ�еĻ�׼���������0.5�����ݹ�ģС�������������
              ��������һ���ǲ������ݣ�һ����������ݣ�ɢ�к���Ϊ���෨�����ԣ���������Ӳ���
             ���������Ϊ 1�����ı�ɢ�к������ԣ����ȡ���������������ݹ�ģ��big�����ԣ��ı�
              �������ݷֲ���ȫ��Ϊ��������ݣ����ԡ�
    ���� �� ������ɢ�з�����������Ӻܴ�ʱ�����Գ���Ϊ1����������Ҵ����޴�Ч�ʵ�
            ������ɢ�з��������ݹ�ģ�ϴ�ʱ����ʱ�϶ࣨ����������Ƶ��ȡַ�������£�
            ���ô���������ɢ�з���ƽ��������ã���Ӧ�ý���ɢ�з��ڱ���ʱ���Ŀռ䣩
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
    int randomNum_small[small] ;//С��ģ�����������
    int randomNum_big[big] ;//���ģ�����������
    int searchArraySmall[small] ;//��ӦС��ģ�Ĳ���Դ���ݣ�һ�����Բ������ݣ�hash���п϶����ڣ���һ���ٴ��������
    int searchArrayBig[big] ;//��Ӧ���ģ��������Դ
    Info * head = new Info ;
    head->next = NULL ;
    Info * rear = head ;
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
    //��׼hash
    HashTable_inner x(small*2) ;
    test(x,small,randomNum_small,searchArraySmall,"��ɢ�з����� ��׼����",rear) ;
    //�ı��������
    HashTable_inner xFactorFull(small) ;
    test(xFactorFull,small,randomNum_small,searchArraySmall,"��ɢ�з������ı��������",rear) ;
    //�ı�ɢ�к���
    HashTable_inner xGETINTHASH(small*2,GETINTHASH) ;
    test(xGETINTHASH,small,randomNum_small,searchArraySmall,"��ɢ�з������ı�ɢ�к���",rear) ;
    //�ı����ݹ�ģ
    HashTable_inner xBig(big*2) ;
    test(xBig,big,randomNum_big,searchArrayBig,"��ɢ�з������ı����ݹ�ģ",rear) ;
    //�ı�������ݵķֲ�������ӵ�����ֱ�Ӳ��ң�
    HashTable_inner xDistribution(small*2) ;
    test(xDistribution,small,randomNum_small,randomNum_small,"��ɢ�з������ı����ݷֲ�",rear) ;
    //��ɢ��
    //��׼����
    HashTable_open x2(small*2) ;
    test(x2,small,randomNum_small,searchArraySmall,"��ɢ�з�������׼����",rear) ;
    //�ı��������
    HashTable_open x2FactorFull(small) ;
    test(x2FactorFull,small,randomNum_small,searchArraySmall,"��ɢ�з������ı��������",rear) ;
    //�ı�ɢ�к���
    HashTable_open x2GETINTHASH(small*2) ;
    test(x2GETINTHASH,small,randomNum_small,searchArraySmall,"��ɢ�з������ı�ɢ�к���",rear) ;
    //�ı����ݹ�ģ
    HashTable_open x2Big(big*2) ;
    test(x2Big,big,randomNum_big,searchArrayBig,"��ɢ�з������ı����ݹ�ģ",rear) ;
    //�ı�������ݷֲ�
    HashTable_open x2Distribution(small*2) ;
    test(x2Distribution,small,randomNum_small,searchArraySmall,"��ɢ�з����� �ı����ݷֲ�     ",rear) ;
    //����������ɢ��
    //��׼����
    HashTable_overflow x3(small*2) ;
    test(x3,small,randomNum_small,searchArraySmall,"����������ɢ�з�������׼����",rear) ;
    //�ı��������
    HashTable_overflow x3FactorFull(small) ;
    test(x3FactorFull,small,randomNum_small,searchArraySmall,"����������ɢ�з������ı��������",rear) ;
    //�ı�ɢ�к���
    HashTable_overflow x3GETINTHASH(small*2) ;
    test(x3GETINTHASH,small,randomNum_small,searchArraySmall,"�����������ɢ�з������ı�ɢ�к���",rear) ;
    //�ı����ݹ�ģ
    HashTable_overflow x3Big(big*2) ;
    test(x3Big,big,randomNum_big,searchArrayBig,"����������ɢ�з������ı����ݹ�ģ",rear) ;
    //�ı�������ݷֲ�
    HashTable_overflow x3Distribution(small*2) ;
    test(x3Distribution,small,randomNum_small,randomNum_small,"����������ɢ�з������ı����ݷֲ�",rear) ;
    //���������Ϣ
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
    cout <<"\n\t\t" <<type <<"��Ϣ"<<endl ;
    cout <<"������������Ϊ "<<totalData <<"\n�ɹ������������Ϊ"<<sucInsert <<",���� "<<totalData-sucInsert<<" ������Ϊ�ظ�����\n" ;
    cout <<"������������Ϊ "<<totalData <<"\n�ɹ����ҵ�������Ϊ "<<sucSearch <<"���������������� "<<totalData/2<<" �����ݿ϶�����\n" ;
    cout <<"�ܵĲ������Ϊ "<<insertTimes <<" ,"<<"���ܲ�����������Ϊ " <<(double)insertTimes/totalData <<endl ;
    cout <<"�ܵĲ��Ҵ���Ϊ "<<searchTimes <<" ,"<<"���ܲ�����������Ϊ " <<(double)searchTimes/totalData <<endl ;
    cout <<"��������Һ�ʱΪ "<<time <<"s" <<endl ;
}
void printTotalInfo(Info * head)
{
    Info * pos = head->next ;
    delete head ;
    cout <<"\n\t\t\t\t������Ϣ����\n\n\n\t����\t\t\t\t��ʱ(s)\t�������/������\t���Ҵ���/������\t\n" ;
    while(pos != NULL)
    {

        cout  <<left <<setw(35)<<pos->type <<"\t" <<pos->times <<"\t\t" <<pos->insertRate <<"\t\t" <<pos->searchRate<<endl ;
        Info * tmp = pos ;
        pos = pos->next ;
        delete tmp ;
    }
}
