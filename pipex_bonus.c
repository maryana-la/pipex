#include "pipex.h"

int main(int argc, char *argv[], char **env)
{
	char **arg_data;
	char *path;
	char *line;
	int fd_in;
	int fd_out;
	int fd[2];
	pid_t pid;
	int fdd;
	int i;
	int flag;
	int ret;

	errno = 0;
	flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		flag = 1;
	if (flag == 0)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in < 0)
		{
			perror(argv[1]);
			exit(1);
		}
		fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else
		fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd_out < 0)
	{
		close(fd_in);
		perror(argv[argc - 1]);
		exit(1);
	}
	fdd = 0;
	i = 2;
	while (i < (argc - 1))
	{
		errno = 0;
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("open");
			exit(-1);
		}
		else if (pid == 0)
		{
			if (i == 2 && flag == 0)
				dup2(fd_in, 0);
			else if (i == 2 && flag == 1)
			{
				ret = 1;
				close(fd[0]);
				while (ret)
				{
					write(0, "pipex_heredoc> ", 15);
					ret = get_next_line(0, &line);
					if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) + 1) == 0)
					{
						free(line);
						break;
					}
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
				exit(0);
			}
			else
				dup2(fdd, 0);
			if (i + 2 != argc)
				dup2(fd[1], 1);
			else if (i + 2 == argc)
				dup2(fd_out, 1);
			close(fd[0]);
			path = get_data_path(argv[i], env, &arg_data);
			if (execve(path, arg_data, env) < 0)
			{
				free(path);
				ft_free_array(arg_data);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(" : command not found\n", 2);
				exit (-1);
			}
			exit(0);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
	return(3);
}