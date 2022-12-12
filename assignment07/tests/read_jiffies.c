// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>

int	main(void)
{
	char jbuf[64];
	int	fd;
	int	ret;

	bzero(jbuf, 64);
	fd = open("/sys/kernel/debug/fortytwo/jiffies", O_RDONLY);
	if (fd > 0)
	{
		printf("\n__ JIFFIES __\n");
		ret = read(fd, jbuf, 64);
		jbuf[ret - 1] = 0x0;
		printf("read [%s] ret : %d\n", jbuf, ret);
	}
	else
		dprintf(2, "No such file jiffies\n");
	return (0);
}
