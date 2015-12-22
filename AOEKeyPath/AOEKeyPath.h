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
    cout <<"请输入事件（顶点）的总数\n" ;
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
    cout <<"请依次输入每个事件的名称，键入回车来分割：\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"请输入第 "<<i+1 <<" 个事件的名称：\n" ;
        cin >> vertex[i] ;
    }
    cout <<"事件录入完成\n" ;
    cout <<"请依次输入每个事件发生之前需要进行的事件编号,以 0 号结束\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {

        cout <<"事件编号:\t" ;
        for(int ii = 0 ; ii < vertexNum ; ii++)
        {
            cout <<ii+1 <<"\t" ;
        }
        cout <<"\n事件名称:\t" ;
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            cout <<vertex[ii] <<"\t" ;
        }
        cout <<endl ;
        cout <<"请输入事件 " <<vertex[i]<<" 发生之前需要进行的事件的编号以及对应活动的所需时间,如 2 3，以 0 0 结束输入\n" ;

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
    cout <<"AOE图建立完成\n" ;
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
    cout <<"事件录入完成\n" ;
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
    cout <<"AOE图建立完成\n" ;
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
            if(act[i][k] != DISCONNECTED && VE[k] < VE[i] +act[i][k]) //VE是取决于耗时最长的活动
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
        cout <<"有向图中存在回路,无效的AOE网" ;
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
            max = VE[i] ; //求出VE[n]
        }
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        VL[i] = max ; //初始化VL
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
            if(act[k][i] != DISCONNECTED && VL[k] > VL[i] - act[k][i])//VL取决于最长的活动
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
        cout <<"有向图有环路，AOE图无效\n" ;
        return false ;
    }
    return true ;
}
void AOE::getKeyPath()
{
    if(Forward() == false || Backward() == false)
    {
        cout <<"关键路径获取失败" ;
        return  ;
    }
    int E, L ;
    cout << "活动\t\tE\tL\tL-E\t是否是关键活动\n" ;
    for(int i = 0 ; i < vertexNum ; i ++)
    {
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(act[i][j] != DISCONNECTED)
            {
                E = VE[i] ;
                L = VL[j] - act[i][j] ;
                act[i][j] =L - E ; //存入act中
                cout <<vertex[i]<<"到"<< vertex[j] <<"\t\t" <<E << "\t" <<L <<"\t " <<act[i][j] <<"\t" ;
                if(act[i][j] == 0)
                {
                    cout <<"\t是\n" ;
                }
                else
                {
                    cout <<"\t否\n" ;
                }
            }
        }
    }
}
#endif // AOEKEYPATH_H_INCLUDED
