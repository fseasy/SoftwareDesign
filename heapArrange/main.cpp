#include <iostream>
#include <string>
#include <fstream>
#include "../lib_x/Heap_max.h"
/**
    **�������ƣ���˳�򣨶�����
    **���ݽṹ����
    **���⣺c++ ���ļ���ȡ�����У�eof�жϻ��ӳ٣������ļ����һ���ظ���ȡ���Σ�

*/
using namespace std;

int main()
{
    ifstream source("info.txt") ;
    if(source == NULL)
    {
        cout <<"���ݶ���ʧ��\n" ;
        return 0 ;
    }
    MaxHeap<string> OrderInEating ;
    Element<string> tmp ;
    int key ;
    string tmpInfo ;
    cout <<"��ʳ�ô򷹵�˳����:\n\n" ;
    while(!source.eof())
    {
        source>> key >>tmpInfo ;
        tmp.setKey(key) ;
        tmp.setInfo(tmpInfo) ;
        cout <<tmpInfo <<"\t" ;
        OrderInEating.Insert(tmp) ;
    }
    cout <<"\n\n��˾�򷹵�˳���ǣ�\n\n" ;
    while(!OrderInEating.isHeapEmpty())
    {
        cout <<OrderInEating.DeleteMax()->getInfo() <<"\t" ;
    }
    return 0;
}