#include <iostream>
#include <fstream>
#include "../lib_x/STACK_list.h"
using namespace std;
/**
 **栈的应用：迷宫求解
 **创建迷宫类，包含迷宫的构造，输出，路径选择，以及最终的路径
 **使用数据结构：栈
 **栈的作用：用于回溯
 **特殊处理：创建迷宫数组时，在外围增加“一堵墙”，便于使程序判断边缘时一般化
*/
class Maze //迷宫类
{
public :
    Maze(int x,int y,bool ** maze_data) ;//使用外部的数据源而不在构造函数内部输入
    ~Maze() ;
    bool find_road() ;
    void road_print() ;
private :
    int width ;
    int height ;
    char * road ;
    int count ;
    bool ** maze ;
} ;
class point //坐标类
{
public:
    point(int X,int Y)
    {
        x = X ;
        y = Y ;
    }
    int getX()
    {
        return x ;
    }
    int getY()
    {
        return y ;
    }
private :
    int x ;
    int y ;
} ;
Maze::Maze(int x, int y,bool ** maze_data)
{
    width = x ;
    height = y ;
    road = new char[x*y] ;
    count = 0 ;

    for(int i = 0 ; i < x*y ; i++)
    {
        road[i] = '\0' ;
    }
    maze = maze_data ;
    cout <<"迷宫为： \n" ;
    for(int i = 0 ; i < x+2 ; i++)
    {
        for(int j = 0 ; j < y+2 ; j++)
        {
            if(maze[i][j] == true)
                cout <<"  " ;
            else
                cout <<"* " ;
        }
        cout <<endl ;
    }
}
Maze::~Maze()
{
    delete [] road ;
    road = NULL ;
}
bool Maze::find_road()
{
    Stack<point*> s  ;
    s.makeNull() ;
    int x,y ;
    x = 1 ;
    y = 1 ;
    point * curent  = new point(x,y) ;
    s.push(curent) ;
    maze[x][y] = false ;
    cout <<"\n\n" ;
    while(!s.isEmpty()&&!(x== width&& y == height))
    {
        if(maze[x-1][y] == true)
        {
            x-- ;
            curent = new point(x,y) ;
            s.push(curent) ;
            maze[x][y] = false ;
            road[count++] = 'u' ;
            cout <<"向上走，" ;
        }
        else if(maze[x+1][y] == true)
        {
            x++ ;
            curent = new point(x,y) ;
            s.push(curent) ;
            maze[x][y] = false ;
            road[count++] = 'd' ;
            cout <<"向下走，" ;
        }
        else if(maze[x][y-1] == true)
        {
            y-- ;
            curent = new point(x,y) ;
            s.push(curent) ;
            maze[x][y] = false ;
            road[count++] = 'l' ;
            cout <<"向左走，" ;
        }
        else if(maze[x][y+1] == true)
        {
            y++ ;
            curent = new point(x,y) ;
            s.push(curent) ;
            maze[x][y] = false ;
            road[count++] = 'r' ;
            cout <<"向右走，" ;
        }
        else
        {
            road[--count] =  '\0' ;
            s.pop() ;
            if(!s.isEmpty())
            {
                x = (*(s.Top())).getX() ;
                y = (*(s.Top())).getY() ;
            }
            cout <<"往回走，" ;

        }
    }
    if(x == width && y == height)
        return true ;
    else
        return false ;
}
void Maze::road_print()
{
    cout << "从迷宫入口进入，" ;
    for(int i = 0 ; i < count ; i++)
    {
        cout <<"向" ;
        switch(road[i])
        {
            case 'u' :
            cout <<"上" ;
            break ;
            case 'd' :
            cout <<"下" ;
            break ;
            case 'l' :
            cout <<"左" ;
            break ;
            case 'r' :
            cout <<"右" ;
        }
        cout <<"走，" ;
    }
    cout << "到达出口\n\n" ;
}


int main()
{
    int choice ;
    int x,y ;
    bool ** maze ;
    cout <<"1.查看迷宫示例\n2.创建迷宫\n输入序号来选择:" ;
    cin >> choice ;
    switch(choice)
    {
    case 1 :
    {
        x = 5 ;
        y = 5 ;
        break ;
    }
    case 2 :
    {
        cout <<"请输入迷宫的宽度和高度\n" ;
        cin >> x >> y ;
        cout << "请输入迷宫\n1表示可通过，0表示不能通过\n" ;
        break ;
    }
    default :
        cout <<"无效的选项\n" ;
    }
    char tmp ;
    ifstream in("mazeData.txt") ;
    if(in == NULL)
    {
        cout <<"迷宫导入失败\n" ;
        return false ;
    }
    //___________________________
    //二维数组的动态构造（为了给构造函数传参，故maze类型设为bool**）
    //若此处maze申明为maze[x+2][y+2],传参时使用（bool**）强转，会出错，不知原因
    maze = new bool*[x+2] ;
    for(int i = 0 ; i < x+2 ; i++)
    {
        maze[i] = new bool[y+2] ;
    }
    //____________________________
    for(int i = 0 ; i < x+2 ; i++)
    {
        for(int j = 0 ; j < y+2 ; j++)
        {
            if(i == 0 || i == x+1)
            {
                maze[i][j] = false ;
            }
            else if(j == 0 || j == y+1)
            {
                maze[i][j] = false ;
            }
            else
            {
                if(choice == 1)
                    in >> tmp ;
                else
                    cin >> tmp ;
                if(tmp == '1')
                    maze[i][j] = true ;
                else
                    maze[i][j] = false ;
            }
        }
    }
    //创建对象
    Maze mazeX(x,y,maze) ;
    if(mazeX.find_road())
    {
        cout <<"到达迷宫出口\n\n\n" ;
        cout <<"路径为:\n\n" ;
        mazeX.road_print() ;
    }

    else
        cout << "没有到达迷宫出口的路\n" ;

    cout <<"按任意键退出程序\n" ;
    getchar() ;
    return 0;
}
