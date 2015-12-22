#include <iostream>
#include "../lib_x/AVLTree.h"
/**
    程序名称：AVL树
    数据结构：AVL树
*/
using namespace std;

int main()
{
    AVLTree<int> avl ;
    AVLNode<int> tmp ;
    for(int i = 0 ; i< 20 ; i++)
    {
        tmp.data = i ;
        avl.Insert(tmp) ;
    }
    avl.LevelOrder() ;
    return 0;
}
