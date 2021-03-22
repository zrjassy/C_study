#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
typedef struct
{
    char ch[MAXSIZE];
    int len;
} seqString;

seqString *StrCat(seqString *s, seqString *t)
{
    int i;
    seqString *r;
    r = (seqString *)malloc(sizeof(seqString));
    printf("s=%s t=%s\n", s->ch, t->ch);
    if (s->len + t->len > MAXSIZE)
        printf("Overflow\n");
    else
    {
        for (i = 0; i < s->len; i++)
            r->ch[i] = s->ch[i];
        for (i = 0; i < t->len; i++)
            r->ch[s->len + i] = t->ch[i];
        r->ch[s->len + i] = '\0';
        r->len = s->len + t->len;
    }
    return r;
}

seqString *Create()
{
    seqString *s;
    s = (seqString *)malloc(sizeof(seqString));
    printf("Input:");
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n')
    {
        s->ch[i] = ch;
        i++;
    }
    s->len = i;
    return s;
}

// 带回溯的模式匹配
int Index(seqString *s,seqString *t)
{
    int i=0,j=0;
    while (i<s->len&&j<t->len)
    {
        if(s->ch[i]==t->ch[j])
        {
            i++;j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j==t->len)
        return i-t->len;
    else
        return -1;
    
}

void Output(seqString *s)
{
    for (int i = 0; i < s->len; i++)
    {
        printf("%c", s->ch[i]);
    }
    printf("\n");
}

int main()
{
    seqString *s1, *s2;
    s1 = Create();
    Output(s1);
    s2 = Create();
    Output(s2);
    int q;
    q=Index(s1,s2);
    printf("Index:%d\n",q);
    s1 = StrCat(s1, s2);
    Output(s1);
    return 0;
}
