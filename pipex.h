#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include "../libft/get-next-line/get_next_line.h"

char *get_data_path(char *argument, char **env, char ***arg_data);

#endif
