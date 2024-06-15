#include<stdio.h>
#include<stdlib.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	int flag=1;
	int x=syscall(295,817,flag);
	printf("flag : %d,the syscall result is %d\n",flag,x);
	x=syscall(295,817,(flag=0));
	printf("flag : %d,the syscall result is %d\n",flag,x);
	return 0;
}
