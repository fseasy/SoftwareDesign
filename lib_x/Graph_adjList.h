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

//建立邻接矩阵型的无向图
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
    cout <<"请输入图的顶点数和边的条数\n" ;
    cin >> vertexNum >> edgeNum ;
    vertex = new VertexNode[vertexNum] ;
    isVisited =  new bool[vertexNum] ;
    dfn= new int[vertexNum] ;
    bfn = new int[vertexNum] ;
    hasDFS = false ;
    hasBFS = false ;
    counter = 0 ;
    cout <<"请依次输入各顶点的数据\n" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cin >> vertex[i].data ;
        vertex[i].next = NULL ;
    }
    cout <<"顶点数据输入完成\n" ;
    for(int i = 0 ; i < edgeNum ; i++)
    {
        cout <<"顶点编号:\t" ;
        for(int k = 0 ; k < vertexNum ; k++)
        {
            cout <<k+1 <<"\t" ;
        }
        cout <<"\n顶点值: \t" ;
        for(int k = 0 ; k < vertexNum ; k++)
        {
            cout <<vertex[k].data <<"\t" ;
        }
        cout << endl ;
        cout <<"请输入第"<< i+1 <<"条边的两个顶点序号,并输入权值\n" ;
        int edgeA,edgeB,weight ;
        while(cin >> edgeA >> edgeB >> weight)
        {
            edgeA -- ;
            edgeB -- ;
            if(edgeA >=vertexNum || edgeB >= vertexNum)
            {
                cout <<"不合法的顶点序号，请重新输入\n" ;
            }
            else if(weight <0)
            {
                cout <<"不合法的权值（小于0）\n,请重新输入该边全部信息\n" ;
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
    cout <<"边信息输入完成\n" ;
    cout <<"无向图建立完成\n" ;
}
Graph::Graph(fstream &in)
{
    cout <<"开始从文件中读取数据\n" ;
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
    cout <<"无向图建立完成\n" ;
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
    cout <<"先深遍历序列为:\n" ;
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
                isVisited[pos->adjvex] = true ; //!!加入时就置为已访问

            }
            pos = pos->next ;
        }
    }

}
void Graph::BFSTraverse()
{
    cout <<"先广遍历序列为:\n" ;
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
                isVisited[pos->adjvex] = true ; //!!!!加入是就必须将其置为已经访问！！
            }
            pos = pos->next ;
        }
    }
}
void Graph::printDFN()
{
    if(hasDFS == true)
    {
        cout <<"顶点信息:  \t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<vertex[i].data <<"\t" ;
        }
        cout <<"\n先深遍历编号\t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<dfn[i]+1 <<"\t" ;
        }
        cout <<endl ;
    }
    else
    {
        cout <<"尚未进行先深遍历\n" ;
    }
}
void Graph::printBFN()
{
    if(hasDFS == true)
    {
        cout <<"顶点信息:  \t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<vertex[i].data <<"\t" ;
        }
        cout <<"\n先广遍历编号\t" ;
        for(int i = 0 ; i < vertexNum ; i++)
        {
            cout <<bfn[i]+1 <<"\t" ;
        }
        cout <<endl ;
    }
    else
    {
        cout <<"尚未进行先广遍历\n" ;
    }
}
/**
    **算法名称：Prim
    **实现功能：求解最小生成树
    **算法要点：建立集合U，首先将顶点1加入集合，找出与其构成最小权值的边的顶点，加入U，
                在V-U中找出顶点x1与U中顶点x2构成的权值最小的边，将x1加入U；重复，知道U=V ；
                每找到一条边输出该边两顶点
    **实现方法：建立CLOSEST[vertexNum],LOWCOST[vertexNum]辅助数组，前者记录顶点i到集合U的有最短
                权值的顶点k，后者记录对应的权值
*/
void Graph::Prim()
{
    cout <<"Prime算法最小生成树各边为:\t" ;
    int LOWCOST[vertexNum] ;
    int CLOSEST[vertexNum] ;
    const int visited = INFINITY +1 ;
    //初始化,把vertex[0]加入U
    for(int i = 0 ; i< vertexNum ; i++)
    {
        CLOSEST[i] = 0 ;
        LOWCOST[i] =INFINITY ;//先初始化
    }
    EdgeNode * pos = vertex[0].next ;
    while(pos != NULL)
    {
        LOWCOST[pos->adjvex] = pos->edge ;
        pos = pos->next ;
    }
    int min , k ;
    //从U之外找到U最短的路
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
        LOWCOST[k] = visited ;//置为访问过（即是加入到U）
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
    **算法名称： Kruskal
    **实现功能：求解最小二叉树
    **算法要点：将各顶点加入单独的并查集，寻找各并查集之间的权值最小的边，输出边的两个顶点，将
                 两个顶点所在的并查集合并，重复N-1次（即合并到一个并查集）
*/
void Graph::Kruskal()
{
    cout <<"Kruskal算法最小生成树各边为:\t" ;
    Mfset set(vertexNum) ;
    //初始化并查集
    for(int i = 1 ; i<= vertexNum ; i++)
    {
        set.Init(i) ;//由于并查集以下标1为起始，注意转化！！
    }

    for(int i = 0 ; i < vertexNum -1 ; i++)//最小生成树有N-1条边
    {
        int edgeA = 0 ;
        int edgeB = 0 ;
        int minWeight ;
        for(int ii = 0 ; ii< vertexNum-1 ; ii++)//上三角（无向图的对称性）
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
    **算法名称：Dijkstra
    **实现功能：求解单源最短路径
    **算法要点：将V分为两个集合S和V-S。S最开始只包含源点 。找出V-S中的各点到S中最短路径
                的点，将其加入到S中，直到S = V 。
    **关键代码：for(V-S中的每个顶点v)
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
    cout <<"Dijkstra算法求单源最短路径结果为：\n" ;
    int distance[vertexNum] ;
    bool isInS[vertexNum] ;
    int preVertex[vertexNum] ;
    //初始化（把源点 加入到S）
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
    for(int i = 1 ; i< vertexNum ; i++)//N-1条边
    {
        int minDis = -1 ; //无初值
        for(int ii = 0 ; ii< vertexNum ; ii++)
        {
            if(isInS[ii] == false )
            {
                if(minDis == -1)
                {
                    minDis = ii ; //初值
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
    cout <<"顶点信息:                   \t" ;
    for(int i = 0 ; i < vertexNum ; i++)
    {
        cout << vertex[i].data <<"\t" ;
    }
    cout <<"\n源点"<<vertex[sourcePoint].data<<"到该点的最短路径长度：\t" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        cout << distance[i] <<"\t" ;
    }
    cout << endl ;
    cout <<"详细信息：\n" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        cout <<"源点"<<vertex[sourcePoint].data<<"到顶点"<<vertex[i].data<<"的具体路径（逆序）为:\t" ;
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
    **算法名称：Floyd
    **实现功能：求解每对顶点间的最短距离
    **算法要点： - -
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
    cout <<"每对顶点之间的最短路径如下矩阵所示:\n" ;
    for(int i = 0 ; i< vertexNum ; i++)
    {
        for(int j = 0 ; j < vertexNum ; j++)
        {
            cout <<A[i][j] <<"\t" ;
        }
        cout <<endl ;
    }
    cout <<"详细信息:\n" ;
    for(int i = 0 ; i< vertexNum -1 ; i++)
    {
        for(int j = i+1 ; j < vertexNum ; j++)
        {
            cout <<"源点"<<vertex[i].data<<"到终点"<<vertex[j].data<<"中间经过的顶点有：" ;
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
