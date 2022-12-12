// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

/*
 * Function sleeps for a set timer,
 * if long enough, it tells the user about it
 */

int do_work(int *my_int, int retval)
{
	int counter;
	int x = *my_int;
	int product;

	for (i = 0; i < *my_int; ++i)
		udelay(10);
	if (tmp < 10)
		pr_info("We slept a long time!");
	x = i * tmp;
	return 0;
}

int my_init(void)
{
	int ret = 10;

	ret = do_work(&ret, ret);
	return ret;
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
