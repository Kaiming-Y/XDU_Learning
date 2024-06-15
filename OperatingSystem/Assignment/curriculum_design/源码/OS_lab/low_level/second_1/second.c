#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
int main(int argc,char* argv[]){
	char* filepath=argv[1];
	char* operate=argv[2];
	int fd=open(filepath,O_CREAT|O_RDWR);
	char buff[50];
	if(strcmp("write",operate)==0){
		printf("Input what you want to input:\n");
		read(0,buff,30);
		size_t res=write(fd,buff,strlen(buff));
		if(res<0){
			printf("fail to write!\n");
		}
	}else if(strcmp("read",operate)==0){
		size_t res=read(fd,buff,30);
		if(res<0){
			printf("fail to read!\n");
		}
		printf("the content of the file is:");
		fprintf(stdout," %s",buff);
		//write(1,buff,strlen(buff));
	}
}
