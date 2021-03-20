#include <stdio.h>
#include "list.h"

int main()
{
    dList *List;
    List = Create();
    List = Insert(List, 0, 2);
    List = Insert(List, 0, 3);
    List = Insert(List, 0, 4);
    List = Insert(List, 0, 5);
    List = Insert(List, 1, 8);
    List = Delete(List, 3);
    Node *k = Get(List, 3);
    Output(List);
    printf("%d \n", k->data);
    List = Replace(List, 3, 9);
    Output(List);
    printf("%d \n", k->data);
    printf("%d \n",Has(List,9));
    return 0;
}