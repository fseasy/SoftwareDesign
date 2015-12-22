#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#define INVALID -1
inline void swap(int & a,int & b)
{
    int tmp = a ;
    a = b ;
    b = tmp ;
}
int FindPivod(int i,int j,int A[])
{
    int firstKey = A[i] ;
    for(int ii = i+ 1 ; ii <= j ; ii++)
    {
        if(A[ii] > firstKey)
        {
            return ii ;
        }
        else if(A[ii] < firstKey)
        {
            return i ;
        }
    }
    return INVALID ;
}
int Partition(int i , int j , int pivod ,int A[])
{
    int l = i ;
    int r = j ;
    do
    {

        while(A[l] < pivod )
        {
            l++ ;
        }
        while(A[r] >= pivod )
        {
            r-- ;
        }
        if(l < r)
        {
            swap(A[l],A[r]) ;
        }
    }while( l<=r ) ;
    return l  ;
}
void QuickSort(int i,int j,int A[] )
{
    int pivodIndex = FindPivod(i,j,A) ;
    int pivod,k ;
    if(pivodIndex != INVALID)
    {
        pivod = A[pivodIndex] ;
        k = Partition(i,j,pivod,A) ;
        QuickSort(i,k-1,A) ;
        QuickSort(k,j,A) ;
    }

}
#endif // SORT_H_INCLUDED
