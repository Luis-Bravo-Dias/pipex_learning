#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	//printf("Fork here\n");
	pid = fork();
	if (pid == -1)
		return (1);
	//printf("\nFork successful!\n");
	if (pid == 0)
	{
		printf("Child: I'm the child, my internal pid is %d.\n", pid);
		//usleep(1000000); //sleep i second
		printf("Child: Done!\n");
	}
	else if (pid > 0)
	{
		printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
		//printf("Parent: Done!\n");
		while (1)
			usleep(1);
	}
	return (0);
}

//https://www.codequoi.com/en/pipex-reproducing-the-pipe-operator-in-c/