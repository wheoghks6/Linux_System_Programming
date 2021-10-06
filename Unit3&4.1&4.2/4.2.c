#include<dirent.h>
#include<stdio.h>
#include<sys/stat.h>

int my_double_ls(const char * name)
{
	struct dirent *d;
	DIR *dp;
	struct stat buf;
	char * str;
	if((dp = opendir(name)) == NULL)
		return -1;

	

	while(d = readdir(dp))
	{
                if(d->d_ino != 0)
                {
			sprintf(str,"%s/%s",name,d->d_name);
                        if(stat(str, &buf) == -1)
			{
				printf("stat error\n");
				continue;
			}
                 

                        if(S_ISDIR(buf.st_mode))
                                printf("%s*\n",d->d_name);
                        else
                                printf("%s\n",d->d_name);
		}
	}
	rewinddir(dp);

	while(d = readdir(dp))
        {
                if(d->d_ino != 0)
                {
                        sprintf(str,"%s/%s",name,d->d_name);
                        if(stat(str, &buf) == -1)
                        {
                                printf("stat error\n");
                                continue;
                        }


                        if(S_ISDIR(buf.st_mode))
                                printf("%s*\n",d->d_name);
                        else
                                printf("%s\n",d->d_name);
                }
        }

	closedir(dp);
	return 0; 
}

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Usage : ./4.2 dir_name\n");
		return 1;
	}
	my_double_ls(argv[1]);
	return 0;
}
