#include <iostream>
#include "../lib_x/QUEUE_list.h"
using namespace std;
/**
    **�������ƣ��źŻ�
    **���ݽṹ������
    **˵��������û�ж��̼߳�����������Ҫ�ֶ�����ҵ��
*/
int main()
{
    cout << "\t\t�����źŻ�\n" << endl;
    Queue<int> ANM ;
    int counter = 0 ;//�ܵĿͻ���
    char * menus = "\n1.����ҵ��\t2.����ҵ��\n3.�˳�����\n" ;
    while(cout <<menus)
    {
        cout  <<"------------�ź���Ϣ--------------\n" ;
        if(ANM.isEmpty())
        {
            cout <<"��ǰ�����Ŷ�\n" ;
        }
        else
        {

            cout   <<"��֮ǰ��"<<ANM.getCounter() <<"�����Ŷ�\n"
                   <<"��ǰ�ͻ�"<<ANM.Front() <<"���ڰ���ҵ��\n" ;

        }
        cout <<"----------------------------------\n" ;
        cout <<"��ѡ��ѡ��\n" ;
        int choice ;
        cin >> choice ;
        switch(choice)
        {
        case 1 :
        {
            ANM.EnQueue(++counter) ;
            cout <<"�ͻ�"<<counter <<"�����Ŷ�\n" ;
            break ;
        }
        case 2 :
        {
            int tmp = ANM.Front() ;
            ANM.DeQueue() ;
            cout <<"�ͻ�"<<tmp<<"�Ѱ�����ҵ��\n" ;
            break ;
        }
        case 3 :
            return 0 ;
        default :
            cout <<"��Ч��ѡ��\n" ;
        }
    }
    return 0;
}
