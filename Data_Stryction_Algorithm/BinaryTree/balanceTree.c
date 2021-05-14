// 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。
// 如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
#include <stdio.h>

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

int max(int a, int b)
{
    return a > b ? a : b;
}

int abs(int a, int b)
{
    return a > b ? a - b : b - a;
}

int searchDeep(bitTree *root)
{
    if (root == NULL)
        return 0;
    else
        return max(searchDeep(root->lchild), searchDeep(root->rchild)) + 1;
}

int isBalance(bitTree *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int left, right;
        left = isBalance(root->lchild);
        right = isBalance(root->rchild);
        if (left == -1 || right == -1)
            return -1;
        return abs(left, right) <= 1 ? max(left, right) + 1 : -1;
    }
}

int main(int argc, char const *argv[])
{
    bitTree *root;
    root = CreateTree();
    int deep = 0;
    deep = searchDeep(root);
    if(isBalance(root)!=-1)
        printf("true.\n");
    else
        printf("false.\n");
    printf("deep:%d\n", deep);
    return 0;
}
