#include "pipex.h"

static void	read_from_stdin (t_pipex *pip, char *stop)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret)
	{
		write(0, "pipex_heredoc> ", 15);
		ret = get_next_line(0, &line);
		if (ft_strncmp(line, stop, ft_strlen(stop) + 1) == 0)
			break ;
		write(pip->fd_in, line, ft_strlen(line));
		write(pip->fd_in, "\n", 1);
		ft_free_line(line);
	}
	ft_free_line(line);
}

static void	heredoc_fd_init(t_pipex *pip, int argc, char **argv)
{
	pip->flag = 1;
	pip->arg_count = argc;
	pip->fd_in = open("tmp_file", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (pip->fd_in < 0 || read(pip->fd_in, 0, 0) < 0)
		ft_error_exit(argv[1], pip, FILE_ERR);
	read_from_stdin (pip, argv[2]);
	close (pip->fd_in);
	pip->fd_in = open("tmp_file", O_RDONLY);
	if (pip->fd_in < 0 || read(pip->fd_in, 0, 0) < 0)
		ft_error_exit("tmp_file", pip, FILE_ERR);
	pip->fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (pip->fd_out < 0 || (access(argv[argc - 1], W_OK) == -1))
		ft_error_exit(argv[argc - 1], pip, FILE_ERR);
	pip->fd_tmp = 0;
}

static void	call_child_bonus(t_pipex *pip, int i, char **argv, char **env)
{
	if ((i == 2 && pip->flag == 0) || (i == 3 && pip->flag == 1))
	{
		dup2(pip->fd_in, 0);
		close(pip->fd_in);
	}
	else
		dup2(pip->fd_tmp, 0);
	close(pip->fds[0]);
	if (i + 2 != pip->arg_count)
		dup2(pip->fds[1], 1);
	else if (i + 2 == pip->arg_count)
		dup2(pip->fd_out, 1);
	close(pip->fds[1]);
	pip->path = get_data_path(argv[i], env, pip);
	if (execve(pip->path, pip->arg_data, env) == -1)
	{
		ft_free_line(pip->path);
		ft_free_array(pip->arg_data);
		ft_putstr_fd(argv[i], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit (0);
	}
	ft_free_line(pip->path);
	ft_free_array(pip->arg_data);
	exit(0);
}

static int	close_fd_at_exit(t_pipex *pip)
{
	close(pip->fds[0]);
	close(pip->fds[1]);
	close(pip->fd_tmp);
	close (pip->fd_in);
	if (pip->flag == 1)
	{
		if (unlink("tmp_file") == -1)
			ft_error_exit("unlink", pip, FILE_ERR);
	}
	close(pip->fd_out);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	t_pipex	pip;
	int		i;

	pip.flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		heredoc_fd_init(&pip, argc, argv);
	else
		fd_init(&pip, argc, argv);
	i = 1;
	if (pip.flag == 1)
		i = 2;
	while (++i < (argc - 1))
	{
		pipe(pip.fds);
		pid = fork();
		if (pid == -1)
			ft_error_exit("fork", &pip, FORK_ERR);
		else if (pid == 0)
			call_child_bonus(&pip, i, argv, env);
		close(pip.fds[1]);
		pip.fd_tmp = pip.fds[0];
	}
	wait(NULL);
	return (close_fd_at_exit(&pip));
}
