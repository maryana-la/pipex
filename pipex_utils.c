#include "pipex.h"

void	fd_init(t_pipex *pip, int argc, char **argv)
{
	if (pip->flag == 2)
	{
		if (argc != 5)
		{
			ft_putstr_fd("Wrong number of arguments\n", 1);
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
			ft_putstr_fd("Bonus: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 1);
			exit(1);
		}
	}
	pip->fd_in = open(argv[1], O_RDONLY);
	if (pip->fd_in < 0 || read(pip->fd_in, 0, 0) < 0)
		ft_error_exit(argv[1], pip, FILE_ERR);
	pip->fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (pip->fd_out < 0 || (access(argv[argc - 1], W_OK) == -1))
		ft_error_exit(argv[argc - 1], pip, FILE_ERR);
	pip->fd_tmp = 0;
	pip->arg_count = argc;
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		if (arr[i])
			free(arr[i]);
	free(arr);
}

void	ft_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
}

void	ft_error_exit (char *str, t_pipex *pip, int err)
{
	perror(str);
	if (pip->flag == 1)
	{
		if (unlink("tmp_file") == -1)
			perror("unlink");
	}
	exit (err);
}
