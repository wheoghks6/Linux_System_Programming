#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define NAMELENGTH 41

char namebuf[NAMELENGTH];

int findfree()
{
	off_t offset;
	ssize_t nread;
	int infile;
	char emptybuf[NAMELENGTH];
	if((infile=open("residents", O_RDONLY)) == -1)
	{
		printf("can not open residents\n");
		return -1;
	}
	
	offset = 0;

	if(lseek(infile, offset, SEEK_SET) == -1)
		return -1;


	int i=0;

	for(int i=0; i<NAMELENGTH;i++)
	{
		emptybuf[i] = '\0';
	}


	while((nread = read(infile, namebuf, NAMELENGTH) ) >0)
	{
		if(strncmp(emptybuf,namebuf,NAMELENGTH) == 0)
		{
			return i+1;
		}
		i++;
		if(i == 10)
		{
			printf("hotel rooms is full\n");
			return -1;
		}
				
	}
	return i+1;
}

