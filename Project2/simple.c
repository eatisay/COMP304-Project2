#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

#include <linux/sched/signal.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Ege Berk & Emir");

static int p = 0;

void dfs(struct task_struct *task) {
	struct task_struct *child; 
	struct list_head *list; 
	
		printk(KERN_INFO "Name: %-20s\tProcess ID: %d\n", task->comm, task->pid);
	
	list_for_each(list, &task->children) {
		child = list_entry(list, struct task_struct, sibling);
		dfs(child);
	}
}

static int simple_init(void)
{
	struct task_struct* task;
	for_each_process(task){
	  	  if (task->pid == p){
			dfs(task);
		
		}
	}

	return 0;
}





 
static void simple_cleanup(void)
{
	printk(KERN_WARNING "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ...\n");
}

module_init(simple_init);
module_exit(simple_cleanup);
module_param(p, int, 0);
