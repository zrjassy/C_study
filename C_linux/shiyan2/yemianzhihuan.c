#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct item
{
    int num;
    int time;
    int use;
} Pro;

void showmenu()
{
    printf("****f:FIFO页面置换****\n");
    printf("****o:OPT页面置换***\n");
    printf("****l:LRU页面置换****\n");
    // printf("****c:CLOCK****\n");
    printf("Please enter the type.End with else.\n");
}

void printMemory(Pro *memory, int setsize)
{
    int i;
    for (i = 0; i < setsize; i++)
    {
        printf("%d %d  ", memory[i].num, memory[i].time);
    }
    printf("\n");
}

int Search(int num, Pro *memory, int setsize)
{
    int j;

    for (j = 0; j < setsize; j++)
    {
        if (memory[j].num == num)
            return j;
    }
    return -1;
}

void FIFO(Pro *page, int pages, Pro *memory, int setsize)
{
    printf("FIFO:\n");
    int missPages = 0;
    float missRate;
    int current = 0;
    int i;
    for (i = 0; i < pages; i++)
    {
        if (Search(page[i].num, memory, setsize) < 0)
        {
            if (memory[current].num != -1)
                missPages++;
            memory[current].num = page[i].num;
            current = (current + 1) % setsize;
        }
        printMemory(memory, setsize);
    }
    missRate = (float)missPages / pages;
    printf("Page fault:%d,page rate:%f\n", missPages, missRate);
}

void OPT(Pro *page, int pages, Pro *memory, int setsize)
{
    printf("OPT:\n");
    int missPages = 0;
    float missRate;
    int current = 0;
    int i;
    for (i = 0; i < pages; i++)
    {
        // t表示位置
        int t;
        t = Search(page[i].num, memory, setsize);
        if (t < 0)
        {
            //找出未来最长时间内不再被访问的页面
            int tem;
            int opt = 0;   // 定义未来最长不再被访问的时间
            int time = -1; // 定义过去最长未使用时间
            for (int k = 0; k < setsize; k++)
            {
                // 尚有空间
                if (memory[k].num == -1)
                {
                    current = k;
                    break;
                }
                tem = 0; //页面k在未来tem时间内不会出现
                int j;
                for (j = i + 1; j < pages; j++)
                {
                    if (page[j].num == memory[k].num)
                    {
                        if (tem > opt)
                        {
                            opt = tem;
                            current = k;
                        }
                        break;
                    }
                    tem++;
                }
                // 页面k在未来一直没有出现
                if (j == pages)
                {

                    opt = tem;
                    // 判断页面k过去未使用时间是否最长
                    if (memory[k].time > time)
                    {
                        current = k;
                        time = memory[k].time;
                    }
                }
            }
            // 产生缺页中断
            if (memory[current].num != -1)
                missPages++;
            memory[current].num = page[i].num;
            memory[current].time = 0;
            int m;
            for (m = 0; m < setsize; m++)
            {
                if (m != current && memory[m].num != -1)
                    memory[m].time++;
            }
        }
        else
        {
            int m;
            for (m = 0; m < setsize; m++)
            {
                if (m == t)
                    memory[m].time = 0;
                else if (memory[m].num != -1)
                    memory[m].time++;
            }
        }
        printMemory(memory, setsize);
    }
    missRate = (float)missPages / pages;
    printf("Page fault:%d,page rate:%f\n", missPages, missRate);
}

void LRU(Pro *page, int pages, Pro *memory, int setsize)
{
    printf("LRU:\n");
    int missPages = 0;
    float missRate;
    int current = 0;
    int i;
    for (i = 0; i < pages; i++)
    {
        int t;
        t = Search(page[i].num, memory, setsize);
        if (t < 0)
        {
            int time = -1; // 定义过去最长未使用时间
            for (int k = 0; k < setsize; k++)
            {
                // 尚有空间
                if (memory[k].num == -1)
                {
                    current = k;
                    break;
                }
                if (memory[k].time > time)
                {
                    current = k;
                    time = memory[k].time;
                }
            }
            // 产生缺页中断
            if (memory[current].num != -1)
                missPages++;
            memory[current].num = page[i].num;
            memory[current].time = 0;
            int m;
            for (m = 0; m < setsize; m++)
            {
                if (m != current && memory[m].num != -1)
                    memory[m].time++;
            }
        }
        else
        {
            int m;
            for (m = 0; m < setsize; m++)
            {
                if (m == t)
                    memory[m].time = 0;
                else if (memory[m].num != -1)
                    memory[m].time++;
            }
        }
        printMemory(memory, setsize);
    }
    missRate = (float)missPages / pages;
    printf("Page fault:%d,page rate:%f\n", missPages, missRate);
}

int main(int argc, char const *argv[])
{
    int pages, setsize; // 页数目 驻留吉大小
    printf("Please enter the number of pages:");
    scanf("%d", &pages);
    printf("Please enter the resident set size:");
    scanf("%d", &setsize);
    int i;
    Pro *page;
    Pro *memory;
    page = (Pro *)malloc(pages * sizeof(Pro));
    memory = (Pro *)malloc(setsize * sizeof(Pro));
    for (i = 0; i < pages; i++)
    {
        printf("Page %d:", i);
        scanf("%d", &page[i].num);
        page[i].time = 0;
        page[i].use = -1;
    }
    while (1)
    {
        for (i = 0; i < setsize; i++)
        {
            memory[i].num = -1;
            memory[i].time = -1;
            memory[i].use = -1;
        }
        showmenu();
        char T;
        getchar();
        scanf("%c", &T);
        if (T == 'f')
        {
            FIFO(page, pages, memory, setsize);
        }
        else if (T == 'o')
        {
            OPT(page, pages, memory, setsize);
        }
        else if (T == 'l')
        {
            LRU(page, pages, memory, setsize);
        }
        else if (T == 'c')
        {
            
            continue;
        }
        else
            break;
    }
    return 0;
}
