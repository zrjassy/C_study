#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef struct node
{
    int data;
    struct node *lchild, *rchild;
} bitTree;

bitTree *CreateTree()
{
    char ch;
    bitTree *Q[MAXSIZE];
    int front, rear;
    bitTree *root, *s;
    root = NULL;
    front = 1;
    rear = 0;
    while ((ch = getchar()) != '#')
    {
        s = NULL;
        if (ch != '@')
        {
            s = (bitTree *)malloc(sizeof(bitTree));
            s->data = ch;
            s->lchild = NULL;
            s->rchild = NULL;
        }
        rear++;
        Q[rear] = s;
        if (rear == 1)
            root = s;
        else
        {
            if (s && Q[front])
            {
                if (rear % 2 == 0)
                    Q[front]->lchild = s;
                else
                    Q[front]->rchild = s;
            }
            if (rear % 2 == 1)
                front++;
        }
    }
    return root;
}

// 深度优先遍历
// 先序遍历
void PreOrder(bitTree *root)
{
    if (root != NULL)
    {
        printf("%c ", root->data);
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

// 中序遍历
void InOrder(bitTree *root)
{
    if (root != NULL)
    {
        InOrder(root->lchild);
        printf("%c ", root->data);
        InOrder(root->rchild);
    }
}

// 后序遍历
void PostOrder(bitTree *root)
{
    if (root != NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%c ", root->data);
    }
}

// 根据先序和中序数组重建二叉树
bitTree *BPI(char preod[], char inod[], int ps, int pe, int is, int ie)
{
    int m;
    bitTree *p;
    if (pe < ps)
        return NULL;
    p = (bitTree *)malloc(sizeof(bitTree));
    p->data = preod[ps];
    m = is;
    while (inod[m] != preod[ps])
        m++;
    p->lchild = BPI(preod, inod, ps + 1, ps + m - is, is, m - 1);
    p->rchild = BPI(preod, inod, ps + m - is + 1, pe, m + 1, ie);
    return p;
}

int main(int argc, char const *argv[])
{
    bitTree *root;
    root = CreateTree();
    PreOrder(root);
    printf("\n");
    InOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");

    char pre[7] = {'a', 'b', 'd', 'e', 'c', 'f', 'g'};
    char in[7] = {'d', 'b', 'e', 'a', 'f', 'c', 'g'};
    int ps,pe,is,ie;
    ps=0;
    is=0;
    pe=6;
    ie=6;
    bitTree *p;
    p=BPI(pre,in,ps,pe,is,pe);
    PreOrder(p);
    printf("\n");
    InOrder(p);
    printf("\n");
    PostOrder(p);
    printf("\n");
    return 0;
}
