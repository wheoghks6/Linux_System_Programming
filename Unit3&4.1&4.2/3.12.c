#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char * argv[])
{
	struct stat statbuf;
	if(argc < 3)
	{
		printf("Usage : ./3.12 permission(oct) filename\n");
		return 1;
	}

	char oct_per[4] = {0,};

	if(strlen(argv[1]) == 4)
	{
		for(int i=0; i<4;i++)
		{
			oct_per[i] = argv[1][i];
		}
	}
	else if(strlen(argv[1]) == 3)
	{
		oct_per[0] = 0;
		for(int i=1;i<4;i++)
		{
			oct_per[i] = argv[1][i];
		}
	}
	else
	{
		printf("Usage : ./3.12 permission(oct) filename\n");
		printf("permission ex) 0777, 666\n");
	}

	
	if(stat(argv[2], &statbuf) == -1)
	{
		printf("Can not get stat \n");
		return 1;
	}

	long permission = 0;

	permission = strtol(oct_per, 0, 8);
	statbuf.st_mode = permission;

	if(chmod(argv[2], statbuf.st_mode) == -1)
	{
		printf("can not chmod \n");
		return 1;
	}
	else
	{
		printf("change permission success\n");
		return 1;
	}


}
