// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>

int	main(void)
{
	char buf[10];
	int	fd;
	int	ret;

	bzero(buf, 10);
	fd = open("/sys/kernel/debug/fortytwo/id", O_RDONLY);
	if (fd > 0)
	{
		printf("\n__ ID __\n");
		ret = read(fd, buf, 10);
		printf("1st read [%s] ret : %d\n", buf, ret);
		ret = read(fd, buf, 10);
		printf("2nd read [%s] ret : %d\n", buf, ret);
		ret = write(fd, "arlaine", 7);
		printf("1st write (arlaine, 7) ret : %d\n", ret);
		ret = write(fd, "aaaaa", 5);
		printf("2nd write (aaaaa, 5) ret : %d\n", ret);
		ret = write(fd, "aaabbbcccddd", 12);
		printf("3rd write (aaabbbcccddd, 12) ret : %d\n", ret);
		close(fd);
	}
	else
		dprintf(2, "No such file id\n");
	return (0);
}
