#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ioctl.h>
#include"test_cmd.h"
#define MAX_SIZE 1024
#define MY_DEVICE_NAME "/dev/lumos_cdev"
int main(){
        int fd=open(MY_DEVICE_NAME,O_RDWR);
        if(fd!=-1){
                char write_buff[]="I am from user\n";
                char read_buff[1024];
                int ret=0;
                //test the first read is id 
                read(fd,read_buff,1024);
                printf("read_buff : %s\n",read_buff);
                
                //test write and read
                printf("-------test write and read-------\n");
                if(ret=write(fd,write_buff,strlen(write_buff))){
                	printf("write successfully!\n");
                }
                read(fd,read_buff,1024);
                printf("read_buff : %s\n",read_buff);

            	                
                //test read old by ioctl
                printf("-------test read old by ioctl-------\n");
                ioctl(fd,READ_OLD,read_buff);
                printf("get ori_rwbuff : %s\n",read_buff);
                
                
                //test read new by ioctl
                printf("-------test read new by ioctl-------\n");
                write(fd,"test read by ioctl",19);
                ioctl(fd,READ_NEW,read_buff);
                printf("get new_rwbuff :%s\n",read_buff);
                
                //clear
                printf("-------test clear by ioctl-------\n");
                ioctl(fd,RW_CLEAR);
               	read(fd,read_buff,1024);
                printf("read_buff : %s\n",read_buff);
      

        }else{
                printf("fail to open %s",MY_DEVICE_NAME);
        }
        close(fd);

	return 0;
}
