#include <stdio.h>
#include <stdlib.h>

typedef struct pnode
{
    float coef; // 系数
    int exp;    // 指数
    struct pnode *next;
} polyNode;

// 建立多项式的循环链表
polyNode *Create()
{
    float coef;
    int exp;
    polyNode *head, *s, *r;
    head = (polyNode *)malloc(sizeof(polyNode));
    head->coef = 0;
    head->exp = -1;
    r = head;
    printf("please input each coef and exp end with 0 0\n");
    while (1)
    {
        printf("coef exp:");
        scanf("%f %d", &coef, &exp);
        if (coef != 0)
        {
            s = (polyNode *)malloc(sizeof(polyNode));
            s->coef = coef;
            s->exp = exp;
            r->next = s;
            r = s;
        }
        else
            break;
    }
    r->next = head;
    return head;
}

// 多项式相加运算 A = A + B
polyNode *PolyAdd(polyNode *pa, polyNode *pb)
{
    polyNode *p, *q, *r, *s;
    float x;
    p = pa->next;
    q = pb->next;
    s = pa;
    while ((p != pa) && (q != pb))
    {
        if (p->exp < q->exp)
        {
            s = p;
            p = p->next;
        }
        if (p->exp > q->exp)
        {
            r = q->next;
            q->next = p;
            s->next = q;
            s = q;
            q = r;
        }
        else
        {
            x = p->coef + q->coef;
            if (x != 0)
            {
                p->coef = x;
                s = p;
            }
            else
            {
                s->next = p->next;
                free(p);
            }
            p = s->next;
            r = q;
            q = q->next;
            free(r);
        }
    }
    if (q != pb)
    {
        r = q;
        while (r->next != pb)
        {
            r = r->next;
        }
        s->next = q;
        r->next = pa;
    }
    return pa;
}

void Output(polyNode *head)
{
    polyNode *p;
    printf("each coef and exp is :");
    p = head->next;
    while (p != head)
    {
        printf("%.1f,%d ", p->coef, p->exp);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    polyNode *ha, *hb;
    printf("\ncreate hA:");
    ha = Create();
    Output(ha);
    printf("\ncreate hB:");
    hb = Create();
    Output(hb);
    ha = PolyAdd(ha, hb);
    printf("\nhA+hB:\n");
    Output(ha);
    return 0;
}
