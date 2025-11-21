#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct my_struct {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

void print_hello(int n);

#endif

