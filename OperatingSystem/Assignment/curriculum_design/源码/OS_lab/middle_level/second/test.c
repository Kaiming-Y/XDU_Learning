#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#define MAX_SIZE 1025
#define content1 "817PROC1 MYFILE1\n"
#define content2 "817PROC2 MYFILE2\n"
typedef struct mem_share{
	int turn;
}ms;
int main(int argc,char*argv[]){
	if(argc!=2){
		perror("error : the number of arguments fault!\n");
		return -1;
	}
	int fd=open(argv[1],O_CREAT|O_RDWR);
//	ftruncate(fd,sizeof(ms));
	if(fd==-1){
		perror("fail to open !\n");
		return -1;
	}
	ms* share_addr=(ms*)mmap(NULL,sizeof(ms),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);	
	share_addr->turn=0;
	int pid=fork();
	if(pid==0){
		printf("---------------father--------------\n");
		while(share_addr->turn!=1){}
		write(fd,content1,strlen(content1));
		share_addr->turn=0;
	}else{
		printf("---------------son------------------\n");
		while(share_addr->turn!=0){}
		write(fd,content2,strlen(content2));
		share_addr->turn=1;
	}
	munmap(share_addr,sizeof(ms));


	return 0;
}
