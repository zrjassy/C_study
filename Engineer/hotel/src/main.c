#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "hotel.h"

int mainmenu()
{
    printf("\t\t\t      hotel management\n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t      1 : control\n");
    printf("\t\t\t      2 : living\n");
    printf("\t\t\t      3 : eating\n");
    printf("\t\t\t      0 : exit\n");
    printf("\t\t\t===============================\n");
    printf("please select:");
    int c;
    scanf("%d", &c);
    while (c < 0 || c > 3)
    {
        printf("error,input again:\n");
        scanf("%d", &c);
    }
    return c;
}

int main(int argc, char const *argv[])
{
    int c;
    int loop = 1;
    while (loop)
    {
        system("cls");
        c=mainmenu();
        switch(c)
		{
			case 1://control
                add_room();
				break;
			case 2://living
                hotel_system();
				break;
            case 3://eating
				break;
			default:
				loop = 0;
				break;
		}
    }
    return 0;
}
