#include <iostream>
#include "../lib_x/BTree.h"
#include <ctime>
#include <stdlib.h>
using namespace std;

int main()
{
    BTree<int> x(2) ;

    for(int i = 0 ; i< 100 ; i++)
    {
        x.btreeInsert(i) ;

    }
    x.printBTree() ;
    BTNode<int> * result ;
    int index ;
    for(int i = 0 ; i <100 ; i++)
    {
        x.btreeDelete(i);
        if(x.search(i-1,result,index))
        {
            cout <<result <<" " <<index <<endl ;
        }
        else
        {
            cout <<"\n\nnot find." ;
        }
       // x.printBTree();
    }

    srand(time(NULL)) ;
    const int quantity = 30 ;
    int randomNum[quantity] ;
    for(int i = 0 ; i < quantity ; i++)
    {
        randomNum[i] = rand()%1000 ;
    }
    int counter = 0 ;
    for(int i =0 ; i < quantity ; i++)
    {
        if(x.btreeInsert(randomNum[i]) )
        {
            counter++ ;
        }
    }
    cout <<counter<<endl ;
    x.printBTree() ;
    counter = 0 ;
    for(int i = 0 ; i < quantity ; i++)
    {
        if(x.search(randomNum[i],result,index) )
        counter++ ;
        cout <<counter <<endl ;
       // x.printBTree() ;
    }
    //cout <<counter <<endl ;

    return 0;
}
