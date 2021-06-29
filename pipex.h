#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include "libft/libft.h"
#include "libft/get-next-line/get_next_line.h"

typedef struct s_pipex
{
	int 	fd_in;
	int 	fd_out;

}				t_pipex;

char *get_data_path(char *argument, char **env, char ***arg_data);
void ft_free_array(char **arr);
void ft_free_line(char *line);

#endif
