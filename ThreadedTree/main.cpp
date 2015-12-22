#include <iostream>
#include "..\lib_x\ThreadedTree.h"
/**
    **�������ƣ�������
    **���ݽṹ������ʵ�ֵ�������
*/
using namespace std;

int main()
{
    ThreadedTree<char> x ;
    char * menus = "\t��ѡ��\n\t1.����ڵ�\n\t2.�鿴�����������У�\n\t3.�˳�\n" ;
    while(cout <<menus)
    {
        int choice ;
        cin >> choice ;
        switch(choice)
        {
            case 1 :
            {
                char info ;
                if(x.isThreadedTreeEmpty() == true)
                {
                    cout <<"��Ϊ�ա�\n��������ڵ���Ϣ\n" ;
                    cin >> info ;
                    Node<char>* tmp = new Node<char>(info) ;
                    x.LInsert(tmp,x.getHead()) ;
                     cout <<"�½ڵ����ɹ�\n" ;
                }
                else
                {
                    cout <<"��ѡ���������Ǹ��ڵ�����\n" ;
                    x.ThInOrder() ;
                    char forSearch ;
                    cin >> forSearch ;
                    Node<char> * pos = x.Retrieve(forSearch) ;
                    if(pos == NULL)
                    {
                        cout <<"�����ڵĽڵ�\n" ;
                        break ;
                    }
                    else
                    {
                        cout <<"������Ҫ����ڵ����Ϣ\n" ;
                        char infoInput ;
                        cin >> infoInput ;
                        Node<char>* newNode = new Node<char>(infoInput) ;
                        cout <<"��ѡ�񽫸ýڵ���뵽"<<info<<"�ڵ������������������\n" ;
                        cout <<"1.������\t2.������\n" ;
                        int choiceWhere ;
                        cin >> choiceWhere ;
                        if(choiceWhere == 1)
                        {
                            x.LInsert(newNode,pos) ;
                        }
                        else if(choiceWhere == 2)
                        {
                            x.RInsert(newNode,pos) ;
                        }
                        else
                        {
                            cout <<"��Ч��ѡ��\n" ;
                            delete newNode ;
                            break ;
                        }
                        cout <<"�½ڵ����ɹ�\n" ;
                    }
                }
                break ;
            }
            case 2 :
            {
                cout <<"�����������Ϊ��\n" ;
                x.ThInOrder() ;
                break ;
            }
            case 3:
            return 0 ;
            default :
            cout <<"��Ч������\n" ;
        }
    }
    return 0;
}