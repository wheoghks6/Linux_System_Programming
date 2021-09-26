#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "hotel.h"
#define NAMELENGTH 41

char namebuf[NAMELENGTH];

int addguest(char* name)
{
	off_t offset;
	ssize_t nwrite;

	int infile;

	if((infile=open("residents", O_WRONLY | O_CREAT,0644)) == -1)
	{
		printf("addgiest : can not open residents\n");
		return -1;
	}
	
	int roomno = findfree();
	printf("findfree() : %d\n",roomno);
	if(roomno < 0)
	{
		close(infile);
		printf("addguest : can not addguest, hotel is full\n");
		return -1;
	}	

	offset = (roomno - 1) * NAMELENGTH;

	if(lseek(infile, offset, SEEK_SET) == -1)
	{
		close(infile);
		printf("addguest : cannot lseek\n");
		return -1;
	}


	for(int i=0; i<NAMELENGTH; i++)
	{
		namebuf[i] = '\0';
	}

	strncpy(namebuf,name,strlen(name));

	if((nwrite = write(infile, namebuf, NAMELENGTH) ) <=0)
	{
		close(infile);
		printf("addguest : can not write residents\n");
		return -1;
	}
	close(infile);
	return 1;
}
