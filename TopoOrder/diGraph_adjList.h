#ifndef DIGRAPH_ADJLIST_H_INCLUDED
#define DIGRAPH_ADJLIST_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000
using namespace std ;
//构建邻接表的有向图,用于课程的拓扑排序
struct EdgeNode
{
    int adjvex ;
    EdgeNode * next ;
} ;
struct VertexNode
{
    string data ;
    EdgeNode * next ;
} ;
class DiGraph
{
public :
    DiGraph() ;
    DiGraph(fstream & in) ;
    void TopoOrder() ;
private :
    int vertexNum ;
    VertexNode * vertex ;
    int * indegree ;
    int nodeCount ;
} ;
DiGraph::DiGraph()
{
    cout <<"请输入课程的总数\n" ;
    cin >> vertexNum ;
    vertex = new VertexNode[vertexNum] ;
    cout <<"请依次输入每门课程的名称，键入回车来分割：\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"请输入第 "<<i+1 <<" 门课程的名称：\n" ;
        cin >> vertex[i].data ;
        vertex[i].next = NULL ;
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
            cout <<vertex[ii].data <<"\t" ;
        }
        cout <<endl ;
        cout <<"请输入课程 " <<vertex[i].data<<" 的先修课程编号,以 0 结束\n" ;

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
            EdgeNode * tmp = new EdgeNode ;
            tmp->adjvex = i ;
            tmp->next = vertex[ID].next ;
            vertex[ID].next = tmp ;
        }
    }
    cout <<"课程图建立完成\n" ;
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
}
DiGraph::DiGraph(fstream & in)
{
    cout <<"从文件中读入数据\n" ;
    in >> vertexNum ;
    vertex = new VertexNode[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i].data ;
        vertex[i].next = NULL ;
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
            EdgeNode * tmp = new EdgeNode ;
            tmp->adjvex = i ;
            tmp->next = vertex[ID].next ;
            vertex[ID].next = tmp ;
        }
    }
    cout <<"课程图建立完成\n" ;
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
        cout <<vertex[k].data <<"\t" ;
        nodeCount++ ;
        EdgeNode * pos = vertex[k].next ;
        while(pos != NULL )
        {
            indegree[pos->adjvex]-- ;
            if(indegree[pos->adjvex] == 0)
            {
                Q.EnQueue(pos->adjvex) ;
            }
             pos = pos->next ;
        }
    }
    if(nodeCount < vertexNum)
    {
        cout <<"\n有向图中存在回路\n" ;
    }
}


#endif // DIGRAPH_ADJLIST_H_INCLUDED
