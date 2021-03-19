typedef struct doubleNode
{
    int data;
    struct doubleNode *pre, *next;
} Node;
typedef struct doubleLinkList
{
    int counter;
    Node *head;
    Node *tail;
} dList;

dList *Create();
dList *Insert(dList *List, int pos, int data);
dList *Delete(dList *List, int pos);
dList *Get(dList *List, int pos);
dList *Replace(dList *List, int pos, int data);
int *Has(dList *List, int data);
