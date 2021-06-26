//
// Created by Ragwyle Chelsea on 6/26/21.
//
#include "pipex.h"

int pipex_bonus_2(int argc, char **argv, char **env)
{
	int ret;
	int fd_temp;
	int fd_out;
	int fds_pair[2];
	char *line;
	char *path;
	char **arg_data;
	char *out_name;

	ret = 1;
	out_name = argv[5];
	fd_temp = open("tmp_gnl", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	fd_out = open(out_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

	pipe(fds_pair);

	while (ret)
	{
		write(0, "pipe_heredoc> ", 14);
		ret = get_next_line(0, &line);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) + 1) == 0)
			break;
		write(fd_temp, line, ft_strlen(line));
		write (fd_temp, "\n", 1);
	}

	close(fd_temp);
	fd_temp = open("tmp_gnl", O_RDONLY);
	pid_t pid = fork();
	if (pid == 0)
	{
		close(fds_pair[0]);
		dup2(fd_temp, 0);
		close(fd_temp);
		dup2(fds_pair[1], 1);
		close(fds_pair[1]);
		path = get_data_path(argv[3], env, &arg_data);
		execve(path, arg_data, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			close(fds_pair[1]);
			dup2(fds_pair[0], 0);
			close(fds_pair[0]);
			dup2(fd_out, 1);
			path = get_data_path(argv[4], env, &arg_data);
			execve(path, arg_data, env);
		}
		else
		{
			close(fds_pair[0]);
			close(fds_pair[1]);
		}
	}
	waitpid(pid, 0, 0);
	exit (9);
}
