#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "libft/libft.h"

# define FILE_ERR	2
# define FORK_ERR	3
# define MALLOC_ERR 4

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		fds[2];
	int		fd_tmp;
	char	**arg_data;
	char	*path;
	int		flag;
	int		arg_count;

}				t_pipex;

/*
 * 		exec.c
 */
char	*get_data_path(char *argument, char **env, t_pipex *pip);
char	*find_exec_file (t_pipex *pip, char **path_arr);
char	*get_path_from_env(char **env);
char	*get_pwd_exec(char *argument, char **env, t_pipex *pip);

/*
 * 		pipex_utils.c
 */

void	ft_free_array(char **arr);
void	ft_free_line(char *line);
void	ft_error_exit (char *str, t_pipex *pip, int err);
void	fd_init(t_pipex *pip, int argc, char **argv);

#endif
