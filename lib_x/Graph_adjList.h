#ifndef GRAPH_ADJLIST_H_INCLUDED
#define GRAPH_ADJLIST_H_INCLUDED
#define DISCONNECTED -1
#define INFINITY 100000
#include <iostream>
#include <fstream>
#include "STACK_array.h"
#include "QUEUE.h"
#include "MFSET.h"
using namespace std ;

//�����ڽӾ����͵�����ͼ
struct EdgeNode
{
    int adjvex ;
    int edge ;
    EdgeNode * next ;
} ;
struct VertexNode
{
    char data ;
    EdgeNode * next ;
} ;
class Graph
{

public :
    Graph() ;
    Graph(fstream &in) ;
    ~Graph() ;
    void DFSTraverse() ;
    void DFSX(int vertexOrder) ;
    void BFSTraverse() ;
    void BFSX(int vertexOrder) ;
    void printDFN() ;
    void printBFN() ;
    void Prim() ;
    void Kruskal() ;
    void Dijkstra(int sourcePoint) ;
    void Floyd() ;
    void FloydPath(int pointA,int pointB,int ** preVertex) ;
    int getVertexNum() ;
private  :
    int vertexNum ;
    int edgeNum ;
    VertexNode * vertex ;
    bool * isVisited ;
    int * dfn ;
    bool hasDFS ;
    int * bfn ;
    bool hasBFS ;
    int counter ;

} ;
Graph::Graph()
{
    cout <<"������ͼ�Ķ������ͱߵ�����\n" ;
    cin >> vertexNum >> edgeNum ;
    vertex = new VertexNode[vertexNum] ;
    isVisited =  new bool[vertexNum] ;
    dfn= new int[vertexNum] ;
    bfn = new int[vertexNum] ;
    hasDFS = false ;
    hasBFS = false ;
    counter = 0 ;
    cout <<"��������������������\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cin >> vertex[i].data ;
        vertex[i].next = NULL ;
    }
    cout <<"���������������\n" ;
    for(int i = 0 ; i < edgeNum ; i++)
    {
        cout <<"������:\t" ;
        for(int k = 0 ; k < vertexNum ; k++)
        {
            cout <<k+1 <<"\t" ;
        }
        cout <<"\n����ֵ: \t" ;
        for(int k = 0 ; k < vertexNum ; k++)
        {
            cout <<vertex[k].data <<"\t" ;
        }
        cout << endl ;
        cout <<"�������"<< i+1 <<"���ߵ������������,������Ȩֵ\n" ;
        int edgeA,edgeB,weight ;
        while(cin >> edgeA >> edgeB >> weight)
        {
            edgeA -- ;
            edgeB -- ;
            if(edgeA >=vertexNum || edgeB >= vertexNum)
            {
                cout <<"���Ϸ��Ķ�����ţ�����������\n" ;
            }
            else if(weight <0)
            {
                cout <<"���Ϸ���Ȩֵ��С��0��\n,����������ñ�ȫ����Ϣ\n" ;
            }
            else
            {
                EdgeNode * tmp = new EdgeNode ;
                tmp->adjvex = edgeB ;
                tmp->edge = weight ;
                tmp->next = vertex[edgeA].next ;
                vertex[edgeA].next = tmp ;
                tmp = new EdgeNode ;
                tmp->adjvex = edgeA ;
                tmp->edge = weight ;
                tmp->next = vertex[edgeB].next ;
                vertex[edgeB].next = tmp ;
                break ;
            }
        }
    }
    cout <<"����Ϣ�������\n" ;
    cout <<"����ͼ�������\n" ;
}
Graph::Graph(fstream &in)
{
    cout <<"��ʼ���ļ��ж�ȡ����\n" ;
    in >> vertexNum >> edgeNum ;
    vertex = new VertexNode[vertexNum] ;
    isVisited =  new bool[vertexNum] ;
    dfn= new int[vertexNum] ;
    bfn = new int[vertexNum] ;
    hasDFS = false ;
    hasBFS = false ;
    counter = 0 ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        in >> vertex[i].data ;
        vertex[i].next = NULL ;
    }
    int edgeA,edgeB,weight ;
    for(int i = 0 ; i < edgeNum ; i++)
    {
        in >> edgeA >> edgeB >> weight ;
        edgeA-- ;
        edgeB-- ;
        EdgeNode * tmp = new EdgeNode ;
        tmp->adjvex = edgeB ;
        tmp->edge = weight ;
        tmp->next = vertex[edgeA].next ;
        vertex[edgeA].next = tmp ;
        tmp = NULL ;
        tmp = new EdgeNode ;
        tmp->adjvex = edgeA ;
        tmp->edge = weight ;
        tmp->next = vertex[edgeB].next ;
        vertex[edgeB].next = tmp ;
    }
    cout <<"����ͼ�������\n" ;
}
Graph::~Graph()
{
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            EdgeNode * posNext = pos->next ;
            delete pos ;
            pos = posNext ;
        }
    }
    delete dfn ;
    delete bfn ;
    delete isVisited ;
}
void Graph::DFSTraverse()
{
    cout <<"�����������Ϊ:\n" ;
    counter = 0 ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        isVisited[i] = false ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        if(isVisited[i] == false)
        {
            DFSX(i) ;
        }
    }
    hasDFS = true ;
    cout <<endl ;
}
void Graph::DFSX(int vertexOrder)
{
    Stack<int> s ;
    s.makeNull() ;
    s.push(vertexOrder) ;
    isVisited[vertexOrder] = true ;
    while(!s.isEmpty())
    {
        int k = s.pop() ;
        dfn[k] = counter ;
        counter++ ;
        cout <<vertex[k].data <<"\t" ;
        EdgeNode * pos = vertex[k].next ;
        while(pos != NULL)
        {
            if(isVisited[pos->adjvex] == false)
            {
                s.push(pos->adjvex) ;
                isVisited[pos->adjvex] = true ; //!!����ʱ����Ϊ�ѷ���

            }
            pos = pos->next ;
        }
    }

}
void Graph::BFSTraverse()
{
    cout <<"�ȹ��������Ϊ:\n" ;
    counter = 0 ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        isVisited[i] = false ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        if(isVisited[i] ==  false)
        {
            BFSX(i) ;
        }
    }
    hasBFS = true ;
    cout << endl ;
}
void Graph::BFSX(int vertexOrder)
{
    Queue<int> q ;
    q.makeNull() ;
    q.EnQueue(vertexOrder) ;
    isVisited[vertexOrder] = true ;
    while(!q.isEmpty())
    {
        int k = q.Front() ;
        q.DeQueue() ;
        bfn[k] = counter ;
        counter++ ;
        cout <<vertex[k].data <<"\t" ;
        EdgeNode * pos = vertex[k].next ;
        while(pos != NULL)
        {
            if(isVisited[pos->adjvex] == false)
            {
                q.EnQueue(pos->adjvex) ;
                isVisited[pos->adjvex] = true ; //!!!!�����Ǿͱ��뽫����Ϊ�Ѿ����ʣ���
            }
            pos = pos->next ;
        }
    }
}
void Graph::printDFN()
{
    if(hasDFS == true)
    {
        cout <<"������Ϣ:  \t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<vertex[i].data <<"\t" ;
        }
        cout <<"\n����������\t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<dfn[i]+1 <<"\t" ;
        }
        cout <<endl ;
    }
    else
    {
        cout <<"��δ�����������\n" ;
    }
}
void Graph::printBFN()
{
    if(hasDFS == true)
    {
        cout <<"������Ϣ:  \t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<vertex[i].data <<"\t" ;
        }
        cout <<"\n�ȹ�������\t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<bfn[i]+1 <<"\t" ;
        }
        cout <<endl ;
    }
    else
    {
        cout <<"��δ�����ȹ����\n" ;
    }
}
/**
    **�㷨���ƣ�Prim
    **ʵ�ֹ��ܣ������С������
    **�㷨Ҫ�㣺��������U�����Ƚ�����1���뼯�ϣ��ҳ����乹����СȨֵ�ıߵĶ��㣬����U��
                ��V-U���ҳ�����x1��U�ж���x2���ɵ�Ȩֵ��С�ıߣ���x1����U���ظ���֪��U=V ��
                ÿ�ҵ�һ��������ñ�������
    **ʵ�ַ���������CLOSEST[vertexNum],LOWCOST[vertexNum]�������飬ǰ�߼�¼����i������U�������
                Ȩֵ�Ķ���k�����߼�¼��Ӧ��Ȩֵ
*/
void Graph::Prim()
{
    cout <<"Prime�㷨��С����������Ϊ:\t" ;
    int LOWCOST[vertexNum] ;
    int CLOSEST[vertexNum] ;
    const int visited = INFINITY +1 ;
    //��ʼ��,��vertex[0]����U
    for(int i = 0 ; i< vertexNum ; i++)
    {
        CLOSEST[i] = 0 ;
        LOWCOST[i] =INFINITY ;//�ȳ�ʼ��
    }
    EdgeNode * pos = vertex[0].next ;
    while(pos != NULL)
    {
        LOWCOST[pos->adjvex] = pos->edge ;
        pos = pos->next ;
    }
    int min , k ;
    //��U֮���ҵ�U��̵�·
    for(int i = 1 ; i < vertexNum ; i++)
    {
        min = LOWCOST[i] ;
        k = i ;
        for(int j = 1 ; j < vertexNum ; j++)
        {
            if(LOWCOST[j] < min)
            {
                min = LOWCOST[j] ;
                k = j ;
            }
        }
        cout <<"(" <<k+1 <<"," <<CLOSEST[k]+1 <<")\t" ;
        LOWCOST[k] = visited ;//��Ϊ���ʹ������Ǽ��뵽U��
        pos = vertex[k].next ;
        while(pos != NULL)
        {
            if(LOWCOST[pos->adjvex] > pos->edge && LOWCOST[pos->adjvex] != visited)
            {
                LOWCOST[pos->adjvex] = pos->edge ;
                CLOSEST[pos->adjvex] = k ;
            }
            pos = pos->next ;
        }
    }
    cout <<endl ;
}
/**
    **�㷨���ƣ� Kruskal
    **ʵ�ֹ��ܣ������С������
    **�㷨Ҫ�㣺����������뵥���Ĳ��鼯��Ѱ�Ҹ����鼯֮���Ȩֵ��С�ıߣ�����ߵ��������㣬��
                 �����������ڵĲ��鼯�ϲ����ظ�N-1�Σ����ϲ���һ�����鼯��
*/
void Graph::Kruskal()
{
    cout <<"Kruskal�㷨��С����������Ϊ:\t" ;
    Mfset set(vertexNum) ;
    //��ʼ�����鼯
    for(int i = 1 ; i<= vertexNum ; i++)
    {
        set.Init(i) ;//���ڲ��鼯���±�1Ϊ��ʼ��ע��ת������
    }

    for(int i = 0 ; i < vertexNum -1 ; i++)//��С��������N-1����
    {
        int edgeA = 0 ;
        int edgeB = 0 ;
        int minWeight ;
        for(int ii = 0 ; ii< vertexNum-1 ; ii++)//�����ǣ�����ͼ�ĶԳ��ԣ�
        {
            EdgeNode * pos  = vertex[ii].next ;
            while(pos != NULL)
            {
                if(pos->adjvex > ii && set.isEquivalence(ii+1,(pos->adjvex) +1)== false )
                {
                    if(edgeA == 0 && edgeB == 0)
                    {
                        edgeA = ii ;
                        edgeB = pos->adjvex ;
                        minWeight = pos->edge ;
                    }
                    else
                    {
                        if( pos->edge < minWeight )
                        {
                            edgeA = ii ;
                            edgeB = pos->adjvex ;
                            minWeight = pos->edge ;

                        }
                    }
                }
                pos = pos->next ;
            }

        }

        set.Union(edgeA+1,edgeB+1) ;
        cout <<"(" <<edgeA+1 <<"," <<edgeB+1 <<")\t" ;
    }
}
/**
    **�㷨���ƣ�Dijkstra
    **ʵ�ֹ��ܣ���ⵥԴ���·��
    **�㷨Ҫ�㣺��V��Ϊ��������S��V-S��S�ʼֻ����Դ�� ���ҳ�V-S�еĸ��㵽S�����·��
                �ĵ㣬������뵽S�У�ֱ��S = V ��
    **�ؼ����룺for(V-S�е�ÿ������v)
                D[v]= min(D(v),D(w)+C[w][v]) ;
*/
void Graph::Dijkstra(int sourcePoint)
{
    sourcePoint -- ;
    if(sourcePoint > vertexNum -1 || sourcePoint < 0)
    {
        cout <<"INVALID SOURCEPOINT\n" ;
        return ;
    }
    cout <<"Dijkstra�㷨��Դ���·�����Ϊ��\n" ;
    int distance[vertexNum] ;
    bool isInS[vertexNum] ;
    int preVertex[vertexNum] ;
    //��ʼ������Դ�� ���뵽S��
    for(int i = 0 ; i < vertexNum ; i++)
    {
        distance[i] = INFINITY ;
        isInS[i] = false ;
        preVertex[i] = sourcePoint ;
    }
    EdgeNode * pos = vertex[sourcePoint].next ;
    while(pos != NULL)
    {
        distance[pos->adjvex] = pos->edge ;
        pos = pos->next ;
    }
    distance[sourcePoint] = 0 ;
    isInS[sourcePoint] = true ;
    preVertex[sourcePoint] = -1 ;
    for(int i = 1 ; i< vertexNum ; i++)//N-1����
    {
        int minDis = -1 ; //�޳�ֵ
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            if(isInS[ii] == false )
            {
                if(minDis == -1)
                {
                    minDis = ii ; //��ֵ
                }
                else
                {
                    if(distance[ii] < distance[minDis])
                    {
                        minDis = ii ;
                    }
                }

            }
        }
        isInS[minDis] = true ;
        pos = vertex[minDis].next ;
        while(pos != NULL)
        {
            if(isInS[pos->adjvex] == false && distance[pos->adjvex] > distance[minDis]+pos->edge)
            {
                distance[pos->adjvex] = distance[minDis] + pos->edge ;
                preVertex[pos->adjvex] = minDis ;
            }
            pos = pos->next ;
        }

    }
    cout <<"������Ϣ:                   \t" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout << vertex[i].data <<"\t" ;
    }
    cout <<"\nԴ��"<<vertex[sourcePoint].data<<"���õ�����·�����ȣ�\t" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        cout << distance[i] <<"\t" ;
    }
    cout << endl ;
    cout <<"��ϸ��Ϣ��\n" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        cout <<"Դ��"<<vertex[sourcePoint].data<<"������"<<vertex[i].data<<"�ľ���·��������Ϊ:\t" ;
        int k = i ;
        while(k != -1)
        {
            cout <<vertex[k].data <<"\t" ;
            k = preVertex[k] ;
        }
        cout <<endl ;
    }
}
/**
    **�㷨���ƣ�Floyd
    **ʵ�ֹ��ܣ����ÿ�Զ�������̾���
    **�㷨Ҫ�㣺 - -
*/
void Graph::Floyd()
{
    int A[vertexNum][vertexNum] ;
    int ** preVertex ;
    preVertex = new int*[vertexNum] ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        preVertex[i] = new int[vertexNum] ;
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        for(int j = 0 ; j < vertexNum ; j++)
        {
            if(i == j)
            {
                A[i][j] = 0 ;
            }
            else
            {
                A[i][j] = INFINITY ;
            }
            preVertex[i][j] = -1 ;
        }
    }
    for(int i = 0 ; i < vertexNum ; i++)
    {
        EdgeNode * pos = vertex[i].next ;
        while(pos != NULL)
        {
            A[i][pos->adjvex] = pos->edge ;
            pos = pos->next ;
        }
    }
    for(int k = 0 ; k< vertexNum ; k++)
    {
        for(int i = 0 ; i< vertexNum ; i++)
        {
            for(int j = 0 ; j < vertexNum ; j++)
            {
                if(A[i][j] > A[i][k]+A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j] ;
                    preVertex[i][j] = k ;
                }
            }
        }
    }
    cout <<"ÿ�Զ���֮������·�����¾�����ʾ:\n" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j < vertexNum ; j++)
        {
            cout <<A[i][j] <<"\t" ;
        }
        cout <<endl ;
    }
    cout <<"��ϸ��Ϣ:\n" ;
    for(int i = 0 ; i< vertexNum -1 ; i++)
    {
        for(int j = i+1 ; j < vertexNum ; j++)
        {
            cout <<"Դ��"<<vertex[i].data<<"���յ�"<<vertex[j].data<<"�м侭���Ķ����У�" ;
            FloydPath(i,j,preVertex) ;
            cout <<"^\n" ;
        }
    }
    for(int i = 0 ; i< vertexNum ; i++)
    {
        delete [] preVertex[i] ;
    }
    delete preVertex ;

}
void Graph::FloydPath(int pointA ,int pointB,int ** preVertex)
{
    int k = preVertex[pointA][pointB] ;
    if(k!= -1)
    {
        FloydPath(pointA,k,preVertex) ;
        cout <<vertex[k].data <<"\t"  ;
        FloydPath(k,pointB,preVertex) ;
    }
}
int Graph::getVertexNum()
{
    return vertexNum ;
}


#endif // GRAPH_ADJLIST_H_INCLUDED
