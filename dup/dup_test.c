#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		fd_copy;
	int		reader;
	char	buffer[15];

	//print the pricess' PID for reference
	printf("My PID is %d\n", getpid());
	//open the file and get the fd
	fd = open("test.txt", O_RDONLY);
	if (!fd)
		return (1);
	//duplicate that fd to the smallest unused fd
	fd_copy = dup(fd);
	if (!fd_copy)
		return (1);
	//read from fd
	reader = read(fd, buffer, 10);
	if (reader == -1)
		return (1);
	buffer[reader] = '\0';
	printf("fd %d contains: %s\n", fd, buffer);
	//read from fd copy
	reader = read(fd_copy, buffer, 10);
	if (reader == -1)
		return (0);
	buffer[reader] = '\0';
	printf("fd %d contains: %s\n", fd_copy, buffer);
	//infinite loop to be able to go check the open fds
	//by this process with ls -la /proc/PID/fd
	while (1)
		;
}