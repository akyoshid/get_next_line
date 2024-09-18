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
	int	fd3;
	int	fd4;
	int	fd5;
	int	fd6;
	int	fd7;
	int	fd8;
	char	*line;

	fd1 = open("test_b1.txt", O_RDONLY);
	fd2 = open("test_b2.txt", O_RDONLY);
	fd3 = open("test_b3.txt", O_RDONLY);
	fd4 = open("test_b4.txt", O_RDONLY);
	fd5 = open("test_b5.txt", O_RDONLY);
	fd6 = open("test_b6.txt", O_RDONLY);
	fd7 = open("test_b7.txt", O_RDONLY);
	fd8 = open("test_b8.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1
		|| fd5 == -1 || fd6 == -1 || fd7 == -1 || fd8 == -1)
	{
		printf("open() failed.\n");
		return (-1);
	}
	if (fd1 == FD || fd2 == FD || fd3 == FD || fd4 == FD
		|| fd5 == FD || fd6 == FD || fd7 == FD || fd8 == FD || FD <= 2)
	{
		printf("FD is an unacceptable value.");
		return (-1);
	}
	else
	{
		fd8 = dup2(fd8, (int)FD);
		if (fd8 == -1)
		{
			printf("dup2() failed.\n");
			return (-1);
		}
	}
	printf("fd8 = %d\n", fd8);
	line = get_next_line(fd1);
	while (line != NULL)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd2);
		while (line != NULL)
		{
			printf("%s", line);
			free (line);
			line = get_next_line(fd3);
			while (line != NULL)
			{
				printf("%s", line);
				free (line);
				line = get_next_line(fd4);
				while (line != NULL)
				{
					printf("%s", line);
					free (line);
					line = get_next_line(fd5);
					while (line != NULL)
					{
						printf("%s", line);
						free (line);
						line = get_next_line(fd6);
						while (line != NULL)
						{
							printf("%s", line);
							free (line);
							line = get_next_line(fd7);
							while (line != NULL)
							{
								printf("%s", line);
								free (line);
								line = get_next_line(fd8);
								while (line != NULL)
								{
									printf("%s", line);
									free (line);
									line = get_next_line(fd8);
								}
								close(fd8);
								line = get_next_line(fd7);
							}
							close(fd7);
							line = get_next_line(fd6);
						}
						close(fd6);
						line = get_next_line(fd5);
					}
					close(fd5);
					line = get_next_line(fd4);
				}
				close(fd4);
				line = get_next_line(fd3);
			}
			close(fd3);
			line = get_next_line(fd2);
		}
		close(fd2);
		line = get_next_line(fd1);
	}
	close(fd1);
	return (0);
}
