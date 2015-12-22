#ifndef DIGRAPH_ADJLIST_H_INCLUDED
#define DIGRAPH_ADJLIST_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000
using namespace std ;
//�����ڽӱ������ͼ,���ڿγ̵���������
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
    cout <<"������γ̵�����\n" ;
    cin >> vertexNum ;
    vertex = new VertexNode[vertexNum] ;
    cout <<"����������ÿ�ſγ̵����ƣ�����س����ָ\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"������� "<<i+1 <<" �ſγ̵����ƣ�\n" ;
        cin >> vertex[i].data ;
        vertex[i].next = NULL ;
    }
    cout <<"�γ�¼�����\n" ;
    cout <<"����������ÿ�ſγ̵����޿γ̱��,�� 0 �Ž���\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {

        cout <<"�γ̱��:\t" ;
        for(int ii = 0 ; ii < vertexNum ; ii++)
        {
            cout <<ii+1 <<"\t" ;
        }
        cout <<"\n�γ�����:\t" ;
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            cout <<vertex[ii].data <<"\t" ;
        }
        cout <<endl ;
        cout <<"������γ� " <<vertex[i].data<<" �����޿γ̱��,�� 0 ����\n" ;

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
    cout <<"�γ�ͼ�������\n" ;
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
    cout <<"���ļ��ж�������\n" ;
    in >> vertexNum ;
    vertex = new VertexNode[vertexNum] ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i].data ;
        vertex[i].next = NULL ;
    }
    cout <<"�γ�¼�����\n" ;
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
    cout <<"�γ�ͼ�������\n" ;
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
    cout <<"������������Ϊ��\n" ;
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
        cout <<"\n����ͼ�д��ڻ�·\n" ;
    }
}


#endif // DIGRAPH_ADJLIST_H_INCLUDED
