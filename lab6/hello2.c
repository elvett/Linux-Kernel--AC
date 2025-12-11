// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/bug.h>

#include "hello1.h"

MODULE_AUTHOR("Egor Priymak");
MODULE_DESCRIPTION("Training module part 2");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);

static int __init hello2_init(void)
{
	int i;

	if (print_count == 0 ||
	    (print_count >= 5 && print_count <= 10))
		pr_warn("Strange repeat: %u is suspicious\n", print_count);
	else if (print_count > 10)
		BUG_ON(print_count > 10);

	for (i = 0; i < print_count; i++)
		print_hello(i + 1);

	pr_info("hello2 module loaded\n");
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

