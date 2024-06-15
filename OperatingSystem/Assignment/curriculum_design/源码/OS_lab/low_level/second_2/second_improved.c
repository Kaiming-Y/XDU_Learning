#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/mman.h>
int main(int argc,char* argv[]){
	char* filepath=argv[1];
	char* operate=argv[2];
	int fd=open(filepath,O_CREAT|O_RDWR,0666);
	char buff[50];
	if(strcmp("write",operate)==0){
		pid_t id=fork();
		sem_t* p = (sem_t*)mmap(NULL,sizeof(sem_t),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANON,-1,0); 
   	    sem_init(p,1,1); 
		if(id>0){
		//father
			sem_wait(p);
			char buff[]="817PROC1 MYFILE1\n";
			pid_t id=getpid();
			printf("[father] id=%d\n",id);
			write(fd,buff,strlen(buff));
			sem_post(p);			
		}else{
		//son
			sem_wait(p);
			char buff[]="817PROC2 MYFILE2\n";
			pid_t id=getpid();
			printf("[son] id=%d\n",id);
			write(fd,buff,strlen(buff));
			sem_post(p);
		}
		sem_destroy(p);
		munmap(p,sizeof(sem_t));

	}else if(strcmp("read",operate)==0){
		size_t res=read(fd,buff,100);
		printf("the numbers of read = %d\n",res);
		if(res<0){
			printf("fail to read!\n");
		}
		fprintf(stdout,"%s",buff);
		//write(1,buff,50);
	}
	close(fd);
}
