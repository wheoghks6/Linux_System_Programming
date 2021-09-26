#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#define SIZE 512

int main(int argc, char * argv[])
{
	ssize_t nread;
	char buf[SIZE];
	if(argc < 2)
	{
		while((nread = read(0,buf,SIZE)) > 0)
			write(1,buf,nread);

		exit(0);
	}
	else
	{
		int filedes;
		for(int i=1; i<argc; i++)
		{
			if((filedes = open(argv[i],O_RDONLY)) < 0 )
			{
				printf("can not open %d :  %s \n",i, argv[i]);
				continue;
			}
			
			while((nread = read(filedes,buf,SIZE)) > 0)
				write(1,buf,nread);

			puts("");
			
		}
	}
}
