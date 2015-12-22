#include <iostream>
#include <fstream>
#include <windows.h>
#include "../lib_x/LIST_array.h"
#define CURRENT_RATE 'c'
#define FIXED_RATE 'f'
using namespace std;
/**
    **�������ƣ��������ʱ����
    **��Ҫ���ݽṹ�����Ա�����ʵ�֣�
    **ʵ�ֲ������鿴���ʣ��޸�,����,ɾ�����ʣ�������Ϣ
    **����ʼ�����bankRate.txt���ļ���֧�ֽ��޸ĺ������
      �ٴ�д����ļ�
*/
class Rate
{
public:
    Rate(float input_year,float input_rate)
    {
        year = input_year ;
        rate = input_rate ;
    }
    float getRate()
    {
        return rate ;
    }
    float getYear()
    {
        return year ;
    }
    void setRate(float input_rate)
    {
        rate = input_rate ;
    }
private :
    float year ;
    float rate ;

} ;
class BankRate
{
public:
    BankRate() ;
    ~BankRate() ;
    bool modifyRate(char deposit_type,float year,float new_rate) ;
    float getRate(char deposit_type,float year) ;
    bool insertRate(char deposit_type,float year,float rate) ;
    bool deleteRate(char deposit_type,float year) ;
    void printRate() ;
    void printRate(char deposit_type,float * rate_list) ;
private:
    List<Rate*> * current_deposit ;
    List<Rate*> * fixed_deposit ;
} ;
BankRate::BankRate()
{
    current_deposit = new List<Rate*>(2) ;
    fixed_deposit = new List<Rate*>() ;
}
BankRate::~BankRate()
{
    delete [] current_deposit ;
    delete [] fixed_deposit ;
    current_deposit = NULL ;
    fixed_deposit = NULL ;
}
bool BankRate::modifyRate(char deposit_type,float year ,float new_rate)
{
    int pos ;
    Rate * tmp ;
    if(deposit_type == CURRENT_RATE)
    {
        pos = current_deposit->first() ;
        if(pos == INVALID)
            return false ;
        else
        {
            tmp = current_deposit->Retrieve(pos) ;
            tmp->setRate(new_rate) ;
            return true ;
        }
    }
    else
    {
        pos = fixed_deposit->first() ;
        while(pos != INVALID)
        {
            tmp=fixed_deposit->Retrieve(pos) ;
            if( tmp->getYear()== year)
            {
                tmp->setRate(new_rate) ;
                return true ;
            }
            else
            {
                pos = fixed_deposit->next(pos) ;
            }
        }
        return false ;
    }
}
float BankRate::getRate(char deposit_type,float year)
{
    Rate * tmp = NULL ;
    if(deposit_type == CURRENT_RATE)
    {
        if(current_deposit->first() == INVALID)
            return (float)INVALID ;
        tmp = current_deposit->Retrieve(current_deposit->first()) ;
        return tmp->getRate() ;
    }
    else
    {
        int pos = fixed_deposit->first() ;
        while(pos!=INVALID)
        {
            tmp = fixed_deposit->Retrieve(pos) ;
            if(tmp->getYear() == year)\
            {
                return tmp->getRate() ;
            }
            else
            {
                pos = fixed_deposit->next(pos) ;
            }
        }
        return (float)INVALID ;
    }

}
bool BankRate::insertRate(char deposit_type,float year , float rate) //��ʱ���ɶ̵�������
{
    int pos ;
    Rate * tmp = NULL ;
    if(deposit_type == CURRENT_RATE)
    {
        pos = current_deposit->first() ;
        if(pos == INVALID)
        {
            tmp = new Rate(year,rate) ;
            current_deposit->Insert(tmp,1) ;
            return true ;
        }
        else
            return false ;
    }
    else
    {
        pos = fixed_deposit->first() ;

        if(pos == INVALID)
        {
            tmp = new Rate(year,rate) ;
            fixed_deposit->Insert(tmp,1) ;
            return true ;
        }
        while(pos!= INVALID)
        {
            tmp = fixed_deposit->Retrieve(pos) ;
            if(year == tmp->getYear())
            {
                return false ;
            }
            else if(year <tmp->getYear())
            {
                tmp = new Rate(year,rate) ;
                fixed_deposit->Insert(tmp,pos) ;
                return true ;
            }
            else
            {
                pos = fixed_deposit->next(pos) ;
            }
        }
        tmp = new Rate(year,rate) ;
        fixed_deposit->Insert(tmp,fixed_deposit->end()+1) ;
        return true ;

    }

}
bool BankRate::deleteRate(char deposit_type,float year)
{
    if(deposit_type == CURRENT_RATE)
    {
        if(current_deposit->Delete(current_deposit->first()))
            return true ;
        else
            return false ;
    }
    else
    {
        int pos = fixed_deposit->first() ;
        Rate * tmp ;
        while(pos != INVALID)
        {
            tmp = fixed_deposit->Retrieve(pos) ;
            if(tmp->getYear() == year)
            {
                fixed_deposit->Delete(pos) ;
                return true ;
            }
            else
            {
                pos = fixed_deposit->next(pos) ;
            }
        }
        return false ;
    }
}
void BankRate::printRate()
{
    int pos ;
    pos = current_deposit->first() ;
    if(pos == INVALID)
        cout <<"���ڴ���������������\n\n" ;
    else
        cout <<"���ڴ��������Ϊ \n\t\t\t" <<(current_deposit->Retrieve(pos))->getRate() <<"%/��\n\n";
    pos = fixed_deposit->first() ;
    if(pos == INVALID)
        cout <<"���ڴ�����������\n\n" ;
    else
    {
        cout <<"���ڴ�������Ϊ��\n\n\t���ڣ��꣩\t���ʣ�%/�꣩\n" ;
        Rate * tmp = NULL ;
        while(pos!= INVALID)
        {
            tmp = fixed_deposit->Retrieve(pos) ;
            cout <<"\t" <<tmp->getYear()<<"\t\t"<<tmp->getRate()<<endl ;
            pos = fixed_deposit->next(pos) ;
        }
    }
}
void BankRate::printRate(char deposit_type,float * rate_list)
{
    int pos ;
    if(deposit_type == CURRENT_RATE)
    {
        pos = current_deposit->first() ;
        if(pos == INVALID)
        {
            rate_list[0] = -1.0 ;
            return ;
        }
        else
        rate_list[0] = (current_deposit->Retrieve(pos))->getRate() ;
    }
    else
    {
        pos = fixed_deposit->first() ;
        while(pos!= INVALID)
        {
            rate_list[2*(pos-1)] = (fixed_deposit->Retrieve(pos))->getYear() ;
            rate_list[2*(pos-1)+1] = (fixed_deposit->Retrieve(pos))->getRate() ;
            pos = fixed_deposit->next(pos) ;
        }
    }
}
int main()
{

    BankRate bank_rate ;
    char * menus="\t\t�������ʱ����\n1.�鿴����\n2.�޸�����\n3.����µ����ʹ���\n4.ɾ�����ʹ���\n5.������Ϣ\n6�������ʵ��ļ�\n7.�˳�\n" ;
    ifstream res("bankRate.txt") ;
    if(res == NULL)
    {
        cout <<"��ȡ�����ļ�ʧ�ܡ�\n��������˳�" ;
        getchar() ;
        return 0 ;
    }
    float year,rate ;
    year = 0.0 ;
    rate = 0.0 ;
    //������ڴ������
    res>>rate ;
    bank_rate.insertRate(CURRENT_RATE,year,rate) ;
    while(!res.eof())
    {
        res >> year >> rate ;
        bank_rate.insertRate(FIXED_RATE,year,rate) ;
    }
    while (cout <<menus)
    {
        int choice ;
        cin >> choice ;
        switch(choice)
        {
        case 1 :
        {
            bank_rate.printRate() ;
            break ;
        }
        case 2 :
        {
            cout <<"��ǰ��˰��Ϊ��\n" ;
            bank_rate.printRate() ;
            cout <<"������Ҫ�޸ĵ��������ͣ�\n1.����2.����\n" ;
            int choice_type ;
            cin >> choice_type ;

            if(choice_type == 1)
            {
                cout <<"�������µĻ�������\n" ;
                cin >> rate ;
                if(bank_rate.modifyRate(CURRENT_RATE,year,rate))
                {
                    cout <<"�����޸ĳɹ�\n��ǰ������Ϊ:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"�޸�ʧ��\n\n" ;
                }

            }
            else if(choice_type == 2)
            {
                cout <<"�����붨��ʱ�估�µ����ʣ��� 3 0.35\n" ;
                cin >> year >> rate ;
                if(bank_rate.modifyRate(FIXED_RATE,year,rate))
                {
                    cout <<"�����޸ĳɹ�\n��ǰ������Ϊ:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"�޸�ʧ�ܣ������ڵ�ʱ��" << endl ;
                }

            }
            else
            {
                cout <<"��Ч������\n\n" ;
            }
            break ;
        }
        case 3 :
        {
            int choice_type ;
            cout <<"������Ҫ������ʵ����ͣ�\n1.����2.����\n" ;
            cin >> choice_type ;
            if(choice_type == 1)
            {
                cout <<"�������������\n" ;
                cin >> rate ;
                if(bank_rate.insertRate(CURRENT_RATE,year,rate))
                {
                    cout <<"������ʳɹ�����ǰ������Ϊ\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"���ʧ�ܣ����������Ѵ���\n" ;
                }

            }
            else if(choice_type == 2)
            {
                cout <<"�������µ����ʹ��� ʱ�� �� ���� �� 10 0.55\n" ;
                cin >> year >> rate ;
                if(bank_rate.insertRate(FIXED_RATE,year,rate))
                {
                    cout <<"������ʳɹ�����ǰ������Ϊ\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"�������ʧ�ܣ���ǰ���ʹ����Ѵ���\n" ;
                }

            }
            else
            {
                cout <<"��Ч������\n" ;
            }
            break ;
        }
        case 4 :
        {
            int choice_type ;
            cout <<"������Ҫɾ�����ʵ����ͣ�\n1.����2.����\n" ;
            cin >> choice_type ;
            if(choice_type == 1)
            {
                if(bank_rate.deleteRate(CURRENT_RATE,year))
                {
                    cout <<"ɾ���ɹ�����ǰ������Ϊ:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"ɾ��ʧ��,�������ʲ�����\n" ;
                }
            }
            else if(choice_type == 2)
            {
                cout <<"����Ҫɾ�������ʹ����Ӧ��ʱ��\n" ;
                cin >> year ;
                if(bank_rate.deleteRate(FIXED_RATE,year))
                {
                    cout <<"ɾ���ɹ�����ǰ������Ϊ:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"ɾ��ʧ�ܣ������ڵĹ���\n" ;
                }
            }
            else
            {
                cout <<"���Ϸ�������\n" ;
            }
            break ;
        }
        case 5 :
        {
            int choice_type ;
            cout <<"������������\n1.����\n2.����\n" ;
            cin >> choice_type ;
            cout <<"��������Ľ�Ԫ����ʱ�䣨�꣩����10000 2.5\n" ;
            float interest ;
            float principal ;
            cin >> principal >> year ;
            if(choice_type == 1)
            {
                rate = bank_rate.getRate(CURRENT_RATE,year) ;
                if(rate == (float)INVALID)
                {
                    cout <<"���ʶ�ȡʧ��\n" ;
                }
                else
                {
                    rate/=100 ;
                    rate/=4 ;
                    int seasons = year*4 ;
                    interest = principal*rate*seasons ;
                    cout <<"������Ϣ���㹫ʽΪ ��Ϣ=����*����*����\n"
                         <<"�һ�����Ϣ�������㡣\n"
                         <<year <<"�����������" <<seasons <<"��,����ϢΪ\n"
                         <<"��Ϣ="<<principal<<"*"<<rate <<"*" <<seasons<<"="<<principal*rate<<seasons <<" (Ԫ)"<<endl ;
                }
            }
            else if(choice_type == 2)
            {
                rate = bank_rate.getRate(FIXED_RATE,year) ;
                if(rate == (float)INVALID)
                {
                    cout <<"�޴�ʱ�������\n" ;
                }
                else
                {
                    cout <<"������Ϣ�ļ��㹫ʽΪ\n��Ϣ=����*����*����\n"
                         <<"����Ϣ="<<principal<<"*"<<rate<<"*"<<year
                         <<"="<<principal*rate*year <<" (Ԫ)\n" ;
                }
            }
            else
            {
                cout <<"��Ч������\n" ;
            }
            break ;
        }
        case 6 :
        {
            ofstream out("bankRate.txt") ;
            if(out == NULL)
            {
                cout <<"�����ļ�����ʧ��\n" ;
                break ;
            }
            float rate_list[2*MAX] ;
            for(int i =0 ; i < 2*MAX ; i++)
            {
                rate_list[i] = -1.0 ;
            }
            bank_rate.printRate(CURRENT_RATE,rate_list) ;
            if(rate_list[0] == -1.0)
            {
                cout <<"�������ݲ�����������ʧ��\n" ;
                break ;
            }
            out <<rate_list[0] <<endl ;
            bank_rate.printRate(FIXED_RATE,rate_list) ;
            if(rate_list[0] == -1.0)
            {
                cout <<"�������ݲ�����������ʧ��\n" ;
                break ;
            }
            int counter = 0 ;
            while(rate_list[counter] != -1.0)
            {
                out <<rate_list[counter++] <<" " ;
                out   <<rate_list[counter++] <<" " ;
                /*
                ������дΪ
                out <<rate_list[counter++] <<" " ;
                    <<rate_list[counter++] <<" " ;
                ��ô���˳����෴
                ���� ԭ��Ϊ0.5 3.3
                ��δ������Ϊ3.3 0.5
                ��֮ǰȫ���ı������ʱ����û���������
                ԭ����
                */
            }
            out.close() ;
            cout <<"����ɹ�\n" ;
            break ;

        }
        case 7 :
            return 0 ;
        default :
            cout <<"��Ч������\n" ;
        }

    cout <<endl ;
    Sleep(1200) ;//��ʱ
    }

    return 0;
}
