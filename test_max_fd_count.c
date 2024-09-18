#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(void)
{
	int	fd;
	int	dup_fd;
	int	max_fd;

	fd = open("test_m1.txt", O_RDONLY);
	dup_fd = fd;
	while (dup_fd != -1)
	{
		max_fd = dup_fd;
		dup_fd = dup(dup_fd);
	}
	// printf("OPEN_MAX:\t\t%d\n", OPEN_MAX); // Linux don't have this macro.
	// Maximum number of open files per process. (compile-time constant defined in header files)
	printf("sysconf(_SC_OPEN_MAX):\t%zu\n", sysconf(_SC_OPEN_MAX));
	// Maximum number of open files per process. (dynamically retrieved at runtime)
	printf("real max fd:\t\t%d\n", max_fd + 1);
	// Real maximun number of open files per process obtained by this program.
	return (0);
}
