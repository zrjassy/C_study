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
            root=s;
        else
        {
            if(s&&Q[front])
            {
                if(rear%2==0)
                    Q[front]->lchild=s;
                else
                    Q[front]->rchild=s;
            }
            if(rear%2==1)
                front++;
        }
    }
    return root;
}

// 深度优先遍历
// 先序遍历
void PreOrder(bitTree *root)
{
    if(root!=NULL)
    {
        printf("%c ",root->data);
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

// 中序遍历
void InOrder(bitTree *root)
{
    if(root!=NULL)
    {
        InOrder(root->lchild);
        printf("%c ",root->data);
        InOrder(root->rchild);
    }
}

// 后序遍历
void PostOrder(bitTree *root)
{
    if(root!=NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%c ",root->data);
    }
}

int main(int argc, char const *argv[])
{
    bitTree *root;
    root=CreateTree();
    PreOrder(root);
    printf("\n");
    InOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");
    return 0;
}
