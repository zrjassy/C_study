#include <stdio.h>

/*输入一个数组，判断其子序列和的最大值，并输出其子序列的开头和结尾*/

struct max
{
    /* data */
    int maxsum;
    int begin;
    int end;
};

// 算法1：循环遍历所有可能的组合，求其中的最大值。
struct max MaxSubSequenceSum(const int A[], int N)
{
    int thisSum, MaxSum, i, j, k;
    int begin = 0, end = 0;
    MaxSum = 0;
    for (i = 0; i < N; i++)
        for (j = i; j < N; j++)
        {
            thisSum = 0;
            for (k = i; k < j + 1; k++)
                thisSum += A[k];

            if (thisSum > MaxSum){
                MaxSum = thisSum;
                begin=i;end=j;
            }       
        }
    struct max Max;
    Max.maxsum=MaxSum;
    Max.begin=begin;
    Max.end=end;
        
    return Max;
}

int main()
{
    int A[7]={1,2,3,1,-2,0,1};
    int N=7;
    struct max Max=MaxSubSequenceSum(A,N);
    printf("%d\n%d\n%d\n",Max.maxsum,Max.begin,Max.end);
    return 0;
}
