#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>
#include<stdlib.h>
#define MY_DEVICE_NAME "/dev/lumos_cdev"
#define MAX_SIZE 1024
int main(){
	int fd=open(MY_DEVICE_NAME,O_RDWR);
	if(fd!=-1){
		printf("succeed to open!\n");
		char*buff;
		char*mapBuf;
		buff=(char*)malloc(MAX_SIZE);
		printf("before mmap\n");
		mapBuf=mmap(NULL,MAX_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,fd,0);
		printf("after mmap\n");
		strcpy(mapBuf,"~~~lumos test mmap!\0");//write
		memset(buff,0,MAX_SIZE);
		strcpy(buff,mapBuf);//read
		//int fd1 = open("111.txt",O_CREAT|O_RDWR);
		//write(fd1,mapBuf,strlen(mapBuf));
		fprintf(stdout,"buff is %s\n",buff);
		memset(buff,0,MAX_SIZE);
		//read(fd,buff,MAX_SIZE);
		//printf("read result is %s\n",buff);
		//munmap(mapBuf,MAX_SIZE);	
		free(buff);	
	}else{
		printf("fail to open %s\n",MY_DEVICE_NAME);
	}
	close(fd);//!!!

	return 0;
}
