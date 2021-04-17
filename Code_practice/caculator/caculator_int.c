#include <stdio.h>
#include <stdlib.h>
/*问题：输入n个整数，求其各位数之和，从大到小排列，如果相同，则比较原数较小者放前
  输入输出举例：
  输入：
    5
    112 345 22 467 129
  输出：
    467 17
    129 12
    345 12
    22 4
    112 4
*/
int jisuanhe(int a)
{
    int r, s;
    r = 0;
    s = 0;
    while (a > 0)
    {
        r = a % 10;
        s = s + r;
        a = a / 10;
    }
    return s;
}

int main()
{
    int *p, *q, i, j, n;
    int temp;
    scanf("%d", &n);
    p = (int *)malloc(n * sizeof(int));
    q = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);
    for (i = 0; i < n; i++)
    {
        q[i] = jisuanhe(p[i]);
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (q[j] < q[j + 1])
            {
                temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
            if (q[j] == q[j + 1])
            {
                if (p[j] > p[j + 1])
                {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", p[i], q[i]);
    }

    return 0;
}