#include <stdio.h>

/*输入一个数组，判断其子序列和的最大值，并输出其子序列的开头和结尾*/

struct max
{
    /* data */
    int maxsum;
    int begin;
    int end;
};

// 算法1：循环遍历所有可能的组合，求其中的最大值。复杂度为O(N^3)
struct max MaxSubSequenceSum1(const int A[], int N)
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

            if (thisSum > MaxSum)
            {
                MaxSum = thisSum;
                begin = i;
                end = j;
            }
        }
    struct max Max;
    Max.maxsum = MaxSum;
    Max.begin = begin;
    Max.end = end;

    return Max;
}

// 算法2
struct max MaxSubSequenceSum2(const int A[], int N)
{
    int thisSum, MaxSum, i, j;
    int begin = 0, end = 0;
    MaxSum = 0;
    for (i = 0; i < N; i++)
    {
        thisSum = 0;
        for (j = i; j < N; j++)
        {
            thisSum += A[j];
            if (thisSum > MaxSum)
            {
                MaxSum = thisSum;
                begin = i;
                end = j;
            }
        }
    }
    struct max Max;
    Max.maxsum = MaxSum;
    Max.begin = begin;
    Max.end = end;

    return Max;
}

// 算法3
struct max MaxSubSequenceSum3(const int A[], int N)
{
    int ThisSum, MaxSum, j, Begin, End;
    Begin = End = 0;
    ThisSum = MaxSum = 0;
    for (j = 0; j < N; j++)
    {
        ThisSum += A[j];
        if (ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
            ThisSum = 0;
    }
    struct max Max;
    Max.maxsum = MaxSum;
    Max.begin = Begin;
    Max.end = End;

    return Max;
};

int main()
{
    int A[7] = {1, -2, 3, 1, -2, 0, 1};
    int N = 7;
    struct max Max1 = MaxSubSequenceSum1(A, N);
    struct max Max2 = MaxSubSequenceSum2(A, N);
    struct max Max3 = MaxSubSequenceSum3(A, N);
    printf("calcu1:\n");
    printf("maxsum:%d\nbegin:%d\nend:%d\n", Max1.maxsum, Max1.begin, Max1.end);
    printf("calcu2:\n");
    printf("maxsum:%d\nbegin:%d\nend:%d\n", Max2.maxsum, Max2.begin, Max2.end);
    printf("calcu3:\n");
    printf("maxsum:%d\nbegin:%d\nend:%d\n", Max3.maxsum, Max3.begin, Max3.end);
    return 0;
}
