#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
struct stat sb;
time_t time;
int fd;

void slowwatch(char * filename, time_t time)
{
        if(stat(filename, &sb) == -1 || sb.st_mtime != time){
                time = sb.st_mtime;
		printf("catch Change\n");
                printf("==================\n");
                char buf[1025];
                int read_size = 0;
                if((fd = open(filename, O_RDONLY)) < 0)
                {
                        printf("can not open file\n");
                        exit(1);
                }

                while((read_size = read(fd, buf, 1024))){
                        buf[read_size] = '\0';
                        printf("%s\n",buf);
                }
		close(fd);
                exit(1);
        }
}


int main(int argc, char * argv[])
{
	int j;
	if(argc != 2)
	{
		printf("Usage : ./3.10 filename\n");
		return 0;
	}

	fd = open(argv[1], O_RDONLY | O_CREAT, 0644);
	fd = close(fd);

	if(stat(argv[1],&sb) == -1){
		printf("can not find file %s stat\n",argv[1]);
		return -1;
	}

	time = sb.st_mtime;

	while(1)
	{
		slowwatch(argv[1], time);
		sleep(1);
	}

}
