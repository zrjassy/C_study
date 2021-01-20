#include "List.h"
#include <stdlib.h>
#include <stdio.h>

/* Place in the interface file */
struct Node
{
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L)
{
    if (L != NULL)
        DeleteList(L);
    L = malloc(sizeof(struct Node));
    if (L == NULL)
        FatalError("Out of memory!");
    L->Next = NULL;
    return L;
}

/* Return true if L is empty */
int IsEmpty(List L)
{
    return L->Next == NULL;
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

/* Return Position of X in L; NULL if not found */
Position Find(ElementType X, List L)
{
    Position P;

    P = L->Next;
    while (P != NULL && P->Element != X)
        P = P->Next;

    return P;
}


/* Delete from a list */
/* Cell pointed to by P->Next is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */
void Delete(ElementType X, List L)
{
    Position P, TmpCell;

    P = FindPrevious(X, L);

    if (!IsLast(P, L)) /* Assumption of header use */
    {                  /* X is found; delete it */
        TmpCell = P->Next;
        P->Next = TmpCell->Next; /* Bypass deleted cell */
        free(TmpCell);
    }
}

/* If X is not found, then Next field of returned value is NULL */
/* Assumes a header */
Position FindPrevious(ElementType X, List L)
{
    Position P;

    /* 1*/ P = L;
    /* 2*/ while (P->Next != NULL && P->Next->Element != X)
        /* 3*/ P = P->Next;

    /* 4*/ return P;
}
/* END */

/* START: fig3_13.txt */
/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;

    /* 1*/ TmpCell = malloc(sizeof(struct Node));
    /* 2*/ if (TmpCell == NULL)
        /* 3*/ FatalError("Out of space!!!");

    /* 4*/ TmpCell->Element = X;
    /* 5*/ TmpCell->Next = P->Next;
    /* 6*/ P->Next = TmpCell;
}
/* END */

/* START: fig3_15.txt */
/* Correct DeleteList algorithm */

void DeleteList(List L)
{
    Position P, Tmp;

    /* 1*/ P = L->Next; /* Header assumed */
    /* 2*/ L->Next = NULL;
    /* 3*/ while (P != NULL)
    {
        /* 4*/ Tmp = P->Next;
        /* 5*/ free(P);
        /* 6*/ P = Tmp;
    }
}
/* END */

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
    return P->Next;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}