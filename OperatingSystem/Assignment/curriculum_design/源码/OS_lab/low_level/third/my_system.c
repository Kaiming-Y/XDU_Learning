#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/unistd.h>
#include<linux/module.h>
#include<linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");
#define SYS_CALL_TABLE_ADDRESS 0xffffffffacc00380 // 每次开机会变化 
#define NUM 295
unsigned long *my_sys_call_table;

static int (*funcPtr)(void);

int old_cr0;

static int clear_cr0(void){
	unsigned int cr0;
	unsigned int ret;
	asm volatile("movq %%cr0,%%rax":"=a"(cr0));
	ret=cr0;
	cr0&=0xfffffffffffeffff;
	asm volatile("movq %%rax,%%cr0"::"a"(cr0));
	return ret;
}
static void setback_cr0(int v){
	asm volatile("movq %%rax,%%cr0"::"a"(v));
}
asmlinkage int  my_sys_call(struct pt_regs* regs){
	printk("the systemcall of the module....\n");
	int sid;
	sid=regs->di;
	int flag;
	flag=regs->si;
	int res=0;
	printk("the argument sid= %d,flag=%d\n",sid,flag);
	if(flag){
		res=sid/10%10;
	}else{
		res=sid%10;
	}
	printk("result=%d\n",res);
	return res;
}

static int __init call_init(void){
	printk("call init....\n");
	my_sys_call_table=(unsigned long*)SYS_CALL_TABLE_ADDRESS;
	funcPtr=( int(*)(void))my_sys_call_table[NUM];
	old_cr0=clear_cr0();
	my_sys_call_table[NUM]=(unsigned long)&my_sys_call;
	setback_cr0(old_cr0);
	return 0;
}
static void __exit call_exit(void){
	printk("call exit....\n");
	old_cr0=clear_cr0();
	my_sys_call_table[NUM]=(unsigned long)funcPtr;
	setback_cr0(old_cr0);
}

module_init(call_init);
module_exit(call_exit);
