#include<stdio.h>
#include<unistd.h>

void whatable(char * filename)
{
	char * target = filename;

	if(access(target, R_OK) == -1)
	{
		perror("can not read");
	}
	else
	{
		printf("%s readable, proceeding\n",target);
	}
	
	if(access(target, W_OK) == -1)
	{
		perror("can not write");
	}
	else
	{
		printf("%s writeable, proceeding\n",target);
	}

	if(access(target, X_OK) == -1)
	{
		perror("can not execute");
	}
	else
	{
		printf("%s executable, proceeding\n",target);
	}
}

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Usage : ./3.6 filename\n");
		return 0;
	}
	
	whatable(argv[1]);
}
