// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Egor Priymak");
MODULE_DESCRIPTION("Training module");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!'");

struct my_struct {
	struct list_head list;
	ktime_t timestamp;
	};

static LIST_HEAD(my_list);

static int __init hello_init(void)
{
	int i;
	struct my_struct *node;

	if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
		pr_warn("Warning: print_count=%u (unusual value)\n", print_count);
	} else if (print_count > 10) {
		pr_err("Error: print_count=%u is too large\n", print_count);
	return -EINVAL;
	}

	for (i = 0; i < print_count; i++) {
		node = kmalloc(sizeof(*node), GFP_KERNEL);
		if (!node)
			return -ENOMEM;
		node->timestamp = ktime_get();
		list_add_tail(&node->list, &my_list);
		pr_info("Hello, world! (%d)\n", i + 1);
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct my_struct *node, *tmp;
	list_for_each_entry_safe(node, tmp, &my_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(node->timestamp));
		list_del(&node->list);
		kfree(node);
}
}

module_init(hello_init);
module_exit(hello_exit);
