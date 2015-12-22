#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000
using namespace std ;
//构建邻接矩阵的有向图,用于课程的拓扑排序

class DiGraph
{
public :
    DiGraph() ;
    DiGraph(fstream & in) ;
    void TopoOrder() ;
private :
    int vertexNum ;
    string * vertex ;
    int ** edge ;
    int * indegree ;
    int nodeCount ;
} ;
DiGraph::DiGraph()
{
    cout <<"请输入课程的总数\n" ;
    cin >> vertexNum ;
    vertex = new string[vertexNum] ;
    edge = new int*[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        edge[i] = new int[vertexNum] ;
    }
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j< vertexNum ; j++)
        {
            edge[i][j] = DISCONNECTED ;
        }
    }
    cout <<"请依次输入每门课程的名称，键入回车来分割：\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"请输入第 "<<i+1 <<" 门课程的名称：\n" ;
        cin >> vertex[i] ;
    }
    cout <<"课程录入完成\n" ;
    cout <<"请依次输入每门课程的先修课程编号,以 0 号结束\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {

        cout <<"课程编号:\t" ;
        for(int ii = 0 ; ii < vertexNum ; ii++)
        {
            cout <<ii+1 <<"\t" ;
        }
        cout <<"\n课程名称:\t" ;
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            cout <<vertex[ii] <<"\t" ;
        }
        cout <<endl ;
        cout <<"请输入课程 " <<vertex[i]<<" 的先修课程编号,以 0 结束\n" ;

        int ID ;
        while(cin >> ID)
        {
            if(ID == 0)
                break ;
            ID-- ;
            if(ID >vertexNum -1 || ID < 0)
            {
                cout <<"INVALID INDEGREE\n" ;
                continue ;
            }
            edge[ID][i] = 1 ;
        }
    }
    cout <<"课程图建立完成\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(edge[j][i] == 1)
            {
                count++ ;
            }
        }
        indegree[i] = count ;
    }
}
DiGraph::DiGraph(fstream & in)
{
    cout <<"从文件中读入数据\n" ;
    in >> vertexNum ;
    vertex = new string[vertexNum] ;
    edge = new int*[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        edge[i] = new int[vertexNum] ;
    }
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j< vertexNum ; j++)
        {
            edge[i][j] = DISCONNECTED ;
        }
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i] ;
    }
    cout <<"课程录入完成\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int ID ;
        while(in >> ID)
        {
            if(ID == 0)
                break ;
            ID-- ;
            edge[ID][i] = 1 ;
        }
    }
    cout <<"课程图建立完成\n" ;
    indegree = new int[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        int count = 0 ;
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(edge[j][i] == 1)
            {
                count++ ;
            }
        }
        indegree[i] = count ;
    }
}
void DiGraph::TopoOrder()
{
    cout <<"拓扑排序序列为：\n" ;
    Queue<int> Q ;
    Q.makeNull() ;
    nodeCount = 0 ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        if(indegree[i] == 0)
        {
                Q.EnQueue(i) ;
        }
    }
    while(!Q.isEmpty())
    {
        int k = Q.Front() ;
        Q.DeQueue() ;
        cout <<vertex[k] <<"\t" ;
        nodeCount++ ;
        for(int i = 0 ; i< vertexNum ; i++)
        {
            if(edge[k][i] == 1)
            {
                indegree[i] -- ;
                if(indegree[i] == 0)
                {
                    Q.EnQueue(i) ;
                }
            }
        }
    }
    if(nodeCount < vertexNum)
    {
        cout <<"\n有向图中存在回路\n" ;
    }
}
#endif // DIGRAPH_H_INCLUDED
