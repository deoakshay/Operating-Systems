#include <linux/module.h>    
#include <linux/kernel.h>    
#include <linux/init.h>      

#include <linux/proc_fs.h>   
#include <linux/seq_file.h> 
#include <linux/mm.h>       

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akshay Deo");
MODULE_DESCRIPTION("Display Pagefaults");

const char file_name[] = "num_pagefaults";

static struct proc_dir_entry* page_fault_no; 

static int pagefault_dis(struct seq_file *file_name, void *v)
{
    unsigned long stats_buffer[NR_VM_EVENT_ITEMS];
    all_vm_events(stats_buffer);
    seq_printf(file_name,"The page fault module has beed inserted and the page faults are:\n");
    seq_printf(file_name, "%lu\n", stats_buffer[PGFAULT]);
    return 0;
}

static int pagefault_list(struct inode *inode, struct file *file)
{
    return single_open(file, pagefault_dis, NULL);
} 

static const struct file_operations pagefault_fileop = {
    .owner    = THIS_MODULE,
    .open     = pagefault_list,
    .read     = seq_read,        
    .llseek   = seq_lseek,       
    .release  = single_release,  
};

static int __init pagefaultd(void)
{
   printk("Entering personal module for page fault display:\n"); 
   page_fault_no = proc_create(file_name,0,NULL,&pagefault_fileop);
    return 0;
}

static void __exit pagefaultc(void)
{
    printk("Exiting personal module for page fault display!!\n");
    remove_proc_entry(file_name,NULL);
}

module_init(pagefaultd);
module_exit(pagefaultc);

/*
Reference:
1. https://www.linux.com/learn/linux-training/39972-kernel-debugging-with-proc-qsequenceq-files-part-2-of-3
2. https://github.com/CSUChico-CSCI340/CSCI340-KernelHacking*/

