#include <stdio.h>
#include <stdlib.h>

void DivideIntoGroup(int n, int R[][9], int cq[], int result[])
{
    int front, rear, group, pre, I, i;
    int newr[n];
    front = n - 1;
    rear = n - 1;
    for (i = 0; i < n; i++)
    {
        newr[i] = 0;
        cq[i] = i + 1;
    }
    group = 1;
    pre = 0;
    do
    {
        front = (front + 1) % n;
        I = cq[front];
        if (I < pre)
        {
            group = group + 1;
            result[I - 1] = group;
            for (i = 0; i < n; i++)
                newr[i] = R[I - 1][i];
        }
        else if (newr[I - 1] != 0)
        {
            rear = (rear + 1) % n;
            cq[rear] = I;
        }
        else
        {
            result[I - 1] = group;
            for (i = 0; i < n; i++)
                newr[i] += R[I - 1][i];
        }
        pre = I;
    } while (rear != front);
    for (i = 0; i < n; i++)
        printf("%d ", result[n]);
}

int main()
{
    int R[][9] = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
                  {1, 0, 0, 0, 1, 1, 0, 1, 1},
                  {0, 0, 0, 0, 0, 1, 1, 0, 0},
                  {0, 0, 0, 0, 1, 0, 0, 0, 1},
                  {0, 1, 0, 1, 0, 1, 1, 0, 1},
                  {0, 1, 1, 0, 1, 0, 1, 0, 0},
                  {0, 0, 1, 0, 1, 1, 0, 0, 0},
                  {0, 1, 0, 0, 0, 0, 0, 0, 0},
                  {0, 1, 0, 1, 1, 0, 0, 0, 0}};
    int cq[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int result[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int n = 9;
    DivideIntoGroup(n, R, cq, result);
    return 0;
}