#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef FD
# define FD 1023
#endif

int	main(void)
{
	int	fd1;
	int	fd2;
	char	*line;
	int		i;

	fd1 = open("test_m9.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("open() failed.\n");
		return (-1);
	}
	if (FD < 0)
	{
		printf("FD is nagative value.");
		return (-1);
	}
	else if (FD >= 0 && FD <= 2)
		fd2 = FD;
	else
	{
		fd2 = dup2(fd1, (int)FD);
		if (fd2 == -1)
		{
			printf("dup2() failed.\n");
			return (-1);
		}
	}
	// printf("fd2 = %d\n", fd2);
	i = 0;
	line = get_next_line(fd2);
	while (line != NULL)
	{
		printf("%d: %s", i, line);
		free (line);
		line = get_next_line(fd2);
		i++;
	}
	close(fd2);
	close(fd1);
	return (0);
}
