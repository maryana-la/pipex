#include "pipex.h"

// ./pipex Makefile rev nl outfile
// ./pipex tolstoy.txt rev nl outfile
// ./pipex Makefile "cat -e" outfile
// ./pipex libft rev nl outfile
// chmod 000 outfile
// ./pipex Makefile rev nl outfile
// ./pipex Makefile rev nsdfl outfile

static void	call_child(t_pipex *pip, int i, char **argv, char **env)
{
	if (i == 2)
	{
		dup2(pip->fd_in, 0);
		dup2(pip->fds[1], 1);
	}
	else if (i == 3)
	{
		dup2(pip->fd_tmp, 0);
		dup2(pip->fd_out, 1);
	}
	close(pip->fds[0]);
	close(pip->fds[1]);
	pip->path = get_data_path(argv[i], env, pip);
	if (execve(pip->path, pip->arg_data, env) == -1)
	{
		ft_free_line(pip->path);
		ft_free_array(pip->arg_data);
		ft_putstr_fd(argv[i], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit(4);
	}
	ft_free_line(pip->path);
	ft_free_array(pip->arg_data);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	t_pipex	pip;
	int		i;

	pip.flag = 2;
	fd_init(&pip, argc, argv);
	i = 1;
	while (++i < 4)
	{
		pipe(pip.fds);
		pid = fork();
		if (pid == -1)
			ft_error_exit("fork", FORK_ERR);
		else if (pid == 0)
			call_child(&pip, i, argv, env);
		close (pip.fds[1]);
		pip.fd_tmp = pip.fds[0];
	}
	waitpid(pid, 0, 0);
	close(pip.fds[0]);
	close(pip.fds[1]);
	close(pip.fd_in);
	close(pip.fd_out);
	return (0);
}
