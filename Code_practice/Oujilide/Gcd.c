#include <stdio.h>

unsigned int Gcd(unsigned int M, unsigned int N)
{
    unsigned int Rem;

    while (N > 0)
    {
        Rem = M % N;
        M = N;
        N = Rem;
    }
    return M;
}

int main()
{
    int M = 1239;
    int N = 345;
    int X = Gcd(M, N);
    printf("%d",X);
}