#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define MY_DEVICE_NAME "/dev/lumos_cdev"
#define MAX_SIZE 1030
int main(){
	int fd=open(MY_DEVICE_NAME,O_RDWR);
	if(fd!=-1){
		char rubb[MAX_SIZE];
		for(int i=0;i<MAX_SIZE;i++){
			rubb[i]='z';
		}
		rubb[MAX_SIZE-1]='\0';//in fact ,write bytes is 1029
		rubb[1023]='a';
		int size=strlen(rubb);
	//	printf("%d\n",size);
		int ret=write(fd,rubb,size);
		if(ret!=-1){
			printf("write rubb successfully!\n");
			char read_buff[MAX_SIZE];
			read(fd,read_buff,MAX_SIZE);
			printf("read_buff is %s\n",read_buff);
			printf("bytes is %ld",strlen(read_buff));
			
			
		}else{
			printf("fail to write rubb!\n");
		
		}
	
	}else{
		printf("fail to open %s\n",MY_DEVICE_NAME);
	}
	close(fd);

	return 0;
}
