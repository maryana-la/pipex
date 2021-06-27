#include "pipex.h"

int pipex_bonus_2(int argc, char **argv, char **env)
{
	int ret;
	int fd_out;
	int fd[2];
	char *line;
	char *path;
	char **arg_data;
	pid_t pid;
	int fdd = 0;

	ret = 1;
	fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

	int i = 2;
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
			if (i == 2)
			{
				close(fd[0]);
				while (ret)
				{
					write(0, "pipex_heredoc> ", 14);
					ret = get_next_line(0, &line);
					if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) + 1) == 0)
						break;
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
				}
				exit(1);
			}
			else
				dup2(fdd, 0);
			if (i + 2 != argc)
				dup2(fd[1], 1);
			else if (i + 2 == argc)
				dup2(fd_out, 1);
			close(fd[0]);
			path = get_data_path(argv[i], env, &arg_data);
			execve(path, arg_data, env);
			exit(1);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
	exit (9);
}
