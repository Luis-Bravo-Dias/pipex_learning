#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	main(void)
{
	pid_t	pid;
	int		ends[2]; //end[0] read / end[1] wirte
	char	secret[30];
	int		reader;
	char	buffer[30];

	//create a pipe and error check
	if (pipe(ends) == -1)
		return (1);
	//create a child process
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		//child process
		close(ends[0]); //nothing we want to read, close pipe's read end
		printf("Child: I'm writing my secret in the pipe...\n");
		strcpy(secret, "I am your child, mwahaha!");
		write(ends[1], secret, strlen(secret));
		close(ends[1]); //done writing, close pipe's write end
		return (0);
	}
	else
	{
		//parent process
		close(ends[1]); //Nothing to write, close pipe's write end
		waitpid(pid, NULL, 0); //wait for child
		printf("Parent: I received my child. What is its secret?\n");
		reader = read(ends[0], buffer, 30);
		close(ends[0]); //read everything, close pipe's read end
		if (reader == -1)
			return (3);
		buffer[reader] = '\0';
		printf("Parent: Oh boy! The secret is: \"%s\"\n", buffer);
	}
}

//https://www.codequoi.com/en/pipex-reproducing-the-pipe-operator-in-c/