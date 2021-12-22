#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/bug.h>

MODULE_AUTHOR("Oleksii Krasnovskyi <finchatticu33@gmail.com>");
MODULE_DESCRIPTION("Lab 5");
MODULE_LICENSE("Dual BSD/GPL");

struct list_node {
	struct list_node *next;
	ktime_t time;
};

static struct list_node *head = NULL;

static int quantity = 1;
module_param(quantity, uint, S_IRUGO);
MODULE_PARM_DESC(quantity, "quantity of 'Hello, world!'	printed by this module");

static int __init hello_init(void)
{
	uint i;

	struct list_node *t, *temp;

	if (quantity == 0)
	{
		printk(KERN_WARNING "quantity == 0");
	}
	else if (quantity >= 5 && quantity <= 10)
	{
		printk(KERN_WARNING "quantity is in [5; 10] range");
	}
	BUG_ON(quantity > 10);

	for (i = 0; i < quantity; ++i)
	{
		t = kmalloc(sizeof(struct list_node), GFP_KERNEL);
		if (i == 4) 
		{
			t = NULL;
		}
		t->time = ktime_get();
		printk(KERN_EMERG "Hello, world\n");
		if (head == NULL) 
		{
			head = t;
			head->next = NULL;
		} 
		else
		{
			temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = t;
			t->next = NULL;
		}	
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct list_node *temp;
	while (head != NULL)
	{
		temp = head;
		printk(KERN_INFO "Time: %lld\n", head->time);
		head = head->next;
		kfree(temp);
	}
}

module_init(hello_init);
module_exit(hello_exit);

