#include <iostream>
#include "../lib_x/QUEUE_list.h"
using namespace std;
/**
    **程序名称：排号机
    **数据结构：队列
    **说明：由于没有多线程技术，所以需要手动结束业务
*/
int main()
{
    cout << "\t\t自助排号机\n" << endl;
    Queue<int> ANM ;
    int counter = 0 ;//总的客户数
    char * menus = "\n1.办理业务\t2.结束业务\n3.退出程序\n" ;
    while(cout <<menus)
    {
        cout  <<"------------排号信息--------------\n" ;
        if(ANM.isEmpty())
        {
            cout <<"当前无人排队\n" ;
        }
        else
        {

            cout   <<"您之前有"<<ANM.getCounter() <<"个人排队\n"
                   <<"当前客户"<<ANM.Front() <<"正在办理业务\n" ;

        }
        cout <<"----------------------------------\n" ;
        cout <<"请选择选项\n" ;
        int choice ;
        cin >> choice ;
        switch(choice)
        {
        case 1 :
        {
            ANM.EnQueue(++counter) ;
            cout <<"客户"<<counter <<"进入排队\n" ;
            break ;
        }
        case 2 :
        {
            int tmp = ANM.Front() ;
            ANM.DeQueue() ;
            cout <<"客户"<<tmp<<"已办理完业务\n" ;
            break ;
        }
        case 3 :
            return 0 ;
        default :
            cout <<"无效的选项\n" ;
        }
    }
    return 0;
}
