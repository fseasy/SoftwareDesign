#include <iostream>
#include <fstream>
#include <windows.h>
#include "../lib_x/LIST_array.h"
#define CURRENT_RATE 'c'
#define FIXED_RATE 'f'
using namespace std;
/**
    **程序名称：银行利率表管理
    **主要数据结构：线性表（数组实现）
    **实现操作：查看利率，修改,增加,删除利率，计算利息
    **程序开始会读入bankRate.txt的文件，支持将修改后的利率
      再次写入该文件
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
bool BankRate::insertRate(char deposit_type,float year , float rate) //按时间由短到长插入
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
        cout <<"活期储蓄暂无利率数据\n\n" ;
    else
        cout <<"活期储蓄的利率为 \n\t\t\t" <<(current_deposit->Retrieve(pos))->getRate() <<"%/年\n\n";
    pos = fixed_deposit->first() ;
    if(pos == INVALID)
        cout <<"定期储蓄暂无数据\n\n" ;
    else
    {
        cout <<"定期储蓄利率为：\n\n\t存期（年）\t利率（%/年）\n" ;
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
    char * menus="\t\t银行利率表管理\n1.查看利率\n2.修改利率\n3.添加新的利率规则\n4.删除利率规则\n5.计算利息\n6保存利率到文件\n7.退出\n" ;
    ifstream res("bankRate.txt") ;
    if(res == NULL)
    {
        cout <<"读取数据文件失败。\n按任意键退出" ;
        getchar() ;
        return 0 ;
    }
    float year,rate ;
    year = 0.0 ;
    rate = 0.0 ;
    //读入活期储蓄；利率
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
            cout <<"当前的税率为：\n" ;
            bank_rate.printRate() ;
            cout <<"请输入要修改的利率类型：\n1.活期2.定期\n" ;
            int choice_type ;
            cin >> choice_type ;

            if(choice_type == 1)
            {
                cout <<"请输入新的活期利率\n" ;
                cin >> rate ;
                if(bank_rate.modifyRate(CURRENT_RATE,year,rate))
                {
                    cout <<"利率修改成功\n当前的利率为:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"修改失败\n\n" ;
                }

            }
            else if(choice_type == 2)
            {
                cout <<"请输入定期时间及新的利率，如 3 0.35\n" ;
                cin >> year >> rate ;
                if(bank_rate.modifyRate(FIXED_RATE,year,rate))
                {
                    cout <<"利率修改成功\n当前的利率为:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"修改失败，不存在的时间" << endl ;
                }

            }
            else
            {
                cout <<"无效的输入\n\n" ;
            }
            break ;
        }
        case 3 :
        {
            int choice_type ;
            cout <<"请输入要添加利率的类型：\n1.活期2.定期\n" ;
            cin >> choice_type ;
            if(choice_type == 1)
            {
                cout <<"请输入活期利率\n" ;
                cin >> rate ;
                if(bank_rate.insertRate(CURRENT_RATE,year,rate))
                {
                    cout <<"添加利率成功，当前的利率为\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"添加失败，活期利率已存在\n" ;
                }

            }
            else if(choice_type == 2)
            {
                cout <<"请输入新的利率规则 时间 及 利率 如 10 0.55\n" ;
                cin >> year >> rate ;
                if(bank_rate.insertRate(FIXED_RATE,year,rate))
                {
                    cout <<"添加利率成功，当前的利率为\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"添加利率失败，当前利率规则已存在\n" ;
                }

            }
            else
            {
                cout <<"无效的输入\n" ;
            }
            break ;
        }
        case 4 :
        {
            int choice_type ;
            cout <<"请输入要删除利率的类型：\n1.活期2.定期\n" ;
            cin >> choice_type ;
            if(choice_type == 1)
            {
                if(bank_rate.deleteRate(CURRENT_RATE,year))
                {
                    cout <<"删除成功，当前的利率为:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"删除失败,活期利率不存在\n" ;
                }
            }
            else if(choice_type == 2)
            {
                cout <<"输入要删除的利率规则对应的时间\n" ;
                cin >> year ;
                if(bank_rate.deleteRate(FIXED_RATE,year))
                {
                    cout <<"删除成功，当前的利率为:\n" ;
                    bank_rate.printRate() ;
                }
                else
                {
                    cout <<"删除失败，不存在的规则\n" ;
                }
            }
            else
            {
                cout <<"不合法的输入\n" ;
            }
            break ;
        }
        case 5 :
        {
            int choice_type ;
            cout <<"请输入存款类型\n1.活期\n2.定期\n" ;
            cin >> choice_type ;
            cout <<"请输入存款的金额（元）与时间（年），如10000 2.5\n" ;
            float interest ;
            float principal ;
            cin >> principal >> year ;
            if(choice_type == 1)
            {
                rate = bank_rate.getRate(CURRENT_RATE,year) ;
                if(rate == (float)INVALID)
                {
                    cout <<"利率读取失败\n" ;
                }
                else
                {
                    rate/=100 ;
                    rate/=4 ;
                    int seasons = year*4 ;
                    interest = principal*rate*seasons ;
                    cout <<"活期利息计算公式为 利息=本金*利率*期限\n"
                         <<"且活期利息按季结算。\n"
                         <<year <<"年包含完整的" <<seasons <<"季,则利息为\n"
                         <<"利息="<<principal<<"*"<<rate <<"*" <<seasons<<"="<<principal*rate<<seasons <<" (元)"<<endl ;
                }
            }
            else if(choice_type == 2)
            {
                rate = bank_rate.getRate(FIXED_RATE,year) ;
                if(rate == (float)INVALID)
                {
                    cout <<"无此时间的利率\n" ;
                }
                else
                {
                    cout <<"定期利息的计算公式为\n利息=本金*利率*期限\n"
                         <<"则利息="<<principal<<"*"<<rate<<"*"<<year
                         <<"="<<principal*rate*year <<" (元)\n" ;
                }
            }
            else
            {
                cout <<"无效的输入\n" ;
            }
            break ;
        }
        case 6 :
        {
            ofstream out("bankRate.txt") ;
            if(out == NULL)
            {
                cout <<"数据文件创建失败\n" ;
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
                cout <<"利率数据不完整，导出失败\n" ;
                break ;
            }
            out <<rate_list[0] <<endl ;
            bank_rate.printRate(FIXED_RATE,rate_list) ;
            if(rate_list[0] == -1.0)
            {
                cout <<"利率数据不完整，导出失败\n" ;
                break ;
            }
            int counter = 0 ;
            while(rate_list[counter] != -1.0)
            {
                out <<rate_list[counter++] <<" " ;
                out   <<rate_list[counter++] <<" " ;
                /*
                如果这段写为
                out <<rate_list[counter++] <<" " ;
                    <<rate_list[counter++] <<" " ;
                那么输出顺序会相反
                既是 原本为0.5 3.3
                这段代码输出为3.3 0.5
                但之前全是文本输出的时候则没有这种情况
                原因不详
                */
            }
            out.close() ;
            cout <<"保存成功\n" ;
            break ;

        }
        case 7 :
            return 0 ;
        default :
            cout <<"无效的输入\n" ;
        }

    cout <<endl ;
    Sleep(1200) ;//延时
    }

    return 0;
}
