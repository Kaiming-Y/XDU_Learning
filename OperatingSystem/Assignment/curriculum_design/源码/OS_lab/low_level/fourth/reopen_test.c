#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define MY_DEVICE_NAME "/dev/lumos_cdev"
int main(){
	int fd=open(MY_DEVICE_NAME,O_RDWR);
	if(fd!=-1){
		printf("open successfully!\n");
		fd=open(MY_DEVICE_NAME,O_RDWR);
		if(fd==-1){
			printf("fail to reopen\n");
		}
	}
	close(fd);

	return 0;
}
