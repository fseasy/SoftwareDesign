#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include "../lib_x/QUEUE.h"
#define DISCONNECTED -10000
using namespace std ;
//�����ڽӾ��������ͼ,���ڿγ̵���������

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
    cout <<"������γ̵�����\n" ;
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
    cout <<"����������ÿ�ſγ̵����ƣ�����س����ָ\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout <<"������� "<<i+1 <<" �ſγ̵����ƣ�\n" ;
        cin >> vertex[i] ;
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
            cout <<vertex[ii] <<"\t" ;
        }
        cout <<endl ;
        cout <<"������γ� " <<vertex[i]<<" �����޿γ̱��,�� 0 ����\n" ;

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
    cout <<"�γ�ͼ�������\n" ;
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
    cout <<"���ļ��ж�������\n" ;
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
    cout <<"�γ�¼�����\n" ;
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
    cout <<"�γ�ͼ�������\n" ;
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
        cout <<"\n����ͼ�д��ڻ�·\n" ;
    }
}
#endif // DIGRAPH_H_INCLUDED
