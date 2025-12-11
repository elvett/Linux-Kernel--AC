// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include "hello1.h"

MODULE_AUTHOR("Egor Priymak");
MODULE_DESCRIPTION("Training module part 1");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(my_list);

static int fake_fail_at = 5;
static int call_count;

void print_hello(int n)
{
	struct my_struct *node;

	call_count++;

	if (call_count == fake_fail_at) {
		pr_err("hello1: simulated kmalloc() returned 0 on call %d\n",
		       call_count);
		return;
	}

	node = kmalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return;

	node->start_time = ktime_get();

	pr_info("Hello, world! (%d)\n", n);

	udelay(10);

	node->end_time = ktime_get();

	list_add_tail(&node->list, &my_list);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct my_struct *node, *tmp;
	s64 delta;

	list_for_each_entry_safe(node, tmp, &my_list, list) {
		delta = ktime_to_ns(ktime_sub(node->end_time,
					      node->start_time));

		pr_info("Time for print: %lld ns\n", delta);

		list_del(&node->list);
		kfree(node);
	}

	pr_info("hello1 unloaded\n");
}

static int __init hello1_init(void)
{
	pr_info("hello1 loaded\n");
	return 0;
}

module_init(hello1_init);
module_exit(hello1_exit);

