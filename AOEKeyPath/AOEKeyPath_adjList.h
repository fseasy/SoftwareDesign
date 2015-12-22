#ifndef AOEKEYPATH_ADJLIST_H_INCLUDED
#define AOEKEYPATH_ADJLIST_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000

using namespace std ;
struct EdgeNode
{
    int adjvex ;
    int act ;
    EdgeNode * next ;
} ;
struct VertexNode
{
    string data ;
    EdgeNode * next ;
} ;
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
    VertexNode * vertex ;
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
    vertex = new VertexNode[vertexNum] ;
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
        cin >> vertex[i].data ;
        vertex[i].next = NULL ;
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
            cout <<vertex[ii].data <<"\t" ;
        }
        cout <<endl ;
        cout <<"请输入事件 " <<vertex[i].data<<" 发生之前需要进行的事件的编号以及对应活动的所需时间,如 2 3，以 0 0 结束输入\n" ;

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
            EdgeNode * tmp = new EdgeNode ;
            tmp->adjvex = i ;
            tmp->act = time ;
            tmp->next = vertex[ID].next ;
            vertex[ID].next = tmp ;
        }
    }
    cout <<"AOE图建立完成\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        indegree[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            indegree[pos->adjvex]++ ;
            pos = pos->next ;
        }
    }
    outdegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        outdegree[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            indegree[i]++ ;
            pos = pos->next ;
        }
    }
}
AOE::AOE(fstream & in)
{
    in >> vertexNum ;
    vertex = new VertexNode[vertexNum] ;
    VE = new int[vertexNum] ;
    VL = new int[vertexNum] ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        VE[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i].data ;
        vertex[i].next  = NULL ;
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

           EdgeNode * tmp  = new EdgeNode ;
           tmp->adjvex = i ;
           tmp->act = time ;
           tmp->next = vertex[ID].next ;
           vertex[ID].next = tmp ;
        }
    }
    cout <<"AOE图建立完成\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        indegree[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            indegree[pos->adjvex]++ ;
            pos = pos->next ;
        }
    }
    outdegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        outdegree[i] = 0 ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            outdegree[i]++ ;
            pos = pos->next ;
        }
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
            EdgeNode * pos = vertex[i].next ;
            while(pos != NULL)
            {
                if(pos->adjvex == k)
                {
                    if(VE[k] < VE[i] + pos->act)
                    {
                        VE[k] = VE[i]+pos->act ;
                    }
                    break ;//最多有一个
                }
                pos = pos->next ;
            }
        }
        nodeCount++ ;
        EdgeNode * pos = vertex[k].next ;
        while(pos != NULL)
        {
            indegree[pos->adjvex]-- ;
            if(indegree[pos->adjvex] == 0)
            {
                Q.EnQueue(pos->adjvex) ;
            }
            pos = pos->next ;
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
        EdgeNode * pos = vertex[k].next ;
        while(pos != NULL)
        {
            if(VL[k] > VL[pos->adjvex] - pos->act)
            {
                VL[k] = VL[pos->adjvex]- pos->act ;
            }
            pos = pos->next ;
        }
        nodeCount++ ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            EdgeNode * pos = vertex[i].next ;
            while(pos != NULL)
            {
                if(pos->adjvex == k)
                {
                    outdegree[i]-- ;
                    if(outdegree[i] == 0)
                    {
                        Q.EnQueue(i) ;
                    }
                }
                pos = pos->next ;
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
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            E = VE[i] ;
            L = VL[pos->adjvex] - pos->act ;
            pos->act = L -E ;
            cout << vertex[i].data <<"到" << vertex[pos->adjvex].data <<"\t\t" <<E <<"\t" <<L <<"\t" <<pos->act <<"\t" ;
            if(pos->act == 0)
            {
                cout <<"是" ;
            }
            else
            {
                cout <<"否" ;
            }
            cout <<endl ;
            pos = pos->next ;
        }

    }
}


#endif // AOEKEYPATH_ADJLIST_H_INCLUDED
