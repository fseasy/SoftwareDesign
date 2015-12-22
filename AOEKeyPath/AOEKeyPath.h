#ifndef AOEKEYPATH_H_INCLUDED
#define AOEKEYPATH_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000

using namespace std ;

class AOE
{
public :
    AOE() ;
    AOE(fstream & in) ;
    void getKeyPath() ;
    void printKeyPath() ;
private :
    bool Forward() ;
    bool Backward() ;
    int vertexNum ;
    string * vertex ;
    int ** act ;
    int * indegree ;
    int * outdegree ;
    int nodeCount ;
    int * VE ;
    int * VL ;
} ;
AOE::AOE()
{
    cout <<"�������¼������㣩������\n" ;
    cin >> vertexNum ;
    vertex = new string[vertexNum] ;
    act = new int*[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        act[i] = new int[vertexNum] ;
    }
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j< vertexNum ; j++)
        {
            act[i][j] = DISCONNECTED ;
        }
    }
    VE = new int[vertexNum] ;
    VL = new int[vertexNum] ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        VE[i] = 0 ;
    }
    cout <<"����������ÿ���¼������ƣ�����س����ָ\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"������� "<<i+1 <<" ���¼������ƣ�\n" ;
        cin >> vertex[i] ;
    }
    cout <<"�¼�¼�����\n" ;
    cout <<"����������ÿ���¼�����֮ǰ��Ҫ���е��¼����,�� 0 �Ž���\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {

        cout <<"�¼����:\t" ;
        for(int ii = 0 ; ii < vertexNum ; ii++)
        {
            cout <<ii+1 <<"\t" ;
        }
        cout <<"\n�¼�����:\t" ;
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            cout <<vertex[ii] <<"\t" ;
        }
        cout <<endl ;
        cout <<"�������¼� " <<vertex[i]<<" ����֮ǰ��Ҫ���е��¼��ı���Լ���Ӧ�������ʱ��,�� 2 3���� 0 0 ��������\n" ;

        int ID ,time;
        while(cin >> ID >> time)
        {
            if(ID == 0 && time == 0)
                break ;
            ID-- ;
            if(ID >vertexNum -1 || ID < 0 || time < 0)
            {
                cout <<"INVALID INDEGREE\n" ;
                continue ;
            }
            act[ID][i] = time ;
        }
    }
    cout <<"AOEͼ�������\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[j][i] !=  DISCONNECTED )
            {
                count++ ;
            }
        }
        indegree[i] = count ;
    }
    outdegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[i][j] != DISCONNECTED)
            {
                count++ ;
            }
        }
        outdegree[i] = count ;
    }
}
AOE::AOE(fstream & in)
{
    in >> vertexNum ;
    vertex = new string[vertexNum] ;
    act = new int*[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        act[i] = new int[vertexNum] ;
    }
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j< vertexNum ; j++)
        {
            act[i][j] = DISCONNECTED ;
        }
    }
    VE = new int[vertexNum] ;
    VL = new int[vertexNum] ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        VE[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i] ;
    }
    cout <<"�¼�¼�����\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int ID ,time;
        while(in >> ID >> time)
        {
            if(ID == 0 && time == 0)
                break ;
            ID-- ;
            if(ID >vertexNum -1 || ID < 0 || time < 0)
            {
                cout <<"INVALID INDEGREE\n" ;
                continue ;
            }
            act[ID][i] = time ;
        }
    }
    cout <<"AOEͼ�������\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[j][i] !=  DISCONNECTED )
            {
                count++ ;
            }
        }
        indegree[i] = count ;
    }
    outdegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[i][j] != DISCONNECTED)
            {
                count++ ;
            }
        }
        outdegree[i] = count ;
    }
}
bool AOE::Forward()
{
    Queue<int> Q ;
    Q.makeNull() ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        if(indegree[i] == 0)
        {
            Q.EnQueue(i) ;
        }
    }
    nodeCount = 0 ;
    while(!Q.isEmpty())
    {
        int k = Q.Front() ;
        Q.DeQueue() ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            if(act[i][k] != DISCONNECTED && VE[k] < VE[i] +act[i][k]) //VE��ȡ���ں�ʱ��Ļ
            {
                VE[k] = VE[i]+act[i][k] ;
            }
        }
        nodeCount++ ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            if(act[k][i] != DISCONNECTED)
            {
                indegree[i]-- ;
                if(indegree[i] == 0)
                {
                    Q.EnQueue(i) ;
                }
            }
        }

    }
    if(nodeCount < vertexNum -1)
    {
        cout <<"����ͼ�д��ڻ�·,��Ч��AOE��" ;
        return false ;
    }
    return true ;
}
bool AOE::Backward()
{
    int max = 0 ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        if(VE[i] > max)
        {
            max = VE[i] ; //���VE[n]
        }
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        VL[i] = max ; //��ʼ��VL
    }
    Queue<int> Q ;
    Q.makeNull() ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        if(outdegree[i] == 0)
            Q.EnQueue(i) ;
    }
    nodeCount = 0 ;
    while(!Q.isEmpty())
    {
        int k = Q.Front() ;
        Q.DeQueue() ;
        for(int i = 0 ; i< vertexNum ; i++)
        {
            if(act[k][i] != DISCONNECTED && VL[k] > VL[i] - act[k][i])//VLȡ������Ļ
            {
                VL[k] = VL[i] - act[k][i] ;
            }
        }
        nodeCount++ ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            if(act[i][k] != DISCONNECTED)
            {
                outdegree[i] -- ;
                if(outdegree[i] == 0)
                {
                    Q.EnQueue(i) ;
                }

            }

        }

    }
    if(nodeCount < vertexNum)
    {
        cout <<"����ͼ�л�·��AOEͼ��Ч\n" ;
        return false ;
    }
    return true ;
}
void AOE::getKeyPath()
{
    if(Forward() == false || Backward() == false)
    {
        cout <<"�ؼ�·����ȡʧ��" ;
        return  ;
    }
    int E, L ;
    cout << "�\t\tE\tL\tL-E\t�Ƿ��ǹؼ��\n" ;
    for(int i = 0 ; i < vertexNum ; i ++)
    {
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[i][j] != DISCONNECTED)
            {
                E = VE[i] ;
                L = VL[j] - act[i][j] ;
                act[i][j] =L - E ; //����act��
                cout <<vertex[i]<<"��"<< vertex[j] <<"\t\t" <<E << "\t" <<L <<"\t " <<act[i][j] <<"\t" ;
                if(act[i][j] == 0)
                {
                    cout <<"\t��\n" ;
                }
                else
                {
                    cout <<"\t��\n" ;
                }
            }
        }
    }
}
#endif // AOEKEYPATH_H_INCLUDED
