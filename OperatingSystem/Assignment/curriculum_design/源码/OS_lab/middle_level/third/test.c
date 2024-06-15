#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/syscall.h>
int main(){
	int id=fork();
	if(id==0){
		printf("father\n");
		syscall(295,817,0);
	}else{
		printf("son\n");
		syscall(295,817,1);
	}

	return 	0;
}
