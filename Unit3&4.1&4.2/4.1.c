#include<dirent.h>
#include<stdio.h>
int my_double_ls(const char * name, int skip)
{
	struct dirent *d;
	DIR *dp;

	if((dp = opendir(name)) == NULL)
		return -1;

	if(skip == 0)
	{
		while(d = readdir(dp))
		{
			if(d->d_ino != 0)
				printf("%s\n",d->d_name);
		}
		rewinddir(dp);

		while(d = readdir(dp))
		{
			if(d->d_ino != 0)
				printf("%s\n",d->d_name);
		}
	}

	else if(skip == 1)
        {
                while(d = readdir(dp))
                {
                        if(d->d_ino != 0 && d->d_name[0] != '.')
                                printf("%s\n",d->d_name);
                }
                rewinddir(dp);

                while(d = readdir(dp))
                {
                        if(d->d_ino != 0 && d->d_name[0] !='.')
                                printf("%s\n",d->d_name);
                }
        }


	closedir(dp);
	return 0;
}

int main(int argc, char * argv[])
{

	if(argc < 3)
	{
		printf("Usage : ./4.1 dir_name skip\n");
		return 1;
	}

	if(argv[2][0] == '0')
	{
		my_double_ls(argv[1],0);
	}
	else if(argv[2][0] == '1')
	{
		my_double_ls(argv[1],1);
	}
}
