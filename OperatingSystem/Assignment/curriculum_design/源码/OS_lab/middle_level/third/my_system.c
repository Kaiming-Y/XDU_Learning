#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/unistd.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/mutex.h>
#include<linux/export.h>
#include<linux/delay.h>
#include<linux/mm.h>
#include<linux/mm_types.h>

MODULE_LICENSE("Dual BSD/GPL");
#define SYS_CALL_TABLE_ADDRESS 0xffffffff87800380
#define NUM 295
unsigned long *my_sys_call_table;

static int (*funcPtr)(void);

int old_cr0;


struct mutex lock;

int gOSE;
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
	mutex_lock(&lock);
	printk("the systemcall of the module....\n");
	int sid;
	gOSE=sid=regs->di;
	int flag;
	flag=regs->si;
	int res=0;
	printk("the argument sid= %d,flag=%d\n",sid,flag);
	if(flag){
		printk("this is ^\n");
		gOSE=gOSE^0xffffffff;
	}else{
		printk("this is ~\n");
		gOSE=~gOSE;
	}
	printk("gOSE=%d\n",gOSE);
	unsigned long vaddr=&gOSE;
	printk("the virtual address of gOSE is 0x%lx",&gOSE);
	pgd_t* pgd;
	p4d_t* p4d;
	pud_t* pud;
	pmd_t* pmd;
	pte_t* pte;
	pgd = pgd_offset(current->mm,vaddr);  //第一个参数是当前进程的mm_struct结构（我们申请的线性地址空间是内核，所以应该查内核页表，又因为所有的进程都共享同一个内核页表，所以可以用当前进程的mm_struct结构来进行查找）
    printk("pgd_val = 0x%lx, pgd_index = %lu\n", pgd_val(*pgd),pgd_index(vaddr));
   	if (pgd_none(*pgd)){
        printk("not mapped in pgd\n");
        return -1;
    }

    p4d = p4d_offset(pgd, vaddr);  //查找到的页全局目录项pgd作为下级查找的参数传入到p4d_offset中
    printk("p4d_val = 0x%lx, p4d_index = %lu\n", p4d_val(*p4d),p4d_index(vaddr));
    if(p4d_none(*p4d))
    { 
        printk("not mapped in p4d\n");
        return -1;
    }

    pud = pud_offset(p4d, vaddr);
    printk("pud_val = 0x%lx, pud_index = %lu\n", pud_val(*pud),pud_index(vaddr));
    if (pud_none(*pud)) {
        printk("not mapped in pud\n");
        return -1;
    }
 
    pmd = pmd_offset(pud, vaddr);
    printk("pmd_val = 0x%lx, pmd_index = %lu\n", pmd_val(*pmd),pmd_index(vaddr));
    if (pmd_none(*pmd)) {
        printk("not mapped in pmd\n");
        return -1;
    }
 
    pte = pte_offset_kernel(pmd, vaddr);  //与上面略有不同，这里表示在内核页表中查找，在进程页表中查找是另外一个完全不同的函数   这里最后取得了页表的线性地址
    printk("pte_val = 0x%lx, ptd_index = %lu\n", pte_val(*pte),pte_index(vaddr));

    if (pte_none(*pte)) {
        printk("not mapped in pte\n");
        return -1;
    }
    unsigned long paddr = 0;
    unsigned long page_addr = 0;
    unsigned long page_offset = 0;
    //从页表的线性地址中取出该页表所映射页框的物理地址
    page_addr = pte_val(*pte) & PAGE_MASK;    //取出其高48位
    //取出页偏移地址，页偏移量也就是线性地址中的低12位
    page_offset = vaddr & ~PAGE_MASK;
    //将两个地址拼接起来，就得到了想要的物理地址了
    paddr = page_addr | page_offset;
    printk("page_addr = %lx, page_offset = %lx\n", page_addr, page_offset);
    printk("vaddr = %lx, paddr = %lx\n", vaddr, paddr);
   
	mutex_unlock(&lock);
	return res;
}

static int __init call_init(void){
	printk("call init....\n");
	my_sys_call_table=(unsigned long*)SYS_CALL_TABLE_ADDRESS;
	funcPtr=( int(*)(void))my_sys_call_table[NUM];
	old_cr0=clear_cr0();
	my_sys_call_table[NUM]=(unsigned long)&my_sys_call;
	setback_cr0(old_cr0);
	
	mutex_init(&lock);
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
