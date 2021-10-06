#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

char re[4] = "";
void lsoct(char * str)
{
	int result[4] = {0,};
	int index = 1;
	for(int i=0; i<9; )
	{
		int value = 0;
		for(int j=0; j<3;j++)
		{
			if(str[i+j] == 'r')
			{
				value +=4;
			}
			if(str[i+j] == 'w')
			{
				value +=2;
			}
			if(str[i+j] == 'x')
			{
				value +=1;
			}
			else
				continue;

		}
		result[index++] = value;
		i = i+3;

	}
	snprintf(re,5,"0%d%d%d",result[1],result[2],result[3]);
	return;
}



int main(int argc, char * argv[])
{
	long permission = 0;
	umask(0000);
	if(argc < 3)
	{
		printf("Usage : ./3.7 filename permission\n");
		return -1;
	}

	if(strlen(argv[2]) == 9)
	{
		lsoct(argv[2]);
		permission = strtol(re,0,8);
	}
	else if(strlen(argv[2]) != 4)
	{
		printf("error permission\n");
		return -1;
	}
	else
	{
		permission = strtol(argv[2], 0, 8);
	}

	if(chmod(argv[1], permission) == -1)
		perror("call to chmmode falled\n");
	else
		printf("chmode success\n");

}
