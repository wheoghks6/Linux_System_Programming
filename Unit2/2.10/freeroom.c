#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define NAMELENGTH 41

char namebuf[NAMELENGTH];

int freeroom(int roomno)
{
	off_t offset;
	ssize_t nwrite;
	int infile;

	if((infile=open("residents", O_WRONLY)) == -1)
	{
		printf("freeroom func fail open residents\n");
		return -1;
	}
	
	offset = (roomno - 1) * NAMELENGTH;

	if(lseek(infile, offset, SEEK_SET) == -1)
		return -1;


	for(int i=0; i<NAMELENGTH; i++)
	{
		namebuf[i] = '\0';
	}

	if((nwrite = write(infile, namebuf, NAMELENGTH) ) <=0)
	{
		printf("freeroom func write fail\n");
		return -1;
	}

	return roomno;
}
