#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>



int main(int argc, char * argv[])
{
	int answer = 0;
	if(argc != 2)
	{
		printf("Usage : ./3.8 filename\n");
		return 0;
	}

	if(access(argv[1], W_OK) == -1)
	{
		printf("can not write permission\n");
		printf("do you want delete this file?\n");
		printf("(1.yes 2.no) : ");
		scanf("%d", &answer);
		if(answer == 1)
			printf("OK delete now\n");
		else
		{
			printf("cancel delete\n");
			return 0;
		}
	}

	if(unlink(argv[1]) == -1)
	{
		printf("fail  to unlink\n");
		return -1;
	}

	printf("Success unlink\n");
	return 1;


}
