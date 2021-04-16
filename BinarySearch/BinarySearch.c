#include <stdio.h>

// 给定一个整数X和整数数列A0,A1,...AN-1,求使得Ai=X的下标i,如果X不在数据中，则返回i=-1

int BinarySearch(const int A[], int X, int N)
{
    int Low, Mid, High;
    Low = 0;
    High = N - 1;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (A[Mid] < X)
            Low = Mid + 1;
        else if (A[Mid] > X)
            High = Mid - 1;
        else
            return Mid;
    }
    return -1;
}

int main()
{
    int A[7]={-2,-1,3,4,6,9,10};
    int N=7;
    int X=3;
    int i=BinarySearch(A,X,N);
    printf("i:%d\n",i);
    return 0;
}