#include<stdio.h>
#include<string.h>
void lsoct(char * str)
{
	int result[3] = {0,};
	int index = 0;
	for(int i=0; i<=8; )
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
	printf("result : %d%d%d\n",result[0],result[1],result[2]);
	return;
}

void octls(char * str)
{
	char result[9];
	int j=0;
	for(int i=0; i<3; i++)
	{
		if(str[i] == '0')
		{
			strncpy(&(result[j]),"---",3);
		}
		else if(str[i] == '1')
		{
			strncpy(&(result[j]),"--x",3);
		}
		else if(str[i] == '2')
		{
			strncpy(&(result[j]),"-w-",3);
		}
		else if(str[i] == '3')
		{
			strncpy(&(result[j]),"-wx",3);
		}
		else if(str[i] == '4')
		{
			strncpy(&(result[j]),"r--",3);
		}
		else if(str[i] == '5')
                {
                        strncpy(&(result[j]),"r-x",3);
                }
		else if(str[i] == '6')
                {
                        strncpy(&(result[j]),"rw-",3);
                }
 		else if(str[i] == '7')
                {
                        strncpy(&(result[j]),"rwx",3);
                }
		j = j+3;

	}
	printf("result : %s\n",result);
}
int main(int argc, char * argv[]){

	if(argc < 2)
	{
		printf("Usage : ./ex3_3 option permission\n");
	}

	if(strcmp(argv[1],"lsoct") == 0)
	{
		lsoct(argv[2]);
	}
	else if(strcmp(argv[1], "octls") == 0)
	{
		octls(argv[2]);
	}
	else
	{
		printf("Can not execute\n");
	}

}
