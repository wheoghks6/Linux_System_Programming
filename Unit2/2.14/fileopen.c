#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int fileopen(char* filename, char * mode);

int main(int argc, char * argv[])
{
	int filedes;
	if( argc < 3)
	{
		printf("Usage : fileopen target mode\n");
		return -1;
	}
	
	
	 filedes = fileopen(argv[1], argv[2]);
	printf("%s file des : %2d\n",argv[1], filedes);
	return filedes;
}

int fileopen(char * filename, char * mode)
{
	int filedes;
	if(strncmp(mode,"rw",2) == 0)
	{
		printf("%s open mode 'rw'\n",filename);
		filedes = open(filename, O_RDWR | O_CREAT, 0644);
	}
	else if(strcmp(mode, "w") == 0)
	{
		printf("%s open mode 'w'\n",filename);
		filedes = open(filename, O_WRONLY | O_CREAT, 0644);
	}
	else if(strcmp(mode, "r") == 0)
	{
		printf("%s open mode 'r' \n",filename);
		filedes = open(filename, O_RDONLY);
	}
	else if(strcmp(mode,"a") == 0)
	{
		printf("%s open mode 'a' \n",filename);
		filedes = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else
	{
		printf("%s open fail\n",filename);
		return -1;
	}
	return filedes;
}
