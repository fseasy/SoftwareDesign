#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "../lib_x/sort.h"
using namespace std;

int main()
{
    const int small = 200 ;
    int randomArray[small] ;
    srand(time(NULL)) ;
    for(int i =0 ; i < small ; i++)
    {
        randomArray[i] = rand()%small ;
    }
    QuickSort(0,small-1 ,randomArray) ;
    for(int i = 0 ; i< small -1 ; i++)
    {
        if(randomArray[i]-randomArray[i+1] >0)
        cout <<"wrong ";
    }
    return 0;
}
