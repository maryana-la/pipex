#include "pipex.h"

int main(int argc, char *argv[], char **env)
{
	char **arg_data;
	char *path;

	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	int i = 0;
	while (i < (argc - 1))
	{
		pipe(fd);
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (i + 2 != argc)
				dup2(fd[1], 1);
			close(fd[0]);
//			execvp(cmd[i][0], cmd[i]);

			path = get_data_path(argv[i+1], env, &arg_data);
			execve(path, arg_data, env);
			exit(1);
		}
		else
		{
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
	return (0);
}