#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	int	fd;
	int	new_fd;

	fd = open("test_m1.txt", O_RDONLY);
	new_fd = fd;
	while (dup2(fd, ++new_fd) != -1)
		close(new_fd);
	printf("The maximum integer value that can be used as a file descriptor : %d\n", new_fd - 1);
	close(fd);
	return (0);
}
