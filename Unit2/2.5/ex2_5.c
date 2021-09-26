#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


#define BUFSIZE 512

int main()
{
	char buffer[BUFSIZE];
	int filedes;

	ssize_t nread;
	long total = 0;

	long words = 0;
	long sentences = 0;

	if((filedes = open("anotherfile",O_RDONLY)) == -1)
	{
		printf("error in opening anotherfile\n");
		exit(1);
	}

	while((nread = read(filedes, buffer, BUFSIZE)) > 0)
	{
		total += nread;
		for(int i=0; i<nread;i++)
		{
			if(buffer[i] == '\t' || buffer[i] == '\n' || buffer[i] == ' ')
				words++;

			if(buffer[i] == '\n' || buffer[i] == '\0')
				sentences++;
		}

	}

	printf("total chars in anotherfile: %ld\n", total);
	printf("total words in anotherfile: %ld\n",words);
	printf("total sentences in anotherfile: %ld\n", sentences);
	exit(0);
}
