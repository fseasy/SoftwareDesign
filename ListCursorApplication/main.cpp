#include <iostream>
#include <fstream>
#include "../lib_x/List_cursor.h"
using namespace std;
/**
    **�������ƣ���̬�ڴ����ģ��
    **���ݽṹ����̬����
    **��Ҫ���������룬ɾ������ȡ����ȡλ��
*/
int main()
{
    ListCursor<int> ls ;
    cout <<"�����һ��Ԫ��\n" ;
    ls.Insert(1,ls.end()) ;
    cout <<"��һ��Ԫ����"<<ls.Retrieve(ls.first()) << endl ;
    cout <<"����ڶ���Ԫ��\n" ;
    ls.Insert(2,ls.end()) ;
    cout <<"�ڶ���Ԫ����"<<ls.Retrieve(ls.next(ls.first())) <<endl ;
    cout <<"ɾ����һ��Ԫ��\n" ;
    ls.Delete(ls.first()) ;
    cout <<"ɾ����һ��Ԫ�غ�\n���ڵ�һ��Ԫ����"<<ls.Retrieve(ls.first()) << endl ;
    cout <<"\n�����������ģ��\n" ;
    getchar() ;
    return 0;
}