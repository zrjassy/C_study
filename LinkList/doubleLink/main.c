#include <stdio.h>
#include "list.h"

int main()
{
    dList *List;
    List = Create();
    List = Insert(List,0,2);
    List = Insert(List,0,3);
    List = Insert(List,0,4);
    List = Insert(List,0,5);
    List = Insert(List,1,8);
    return 0;
}