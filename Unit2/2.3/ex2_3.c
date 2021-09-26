#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main()
{
   int newfile = creat("abc",0644);

   int fileread;
   int filewrite;

   if((fileread = open("abc",O_RDONLY)) < 0 )
   {
	   printf("read open fail\n");
   }
   else{
   	printf("read open success\n");
   }

   if((filewrite = open("abc",O_WRONLY)) < 0)
   {
	printf("write open fail\n");
   }
   else
   {
	   printf("write open success\n");
   }

}
