#include <stdio.h>
#include <stdlib.h>

#define N 7

void MapColor(int R[][N], int n, int S[])
{
    int color, area, k;
    S[0] = 1;
    area = 1;
    color = 1;
    while (area < N)
    {
        while (color <= 4)
        {
            k = 0;
            while ((k < area) && (S[k] * R[area][k] != color))
                k++;
            if (k < area)
                color++;
            else
            {
                S[area] = color;
                area++;
                if (area > N)
                    break;
                color = 1;
            }
        }
        if (color > 4)
        {
            area -= 1;
            color = S[area] + 1;
        }
    }
}

int main()
{
    int S[7];
    int R[][7] = {{0, 1, 1, 1, 1, 1, 0},
                 {1, 0, 0, 0, 0, 1, 0},
                 {1, 0, 0, 1, 1, 0, 0},
                 {1, 0, 1, 0, 1, 1, 0},
                 {1, 0, 1, 1, 0, 1, 0},
                 {1, 1, 0, 1, 1, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0}};
    int n;
    n = 7;
    MapColor(R,n,S);
    for(int i=0;i<7;i++)
        printf("%d\n",S[i]);
    return 0;
}