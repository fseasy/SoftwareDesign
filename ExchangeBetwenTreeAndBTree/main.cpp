#include <iostream>
#include <stdlib.h>
#include <string>
#include "../lib_x/Tree.h"
/**
    **�������ƣ��ڽӱ����ڶ����������Ľ������໥ת����ɭ��
    **���ݽṹ�����������ڽӱ��ͺͶ��������ͣ�
*/
using namespace std;

int main()
{
    Tree<char>* x = NULL ;
    string menus = "\t�ڽӱ����ڶ����������Ľ������໥ת����ɭ��\n" ;
    menus+="1.�����ڽӱ���\n2.��������������\n3.�����ϲ�Ϊɭ��\n4.�˳�\n" ;
    char choice ;
    while(cout << menus)
    {
        cin >> choice ;
        switch(choice)
        {
        case '1' :
        {
            x = new Tree<char>() ;
            x->CreateListTree() ;
            cout <<"�ڽӱ��������ɹ�\n" ;
            string menusSec = "\n1.�鿴�ڽӱ���\n2.���ڽӱ���ת��Ϊ������������\n" ;
            menusSec+="3.�鿴ת���Ķ���������\n4.�������˵�\n" ;
            char choiceSec = '0' ;
            while(choiceSec != '4' && cout << menusSec)
            {
                cin >> choiceSec ;
                switch(choiceSec)
                {
                case '1':
                {
                    x->listOrder() ;
                    break ;
                }
                case '2':
                {
                    x->listToTree() ;
                    cout <<"\nת�����\n" ;
                    break ;
                }
                case '3' :
                {
                    cout <<"\n����������Ϊ\n\n" ;
                    x->TreePreOrder() ;
                    break ;
                }
                case '4' :
                {
                    system("cls") ;
                    break ;
                }
                default :
                    cout <<"INVALID CHOICE\n" ;
                }
            }
            delete x ;
            break ;
        }
        case '2' :
        {
            x = new Tree<char>() ;
            x->CreateTree() ;
            cout <<"���������������ɹ�\n" ;
            string menusSec = "1.����鿴����������\n2.������������ת��Ϊ�ڽӱ�����\n" ;
            menusSec+="3.�鿴ת�����ڽӱ���\n4.�������˵�\n" ;
            char choiceSec = '0' ;
            while(choiceSec != '4' && cout <<menusSec  )
            {
                cin >> choiceSec ;
                switch(choiceSec)
                {
                case '1' :
                {
                    cout <<"��������Ľ��Ϊ\n\n" ;
                    x->TreePreOrder() ;
                    break ;
                }
                case '2' :
                {
                    x->treeToList() ;
                    cout <<"ת�����\n" ;
                    break ;
                }
                case '3' :
                {
                    x->listOrder() ;
                    break ;
                }
                case '4' :
                    system("cls") ;
                    break ;
                default :
                    cout <<"INVALID CHOICE\n" ;
                }
            }
        }
        case '3' :
        {
            int num ;
            cout <<"��������������\n" ;
            cin >> num ;
            if(num < 1)
            {
                cout <<"INVALID INPUTS\n" ;
                break ;
            }
            Tree<char>* trees[num] ;
            for(int i = 1 ; i<= num ; i++)
            {
                cout <<"\n������"<<i<<"����\n\n" ;
                trees[i-1] = new Tree<char>() ;
                trees[i-1]->CreateTree() ;
                cout <<"��"<<i<<"�����������\n" ;
            }
            cout <<"\n��ʼ�ϲ�Ϊɭ��\n\n" ;
            for(int i = 2 ; i<= num ; i++)
            {
                trees[0]->Unoin(trees[i-1]) ;
                cout <<"�ϲ���һ�ú�"<<i<<"����...\n" ;
            }
            cout <<"�ϲ����\n�ϲ���ɭ�ֵ���������Ϊ\n\n" ;
            trees[0]->TreePreOrder() ;
        }
        case '4' :
            return 0 ;
        default :
            cout <<"INVALID CHOICE\n" ;
        }
    }

    return 0;
}
