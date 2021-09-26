#include<stdio.h>
#include "hotel.h"

void menu();
int main()
{
	int choice_option;
	char * getoccupier(int), *p;
	int room_num;
	char username[41];
	
	printf("welcome to hotel desk\n");
	
	while(1)
	{
		printf("\n");
		menu();
		scanf("%d",&choice_option);
	
		while(getchar() !='\n')
			continue;

		if(choice_option == 1)
		{
			
			printf("choice roomnum(1~10) : ");
			scanf("%d", &room_num);
			while(getchar() != '\n')
				continue;

			p = getoccupier(room_num);
			printf("Room %2d, %s\n",room_num, p);
			continue;

		}
		else if(choice_option == 2)
		{
			printf("choice roomnum(1~10) : ");
			scanf("%d", &room_num);
			while(getchar() != '\n')
				continue;

			int i = freeroom(room_num);
			if(i > 0)
				printf("Room %2d is free\n",i);

		}
		else if(choice_option == 3)
		{
			printf("input name : ");
			fgets(username,40,stdin);
			for(int i=0; i<41;i++)
			{
				if(username[i] == '\n')
				{
					username[i] = '\0';
					break;
				}
			}
			username[40] = '\0';

			if(addguest(username) != 1)
			{
				printf("fail addguest\n");
			}
			else
			{
				printf("success addguest\n");
	
			}
		}
		else if(choice_option == 4)
		{
			if(findfree() != -1)
				printf("%d room is free\n",findfree());
		}
		else if(choice_option == 5)
		{
			printf("Thank you.\n");
			return 0;
		}
		else
		{
			printf("this is cannot execute option\n retry input option\n");
		}
	}
	
}

void menu()
{
	printf("\nMenu\n");
	printf("1.getoccupier (find user name)\n");
	printf("2.freeroom (delete resident)\n");
	printf("3.addguest (guest listup)\n");
	printf("4.findfree (find free roomnum)\n");
	printf("5.exit\n");
	printf("choice option(number): ");
}

