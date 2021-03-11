#include <stdio.h>

/*计算X^N,如果N是偶数，X^N = X^N/2 * X^N/2 ;如果N为奇数，则X^N = X^(N-1)/2 * X^(N-1)/2 * X */

int IsEven(int N)
{
    if (N % 2 == 1)
        return 1;
    else if (N % 2 == 0)
        return 0;
}

long int Pow(long int X, unsigned int N)
{
    if (N == 0)
        return 1;
    if (N == 1)
        return X;
    if (IsEven(N))
        return Pow(X * X, N / 2);
    else
        // return Pow(X * X, N / 2) * X;
        return Pow(X, N - 1) * X;
}

int main()
{
    long int X = 12000;
    int N = 6;
    long int Y = Pow(X, N);
    printf("%ld\n", Y);
}
