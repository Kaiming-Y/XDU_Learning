#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/ctype.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/uaccess.h>
#include<linux/mm.h>
#include<asm/io.h>
#include"test_cmd.h"
#define BUFF_SIZE 1024
#define id 817
#define ERROR 1
#define MY_DEVICE_NAME "lumos_cdev"

static char rwbuff[BUFF_SIZE+1]="817";
static int rwbufflen=4;
static char ori_rwbuff[BUFF_SIZE+1];
static int oribufflen=0;
static int inuse=0;

static int cdev_open(struct inode* i,struct file* f){
	printk("cdev_open is called!\n");
	printk("rwbuff  :  %s\n",rwbuff);
	printk("ori_rwbuff  :  %s\n",ori_rwbuff);
	if(inuse==0){
		inuse=1;
		try_module_get(THIS_MODULE);
		return 0;
	
	}
	return -1;
}
static int cdev_release(struct inode*i,struct file* f){
	printk("[lumos] device is released!\n");
	memset(ori_rwbuff,0,BUFF_SIZE);
	oribufflen=0;
	strcpy(rwbuff,"817");
	rwbufflen=4;
	inuse=0;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t cdev_write(struct file*f,const char* u_buff,size_t size,loff_t *l)
{
	ssize_t ret=0;
	printk("[lumos]cdev_write is called!\n");
	if(size>BUFF_SIZE){
		size=BUFF_SIZE;
		//u_buff[size]='\0';
	}
	//printk("before copy ori_rwbuff is %s\n",ori_rwbuff);
	//printk("before copy rwbuff is %s\n",rwbuff);
	strcpy(ori_rwbuff,rwbuff);
	printk("after copy ori_rwbuff is %s\n",ori_rwbuff);
	printk("after copy rwbuff is %s\n",rwbuff);
	oribufflen=rwbufflen;
//	printk("The content before the last modification is %s\n",ori_rwbuff);
	if(copy_from_user(rwbuff,u_buff,size)){
		printk(KERN_ERR"fail to copy from user_buff to rwbuff!\n");
		ret=0;
	}
	else{
		if(size==BUFF_SIZE){ rwbuff[size]='\0';}
		printk("write data is %s\n",rwbuff);
		printk("write byte is %d\n",strlen(rwbuff));
		ret=size;
		rwbufflen=size;
	}
	return ret;


}
static ssize_t cdev_read(struct file*f,char* u_buff,size_t size,loff_t* l){
	int ret=0;
	printk("[papa]cdev_read is called!\n");
	if(size>BUFF_SIZE) size=BUFF_SIZE;
	if(copy_to_user(u_buff,rwbuff,size+1)){
		printk(KERN_ERR"error:fail to copy to user_buff from rwbuff");
		ret=0;
	}else{
		printk("[cdev_read] rwbuff is %s\n",rwbuff);
		ret=size;
	}



	return ret;
}
static long cdev_ioctl(struct file* f,unsigned int cmd,unsigned long args){
	printk("[lumos]cdev_ioctl is calling!\n");
	int ret;
	switch(cmd){
		case RW_CLEAR:{
			memset(rwbuff,0,rwbufflen);
			rwbufflen=0;
			printk("successfully clear! now buff_len is %d\n",rwbufflen);	
			ret=1;
			
		};break;
		case READ_OLD:{
			if(copy_to_user((char*)args,ori_rwbuff,oribufflen)){
				printk("[READ_OLD]  copy_to_user fail\n");
				ret = EFAULT;
			}
			printk("[READ_OLD]  copy_to_user successfully!\n");
		};break;
		case READ_NEW:{
			if(copy_to_user((char*)args,rwbuff,rwbufflen)){
				printk("[READ_NEW]  copy_to_user fail\n");
				ret = EFAULT;
			}
			printk("[READ_NEW]  copy_to_user successfully!\n");
		
		};break;
		default:printk("error cmd!\n");
		 ret = - EINVAL;
		 break;	
	}





	return ret;
}
static int cdev_mmap(struct file *f,struct vm_area_struct* vma){
	vma->vm_flags=(VM_IO|VM_DONTEXPAND|VM_DONTDUMP);
	int ret=remap_pfn_range(vma,vma->vm_start,virt_to_phys(rwbuff)>>PAGE_SHIFT,vma->vm_end-vma->vm_start,vma->vm_page_prot);
	return ret;
}
static struct file_operations cdev_fops={
	.open = cdev_open,
	.release = cdev_release,
	.read = cdev_read,
	.write = cdev_write,
	.mmap = cdev_mmap,
	.unlocked_ioctl = cdev_ioctl,
	.owner = THIS_MODULE
};

static int __init chrdev_init(void){
	printk("cdev_init is called!\n");
	printk("hello,my id is %d\n",id);
	int ret=1;
	ret=register_chrdev(60,MY_DEVICE_NAME,&cdev_fops);
	if(ret != -1){
		printk("[lumos] device successfully initialized.\n");
	}else{
		printk("[lumos]  device failed when initializing.\n");
	}
	return ret;
}
static void __exit chrdev_exit(void){
	printk("dev_exit is called!\n");
	unregister_chrdev(60,MY_DEVICE_NAME);
	printk("[lumos]  device successfully removed.\n");

}








MODULE_LICENSE("GPL");
module_init(chrdev_init);
module_exit(chrdev_exit);
